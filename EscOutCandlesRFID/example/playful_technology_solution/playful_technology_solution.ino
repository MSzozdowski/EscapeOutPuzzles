#define DEBUG

#include <SPI.h>
#include <MFRC522.h>

const byte numReaders = 4;
const byte ssPins[] = {2,3,4,5};
const byte resetPin = 8;

MFRC522 mfrc522[numReaders];

const String correcIDs[] = {"3acbbd40", "3acbbd41", "3acbbd42", "3acbbd43"};

String currentIDs[numReaders];

const byte lockPin = A0;

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println(F("Serial communication started"));
  #endif

  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, HIGH);

  SPI.begin();

  for(uint8_t i = 0; i < numReaders; i++)
  {
    mfrc522[i].PCD_Init(ssPins[i], resetPin);
    //mfrc522[i].PCD_SetAntennaGain(MFRC522::PCD_RxGain::RxGain_max);

    Serial.print(F("Reader #"));
    Serial.print(i);
    Serial.print(F(" initialised on pin "));
    Serial.print(String(ssPins[i]));
    Serial.print(F(". Antenna strength: "));
    Serial.print(mfrc522[i].PCD_GetAntennaGain());
    Serial.print(F(". Version : "));
    mfrc522[i].PCD_DumpVersionToSerial();

    delay(100);
  }

  Serial.println(F("--- END SETUP ---"));
}

void loop() {
  boolean puzzleSolved = true;

  boolean changedValue = false;

  for(uint8_t i = 0; i < numReaders; i++)
  {
    mfrc522[i].PCD_Init();

    String readRFID = "";
    if(mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()){
      readRFID = dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
    }

    if(readRFID != currentIDs[i]){
      changedValue = true;

      currentIDs[i] = readRFID;
    }

    if(currentIDs[i] != correcIDs[i]){
      puzzleSolved = false;
    }

    mfrc522[i].PICC_HaltA();

    mfrc522[i].PCD_StopCrypto1();
  }

  if(changedValue){
    for(uint8_t i = 0; i < numReaders; i++){
      Serial.print(F("Reader #"));
      Serial.print(i);
      Serial.print(F(" on pin "));
      Serial.print(String(ssPins[i]));
      Serial.print(F(" detected tag: "));
      Serial.println(currentIDs[i]);
    }
    Serial.println(F("---"));
  }

  if(puzzleSolved)
  {
    onSolve();
  }

  delay(100);
}

void onSolve()
{
  #ifdef DEBUG
  Serial.println(F("Puzzle solved!"));
  #endif

  digitalWrite(lockPin, LOW);
  while(true){

  }
}

String dump_byte_array(byte *buffer, byte bufferSize) {
    String uid = "";
    for (byte i = 0; i < bufferSize; i++) {
        if (buffer[i] < 0x10) {
            uid += "0"; // Ensure two-digit hex representation
        }
        uid += String(buffer[i], HEX);
    }
    return uid;
}