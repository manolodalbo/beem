const int outputPin = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(outputPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(outputPin,HIGH);
  delay(2000);
  digitalWrite(outputPin,LOW);
  delay(2000);
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