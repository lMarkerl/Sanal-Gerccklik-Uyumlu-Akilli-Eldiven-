#include <Wire.h>
#include <SFE_BMP180.h>
SFE_BMP180 bmp180;

const int FLEX_PIN = A0; 
const float VCC = 4.98; 
const float R_DIV = 9700; 
const float STRAIGHT_RESISTANCE =52000; 
const float BEND_RESISTANCE =180000; 
void setup() 
{
  Serial.begin(9600);
  bmp180.begin();
  pinMode(FLEX_PIN, INPUT);
}
void loop() 
{
  char status;
  double T,P;
  bool success = false;

  int flexADC = analogRead(FLEX_PIN);
  float flexV = flexADC * VCC / 1024.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0);
   status = bmp180.startTemperature();
  if (status != 0) {
    status = bmp180.getTemperature(T);
    if (status != 0) {
      status = bmp180.startPressure(3);
      if (status != 0) {
        status = bmp180.getPressure(P, T);}}}
  Serial.println(String(angle)+" degree "+String(P)+" hPA");
  delay(500);}
