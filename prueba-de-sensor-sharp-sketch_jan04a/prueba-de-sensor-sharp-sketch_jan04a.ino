void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
}

double sensor1 = 0;
double sensor2 = 0;
double sensor3 = 0;
double sensor4 = 0;
double alpha = 0.04;
String trama = "";
void loop() {
  // put your main code here, to run repeatedly:
  /*
  sensor1 = sensor1*(1-alpha) + analogRead(A0)*alpha;
  sensor2 = sensor2*(1-alpha) + analogRead(A1)*alpha;
  sensor3 = sensor3*(1-alpha) + analogRead(A2)*alpha;
  sensor4 = sensor4*(1-alpha) + analogRead(A3)*alpha;
  trama = "sensor1 = ";
  trama += sensor1;
  trama += "\t\t sensor2 = ";
  trama += sensor2;
  trama += "\t\t sensor3 = ";
  trama += sensor3;
  trama += "\t\t sensor4 = ";
  trama += sensor4;
  */
  sensor1 = sensorPromedio(A0,50);
  sensor2 = sensorPromedio(A1,50);
  sensor3 = sensorPromedio(A2,50);
  sensor4 = sensorPromedio(A3,50);
  trama = "sensor1 = ";
  trama += sensor1;
  trama += "\t\t sensor2 = ";
  trama += sensor2;
  trama += "\t\t sensor3 = ";
  trama += sensor3;
  trama += "\t\t sensor4 = ";
  trama += sensor4;
  Serial.println(trama);
  delay(1);
}


int sensorPromedio(int pin,int n)
{
  double suma=0;
  double alpha = 0.02;
  for(int i=0;i<n;i++)
  {
    suma=suma*(1-alpha)+analogRead(pin)*alpha;
  }  
  return((int)suma);
}
