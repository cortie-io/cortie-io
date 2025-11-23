#include "Arduino.h"
#include "AX12A.h"

#define DirectionPin    (10u)
#define BaudRate        (1000000ul)

#define ID1            (1u)
#define ID2            (2u)
#define ID3            (3u)
#define ID4            (4u)

int mot1Pos = 512;
int mot2Pos = 512;
int mot3Pos = 200;
int mot4Pos = 512;



 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ax12a.begin(BaudRate, DirectionPin, &Serial1);
}

void loop() {
  // put your main code here, to run repeatedly:
  receiveSerial();
  moveMotor();
}

void moveMotor() {
  ax12a.move(ID1, mot1Pos);
  ax12a.move(ID2, mot2Pos);
  ax12a.move(ID3, mot3Pos);
  ax12a.move(ID4, mot4Pos);

  
  Serial.print(mot1Pos);
  Serial.print(",");
  Serial.print(mot2Pos);
  Serial.print(",");
  Serial.print(mot3Pos);
  Serial.print(",");
  Serial.print(mot4Pos);
  Serial.println();
}

void receiveSerial() {
  if (Serial.available()) {
    int n1, n2, n3, n4;
    String packet = Serial.readStringUntil('*');
    sscanf(packet.c_str(), "%d,%d,%d,%d", &n1, &n2, &n3, &n4); //mot1Pos,mot1Pos,mot1Pos,mot1Pos

    mot1Pos = constrain(n1, 410, 840);
    mot2Pos = constrain(n2, 50, 940);
    mot3Pos = constrain(n3, 0, 530);
    mot4Pos = constrain(n4, 0, 1023);
  }
}