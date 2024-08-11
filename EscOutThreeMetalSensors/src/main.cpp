#include <Arduino.h>
#include "MetalSensor.h"
#include "doors.h"
#include "pitches.h"

#define LED 13
#define BUTTON 12
#define SENS_1 11
#define SENS_2 10
#define SENS_3 9
#define BUZZER 8

#define SENS_1_SOLUTION 7
#define SENS_2_SOLUTION 6
#define SENS_3_SOLUTION 5

MetalSensor Sensor1(SENS_1);
MetalSensor Sensor2(SENS_2);
MetalSensor Sensor3(SENS_3);

// Metal Sensor is compatible behaviour as button
MetalSensor Button(BUTTON);

uint8_t sens_array[3] = {0, 0, 0};

void PlayGoodMelody(void);
void PlayWinMelody(void);
void PlayBadMelody(void);
void ClearSensArray(void);

void setup()
{
  pinMode(LED, OUTPUT);

  Sensor1.begin();
  Sensor2.begin();
  Sensor3.begin();
  Button.begin();
  Serial.begin(9600);
  DOORS_Init();
}

uint8_t init_state = 1;

void loop()
{
  DOORS_Process();

  if (Sensor1.pressed())
  {
    sens_array[0]++;
    Serial.print("S1 detected number of detections :");
    Serial.println(sens_array[0]);
    PlayGoodMelody();
  }
  else if (Sensor2.pressed())
  {
    sens_array[1]++;
    Serial.print("S2 detected number of detections :");
    Serial.println(sens_array[1]);
    PlayGoodMelody();
  }
  else if (Sensor3.pressed())
  {
    sens_array[2]++;
    Serial.print("S3 detected number of detections :");
    Serial.println(sens_array[2]);
    PlayGoodMelody();
  }

  if (Button.released())
  {
    if (sens_array[0] == SENS_1_SOLUTION && sens_array[1] == SENS_2_SOLUTION && sens_array[2] == SENS_3_SOLUTION)
    {
      DOORS_Open();
      Serial.print("Good! ");
      Serial.print("S1:");
      Serial.print(sens_array[0]);
      Serial.print(" S2:");
      Serial.print(sens_array[1]);
      Serial.print(" S3:");
      Serial.println(sens_array[2]);

      PlayWinMelody();

      // digitalWrite(3, HIGH);
      // delay(1000);
      // digitalWrite(3, LOW);
    }
    else
    {
      Serial.print("Failed! ");
      Serial.print("S1:");
      Serial.print(sens_array[0]);
      Serial.print(" S2:");
      Serial.print(sens_array[1]);
      Serial.print(" S3:");
      Serial.println(sens_array[2]);
      PlayBadMelody();
    }
    ClearSensArray();
  }
}

void PlayGoodMelody(void)
{
  tone(BUZZER, 2000, 100);
  delay(100);
}
void PlayBadMelody(void)
{
  tone(BUZZER, NOTE_G4);
  delay(250);
  tone(BUZZER, NOTE_C4);
  delay(500);
  noTone(BUZZER);
}

void PlayWinMelody(void)
{
  tone(BUZZER, NOTE_A7);
  delay(250);
  tone(BUZZER, NOTE_D8);
  delay(500);
  noTone(BUZZER);
}

void ClearSensArray(void)
{
  for (uint8_t i = 0; i < 3; i++)
    sens_array[i] = 0;
}