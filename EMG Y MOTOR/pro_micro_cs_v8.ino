#include <Servo.h>

Servo servo1;  // create servo object to control a servo


int Flexion;
int Extension;
int N_veces;
int Velocidad;
int Delay_flex;
int Delay_ext;
int Pos_inic;

//---------------------------------------
//variables del servomotor
int delay_veloc; //es el delay para variar la velocidad de las repeticiones
int i, j, k;
int pin_servo = 9;
int pulso_min = 625;
//625
int pulso_max = 2450;
//2450


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //  delay(100);
  Serial1.begin(9600);
  //delay(100);
  //  Serial.println("Ingrese la configuracion:");
  //  servo1.attach(pin_servo, pulso_min, pulso_max);  // attaches the servo on pin 9 to the servo object
  //  servo1.write(0);                                 // tell servo to go to position in variable 'pos'
  //  delay(20);
    Flexion=0;
    Extension=0;
    N_veces=0;
    Velocidad=0;
    Delay_flex=0;
    Delay_ext=0;
    Pos_inic=0;
}

void loop() {

//int datos2 = Serial1.read();
//Serial.println(datos2);
  //Serial.println("Ingrese la configuracion:");
  if (Serial1.available() > 0) {
    int datos = Serial1.read();
    if (datos == 's') {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
      Flexion = Serial1.parseInt();
      Extension = Serial1.parseInt();
      N_veces = Serial1.parseInt();
      Velocidad = Serial1.parseInt();
      Delay_flex = Serial1.parseInt();
      Delay_ext = Serial1.parseInt();
      Pos_inic = Serial1.parseInt();

      //Con este codigo reviso en la compu si recibi bien los datos
      Serial.println("Su configuracion fue:");
      Serial.println(Flexion);
      Serial.println(Extension);
      Serial.println(N_veces);
      Serial.println(Velocidad);
      Serial.println(Delay_flex);
      Serial.println(Delay_ext);
      Serial.println(Pos_inic);

      //Voy a configurar la velocidad
      // la 3 es la más rápida
      switch (Velocidad) {
        case 1:
          delay_veloc = 35;
          break;
        case 2:
          delay_veloc = 20;
          break;
        case 3:
          delay_veloc = 12;
          break;
      }

      //Ahora voy a hacer la conversion de los parámetros
      // (para que funcione bien el motor):
      Flexion=180-Flexion;
      Extension=180-Extension;
      Delay_flex=Delay_flex*1000;
      Delay_ext=Delay_ext*1000;
      Pos_inic=180-Pos_inic;


      Serial1.print('E');

      k = Pos_inic; //Este valor debe medirse con el goniómetro
      // medir con goniómetro
      if (N_veces > 0) {


        servo1.attach(pin_servo, pulso_min, pulso_max);  // attaches the servo on pin 9 to the servo object
        //j = k;
        for (i = 1; i <= N_veces; i += 1) {

          for (j = k; j <= Flexion; j += 1) {
            servo1.write(j);
            delay(delay_veloc);
          }

          delay(Delay_flex);

          k = j;

          for (j = k; j >= Extension; j -= 1) {
            servo1.write(j);
            delay(delay_veloc);
          }
          delay(Delay_ext);
          k = j;
        }


        //        k = j;
        //        //Con esto regreso a 0 suavemente:
        //        for (j = k; j > 0; j -= 1) {
        //          servo1.write(j);
        //          delay(20);
      }
      Serial.println("La sesión ha terminado");
      Serial1.print('Q');
      servo1.detach(); //Aqui le paro al motor hasta donde se haya quedado en la ultima extension
      Flexion = 0;
      Extension = 0;
      N_veces = 0;
      Velocidad = 0;
      Delay_flex= 0;
      Delay_ext= 0;
      Pos_inic=0;
      i=0;
      j=0;
      k=0;
    }
  }
}


