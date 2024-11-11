#include <Arduino.h>
#include <rdm6300.h>


#define RDM6300_RX_PIN 23

#define ELEKTROZWORA 26
#define SOUND_ENABLE 22
#define RESET 21 


Rdm6300 rdm6300;

void setup() {
  pinMode(ELEKTROZWORA, OUTPUT);
  digitalWrite(ELEKTROZWORA, HIGH);
  pinMode(SOUND_ENABLE, OUTPUT);
  digitalWrite(SOUND_ENABLE, HIGH);
  pinMode(RESET, INPUT_PULLUP);
  rdm6300.begin(RDM6300_RX_PIN);
  // put your setup code here, to run once:
  Serial.begin(9600);
}

uint32_t tag_id = 0;

void loop() {
  tag_id = rdm6300.get_new_tag_id();
    if (tag_id == 11497528)
    {
      Serial.print("tag_id correct: ");
      Serial.println(tag_id);
      enableAllThings();
    }
    delay(10);
  // put your main code here, to run repeatedly:

}
int val = 1;

void enableAllThings()
{
  digitalWrite(SOUND_ENABLE, LOW);
  delay(1000);
  digitalWrite(SOUND_ENABLE, HIGH);
  delay(59000);
  digitalWrite(ELEKTROZWORA, LOW);
  while(true)
  {
    val = digitalRead(RESET);
    delay(10);
    if(val == 0)
    {
      ESP.restart();
    }
  }
}
