#include "Arduino.h"
#include "EscOutCandles.h"
#include "MFRC522.h"
#include "doors.h"
#include <avr/wdt.h>

static void DumbByteArray(byte *buffer, byte bufferSize);
static bool areEqual(byte *arr1, byte *arr2, uint8_t n1, uint8_t n2);
static uint8_t sumArray(byte *arr, uint8_t n);
static void clearArray(byte *arr, uint8_t n);
static void toggleLED(uint8_t toggle_number);
// static void rebootArduino(void);

byte ssPins[] = {SS_1_PIN, SS_2_PIN, SS_3_PIN, SS_4_PIN, SS_5_PIN, SS_6_PIN};
MFRC522 mfrc522[NR_OF_READERS];

static rfid_state_t rfid_state = RFID_GET_TAG_ID;
static byte correct[NR_OF_READERS] = {0};

// byte tags_uids[NR_OF_READERS][7] = {
//     {0x1D, 0x8F, 0xC6, 0xA7, 0x03, 0x10, 0x80}, // 1
//     {0x1D, 0x94, 0xC6, 0xA7, 0x03, 0x10, 0x80}, // 2
//     {0x1D, 0x92, 0xC6, 0xA7, 0x03, 0x10, 0x80}, // 3
//     {0x1D, 0xFC, 0xC4, 0xA7, 0x03, 0x10, 0x80}, // 4
//     {0x1D, 0x00, 0xC6, 0xA7, 0x03, 0x10, 0x80}, // 5
//     {0x1D, 0xF1, 0xC4, 0xA7, 0x03, 0x10, 0x80}, // 6
// };

byte tags_uids[NR_OF_READERS][4] = {
    {0xF3, 0x19, 0xA8, 0xF7}, // 1
    {0x83, 0x0E, 0x04, 0xB7}, // 2
    {0x01, 0x72, 0x7F, 0x26}, // 3
    {0x63, 0x94, 0x7B, 0xB7}, // 4
    {0x53, 0xAB, 0xA6, 0xF7}, // 5
    {0xD3, 0xBE, 0x7A, 0xB7}, // 6
};

void EscOutCandles_Init(void)
{

    Serial.begin(9600);
    while (!Serial)
        ;
    SPI.begin();
    bool correct_init_flag = false;
    while (correct_init_flag == false)
    {
        for (uint8_t reader = 0; reader < NR_OF_READERS; reader++)
        {
            if (correct[reader] == 0)
            {
                mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
                byte rfid_version = mfrc522[reader].PCD_DumpVersion();
                Serial.print(F("Reader "));
                Serial.print(reader);
                Serial.print(F(" ver: "));
                Serial.println(rfid_version, HEX);

                if (rfid_version != 0x92)
                {
                    correct[reader] = 0;
                    mfrc522[reader].PCD_SoftPowerDown();
                }
                else
                {
                    bool result = mfrc522[reader].PCD_PerformSelfTest();
                    if (result == true)
                    {
                        correct[reader] = 1;
                        mfrc522[reader].PCD_SetAntennaGain(MFRC522::PCD_RxGain::RxGain_max);
                        Serial.print(F("Reader "));
                        Serial.print(reader);
                        Serial.println(" test passed!");
                    }
                    else
                    {
                        correct[reader] = 0;
                        mfrc522[reader].PCD_SoftPowerDown();
                    }
                }
            }
            delay(100);
        }

        if (sumArray(correct, NR_OF_READERS) == NR_OF_READERS)
            correct_init_flag = true;

        Serial.print("Initialization array: ");
        DumbByteArray(correct, NR_OF_READERS);
    }
    toggleLED(1);
    clearArray(correct, NR_OF_READERS);
}

void EscOutCandles_Process(void)
{
    switch (rfid_state)
    {
    case RFID_GET_TAG_ID:
    {
        for (uint8_t reader = 0; reader < NR_OF_READERS; reader++)
        {
            if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial())
            {
                Serial.print(F("Reader "));
                Serial.print(reader);
                Serial.print(F(": Card UID:"));
                DumbByteArray(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
                Serial.println();
                mfrc522[reader].PICC_HaltA();
                mfrc522[reader].PCD_StopCrypto1();

                if (areEqual(mfrc522[reader].uid.uidByte, tags_uids[reader], mfrc522[reader].uid.size, 4))
                {
                    Serial.print("Tag placed properly ");
                    correct[reader] = 1;
                }
                else
                {
                    Serial.print("Tag NOT placed properly ");
                    correct[reader] = 0;
                }
                DumbByteArray(tags_uids[reader], 4);
                Serial.println();
                Serial.print("Correct array:");
                DumbByteArray(correct, NR_OF_READERS);
                Serial.println();
                Serial.println();

                if (sumArray(correct, NR_OF_READERS) == NR_OF_READERS)
                {
                    Serial.println("All tags placed correctly!");
                    DOORS_Open();
                    rfid_state = RFID_WAIT_FOR_CLOSE;
                    //rfid_state = RFID_CHECK_ALL_TAGS;
                }
            }
        }
        break;
    }

    case RFID_CHECK_ALL_TAGS:
    {
        bool correct_flag = false;
        uint8_t correct_tags = 0;
        for (uint8_t reader = 0; reader < NR_OF_READERS; reader++)
        {
            for (int i = 0; i < 200; i++)
            {
                byte bufferATQA[2];
                byte bufferSize = sizeof(bufferATQA);

                MFRC522::StatusCode result = mfrc522[reader].PICC_WakeupA(bufferATQA, &bufferSize);
                correct_flag = false;
                if (result == MFRC522::STATUS_OK && mfrc522[reader].PICC_ReadCardSerial())
                {
                    mfrc522[reader].PICC_HaltA();
                    Serial.print(F("Reader "));
                    Serial.print(reader);
                    Serial.println(" OK");
                    correct_flag = true;
                    correct_tags++;
                    break;
                }
            }
            if (!correct_flag)
            {
                Serial.print(F("Reader "));
                Serial.print(reader);
                Serial.println(" FAIL");
                rfid_state = RFID_GET_TAG_ID;
            }
        }

        if (correct_tags == NR_OF_READERS)
        {
            Serial.println("All tags placed correctly!");
            DOORS_Open();
            rfid_state = RFID_WAIT_FOR_CLOSE;
        }
        else
        {
            Serial.println("Move to RFID GET TAG ID");
        }
        break;
    }

    case RFID_WAIT_FOR_CLOSE:
    {
        if (DOORS_AreOpen() == false)
        {
            rfid_state = RFID_GET_TAG_ID;
            Serial.println("Doors closed - new game started");
            clearArray(correct, NR_OF_READERS);
        }
        break;
    }
    }
}

// Helper routine to dump a byte array as hex values to Serial.
static void DumbByteArray(byte *buffer, byte bufferSize)
{
    for (byte i = 0; i < bufferSize; i++)
    {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

static bool areEqual(byte *arr1, byte *arr2, uint8_t n1, uint8_t n2)
{
    if (n1 != n2)
        return false;

    for (uint8_t i = 0; i < n1; i++)
        if (arr1[i] != arr2[i])
            return false;

    return true;
}

static uint8_t sumArray(byte *arr, uint8_t n)
{
    uint8_t sum = 0;
    for (uint8_t i = 0; i < n; i++)
        sum = sum + arr[i];
    return sum;
}

static void clearArray(byte *arr, uint8_t n)
{
    for (uint8_t i = 0; i < n; i++)
        arr[i] = 0;
}

static void toggleLED(uint8_t toggle_number)
{
    pinMode(A0, OUTPUT);
    bool toggle = true;
    for (uint8_t i = 0; i < toggle_number * 2; i++)
    {
        toggle = !toggle;
        digitalWrite(A0, toggle);
        delay(150);
    }
}

// void rebootArduino(void)
// {
//     // Serial.println("Reboot Arduino");
//     // Serial.println("--------------");
//     delay(500);
//     wdt_disable();
//     wdt_enable(WDTO_15MS);
//     while (1)
//     {
//     }
// }