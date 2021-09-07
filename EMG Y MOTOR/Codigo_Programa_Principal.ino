#define sensorPin A0
//Valor de confianza para el low-pass filter
#define alpha 0.20
#include <EEPROM.h>
// twelve servo objects can be created on most boards
double lectura; //Lecturas filtradas que se enviaran por serial
int n_veces; //número de veces de la flexión-extensión 
int i;
int j;
String string = "";
int m = 0;
int pulso_min=500;
int pulso_max=2400;
char palabra[5];
int value = 0;
int Flexion;
int Extension;
int N_veces;
int Velocidad;
int Tiempo_extension;
int Tiempo_flexion;
int P_inicial;
char rutina;
bool rutina_lista=false;


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
}

void loop() {

  
  if((Serial1.available()>0) || (Serial2.available()>0))
  {

    int mensaje = Serial1.read();  //Recibo x el bluetooth
    char mensaje2 = Serial2.read();
    Serial.println(mensaje2);
    //string += mensaje;              //paso a string mensaje 
    //m = string.length();
    // tomo el lenght de string
    
      if (mensaje == 's') {
      Flexion = Serial1.parseInt();
      Extension = Serial1.parseInt();
      N_veces = Serial1.parseInt();
      Velocidad = Serial1.parseInt();
      Tiempo_flexion=Serial1.parseInt();
      Tiempo_extension=Serial1.parseInt();
      P_inicial=Serial1.parseInt();
      rutina_lista=true;
     // digitalWrite(led,HIGH);
      delay(500);
      
//    if (m == 4) {
//    string.toCharArray(palabra, 5);
//    string = "";
//    Serial.println(palabra);
//
//    //TOMA DE LOS VALORES QUE LLEGARON POR EL SERIAL DEL CELULAR
//    
//    Flexion=palabra[0];
//    Extension=palabra[1];
//    N_veces=palabra[3];
//    Velocidad=palabra[2];
//    rutina_lista=true;
//    digitalWrite(led,HIGH);
//    delay(500);
//   
    Serial.println("la rutina esta lista"); 
    }
    else{
     Flexion=0;
     Extension=0;
     N_veces=0;
     Velocidad=0;

  }
      //switch(mensaje){
     //case 'E':
     if ((mensaje=='E') || (mensaje2=='E'))
     {
     start();
     //break; 
     }
     mensaje=0;

     //Si la rutina ya esta lista empiezo la comunicación
  if (rutina_lista==true){ 

      Serial2.println('s');     
      Serial2.print(Flexion);
      Serial.println(Flexion);
      Serial2.print(',');
      Serial2.print(Extension);
      Serial.println(Extension);
      Serial2.print(',');
      Serial2.print(N_veces);
      Serial.println(N_veces);
      Serial2.print(',');
      Serial2.println(Velocidad);
      Serial.println(Velocidad);
      Serial2.print(',');
      Serial2.println(Tiempo_flexion);
      Serial.println(Tiempo_flexion);
      Serial2.print(',');
      Serial2.println(Tiempo_extension);
      Serial.println(Tiempo_extension);
      Serial2.print(P_inicial);
      Serial.println(P_inicial);
      Serial2.print(',');
      rutina_lista=false;
  }
}
}

void start(){
 while(1){
  Serial1.print('s');
  int val=analogRead(sensorPin);
  lectura = (1-alpha)*lectura+alpha*val; //Filtrar estas lecturas
  Serial1.print(floatMap(lectura,0,1023,0,5),2);
  Serial.println(floatMap(lectura,0,1023,0,5),2);
  delay(1);
  
  if((Serial1.available()>0)||(Serial2.available()>0)){
    if ((Serial1.read()=='Q')||(Serial2.read()=='Q')) return;
  }
 }
}
float floatMap(float x, float inMin, float inMax, float outMin, float outMax){
  return (x-inMin)*(outMax-outMin)/(inMax-inMin)+outMin;
}
