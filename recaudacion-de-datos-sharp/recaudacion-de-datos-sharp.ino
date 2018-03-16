void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
}

double sensor4 = 0;
String trama = "";
void loop() {
  // put your main code here, to run repeatedly:
  sensor4 = analogRead(A1);
  trama = "";
  trama += sensor4;
  Serial.println(trama);
  delay(1);
}
