#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(3, 2); // RX, TX

DFRobotDFPlayerMini myDFPlayer;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); 
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini"));
  Serial.println(F("Initializing DFPlayer module ... Wait!"));


    if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Not initialized:"));
    Serial.println(F("1. Check the DFPlayer Mini connections"));
    Serial.println(F("2. Insert an SD card"));
    while (true)
      ;
    }

    Serial.println();
    Serial.println(F("DFPlayer Mini module initialized!"));

  myDFPlayer.setTimeOut(500);  // Serial timeout 500ms
  myDFPlayer.volume(30);        // Volume 5
  myDFPlayer.EQ(0);            // Normal equalization
  //myDFPlayer.loop(1);
  myDFPlayer.play(1);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}
