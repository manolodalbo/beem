#include <Wire.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;

const int outputPin = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(outputPin,OUTPUT);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(outputPin,HIGH);
  delay(2000);
  digitalWrite(outputPin,LOW);
  delay(2000);

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
void startCamera() {
  signal();
}

void endCamera() {
  signal();
}

void signal() {
  digitalWrite(outputPin,HIGH);
  delay(10000);
  digitalWrite(outputPin,LOW);
}
