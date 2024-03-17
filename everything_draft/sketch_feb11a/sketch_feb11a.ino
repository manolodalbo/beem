#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

#include <Wire.h>

const int pressureInput = A0;
const int pressureZero = 102.4;
const int pressureMax = 921.6;
const int pressuretransducermaxPSI = 100;
const int sensorreadDelay = 250;

float pressureValue = 0;

const int cameraTriggerPin = 6;
Adafruit_BMP085 bmp;
float x_acceleration = 0;
int going = 0;
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
  printData();
  readWaterSensor();
  while(a>2.00) {
    startCamera();
    printData();
    readWaterSensor();
    a = getYAcceleration();
  }
  if (going == 1) {
    delay(100);
    endCamera();
  }
}
/*
Given that the same signal is used to start and end the recording from the camera, we simply call the signal method
which will send this signal.
*/
void startCamera() {
  going = 1;
  signal();
}
/*
The endCamera() function is exactly the same as the startCamera, but we use it for increased organization and clarity
*/
void endCamera() {
  going = 0;
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
  Serial.print("accelaration in x_direction:");
  Serial.println(event.acceleration.x);
  Serial.print("acceleration in y_direction:");
  Serial.println(event.acceleration.y);
  Serial.print("acceleration in z_direction:");
  Serial.println(event.acceleration.z);
  return event.acceleration.x;
}
/*
This is called to to print the data recorded by the bmp.
*/
void printData() {
  // for the pressure and temperature sensor
  Serial.print("Temperature:");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
    
  Serial.print("Pressure:");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  // use delay 1 for every 10 ms as stated by maddy 
  Serial.println();
}

void readWaterSensor() {
  pressureValue = analogRead(pressureInput);
  Serial.print("pressure value:");
  Serial.println(pressureValue);
  pressureValue = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero);
  Serial.print("WaterPressure:");
  Serial.print(pressureValue);
  Serial.println("psi");
  delay(250);
}