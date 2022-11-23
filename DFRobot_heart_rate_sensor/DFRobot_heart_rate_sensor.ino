#include "DFRobot_Heartrate.h"

DFRobot_Heartrate heartrate(DIGITAL_MODE);

void setup() {
  Serial.begin(9600);
}

int heartrateValue;
int count;
int BPM;

void loop() {
  heartrateValue = heartrate.getValue(A0);
  count = heartrate.getCnt();
  BPM = heartrate.getRate();

  if(BPM) {
    Serial.print(" BPM: ");
    Serial.println(BPM);
  }

  delay(20);
}
