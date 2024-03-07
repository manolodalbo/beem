#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Wire.h>


const int cameraTriggerPin = 6;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
void setup() {

  Serial.begin(9600);
  pinMode(cameraTriggerPin,OUTPUT);
  if (!accel.begin()) {
    Serial.println("No accelerometer detected");
    while(1);
  }
}

void loop() {
  float a = getYAcceleration();
  while(a>5.00) {
    startCamera();
    delay(10000);
  }
}
void startCamera() {
  signal();
}

void endCamera() {
  signal();
}

void signal() {
  digitalWrite(cameraTriggerPin,HIGH);
  delay(200);
  digitalWrite(cameraTriggerPin,LOW);
}
float getYAcceleration() {
  sensors_event_t event;
  accel.getEvent(event);
  return event.acceleration.y;
}