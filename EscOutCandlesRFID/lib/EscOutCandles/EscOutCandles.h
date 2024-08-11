#ifndef EscOutCandles_h
#define EscOutCandles_h

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_1_PIN        4           // Configurable, take a unused pin, only HIGH/LOW required
#define SS_2_PIN        5           // Configurable, take a unused pin, only HIGH/LOW required
#define SS_3_PIN        A5          // Configurable, take a unused pin, only HIGH/LOW required
#define SS_4_PIN        A4          // Configurable, take a unused pin, only HIGH/LOW required
#define SS_5_PIN        A3          // Configurable, take a unused pin, only HIGH/LOW required
#define SS_6_PIN        A2          // Configurable, take a unused pin, only HIGH/LOW required

#define NR_OF_READERS   6

typedef enum
{
    RFID_GET_TAG_ID,
    RFID_CHECK_ALL_TAGS,
    RFID_WAIT_FOR_CLOSE
}rfid_state_t;

void EscOutCandles_Init(void);
void EscOutCandles_Process(void);

#endif