#include <Servo.h> 
Servo myservo;   

float  Velocidad, Distancia1, u1, u2, Utotal, dt = 0.3 ;
//float k[] = { -3.512,  -92.3,   47.0209,   10.0045};
float k[] = { -2.712,  -25.3,   47.0209,   10.0045};
int Setpoint = 20;
int Distancia;

void setup() 
{
  Serial.begin(9600);
  myservo.attach(7);
}
void loop() 
{
  long tiempo=millis(); //tiempo antes de iniciar la lectura
  int D_cm=distancia(500); //lectura de distancia
  tiempo=millis()-tiempo; //milisegundos que duró la lectura

  Distancia = Setpoint - D_cm;

  Velocidad = (Distancia - Distancia1)/dt;
  
  /***** LEY DE CONTROL ************/
  
  u1 = -k[0]*Distancia;
  u2 = -k[1]*Velocidad; 
  Utotal = u1 + u2;
  
  /********************************/
  
  Distancia1 = Distancia;
  Serial.println(Distancia);
  myservo.writeMicroseconds(Utotal+1365+Setpoint);

}
float distancia(int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A0);
  }  
  float adc=suma/n;
  float distancia_cm = 17569.7 * pow(adc, -1.2062);
  return(distancia_cm);
}
