#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

#include <Wire.h>


const int cameraTriggerPin = 6;
Adafruit_BMP085 bmp;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

/*
The setup method sets up both the bmp and accelerometer and also indicates the serial to begin recording
*/
void setup() {
  Serial.begin(9600);
  pinMode(cameraTriggerPin,OUTPUT);
  if (!accel.begin()) {
    Serial.println("No accelerometer detected");
    while(1){}
  }
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
}
/*
The loop gets the acceleration and if the acceleration is over a certain value than it stays in the loop
all the while printing out the bmp data.
*/
void loop() {
  float a = getYAcceleration();
  // printData();
  while(a>5.00) {
    startCamera();
    // printData();
  }
}
/*
Given that the same signal is used to start and end the recording from the camera, we simply call the signal method
which will send this signal.
*/
void startCamera() {
  signal();
}
/*
The endCamera() function is exactly the same as the startCamera, but we use it for increased organization and clarity
*/
void endCamera() {
  signal();
}
/*
The signal function sends a pulse to the camera for 200ms which should toggle the camera. Still have to test the duration
that the signal should be sent for.
*/
void signal() {
  digitalWrite(cameraTriggerPin,HIGH);
  delay(200);
  digitalWrite(cameraTriggerPin,LOW);
}
/*
Gets the y acceleration by using the adafruits library.
*/
float getYAcceleration() {
  sensors_event_t event;
  accel.getEvent(&event);
  Serial.print("accelaration in y_direction: ");
  Serial.println(event.acceleration.y);
  return event.acceleration.y;
}
/*
This is called to to print the data recorded by the bmp.
*/
void printData() {
  // for the pressure and temperature sensor
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
    
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");

  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");

  Serial.print("Real altitude = ");
  Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
  Serial.println(" meters");

  // use delay 1 for every 10 ms as stated by maddy 
  Serial.println();
  delay(500);
}