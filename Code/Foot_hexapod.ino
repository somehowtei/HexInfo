#include <Servo.h>
int pin_coxa1=2;
int pin_femur1=3;
int pin_tibie1=4;

int poz_coxa_initial=90;
int poz_femur_initial=180;
int poz_tibie_initial=180;

int poz_coxa1=90;
int poz_femur1=180-35;
int poz_tibie1=180-55;

Servo servo_coxa1;
Servo servo_femur1;
Servo servo_tibie1;

void setup() {
 Serial.begin(9600);
 servo_coxa1.attach(pin_coxa1);
 servo_femur1.attach(pin_femur1);
 servo_tibie1.attach(pin_tibie1);
}

void loop() {
  /*servo_coxa1.write(poz_coxa1);
  servo_femur1.write(poz_femur1);
  servo_tibie1.write(poz_tibie1);
  */

  servo_coxa1.write(poz_coxa_initial);
  servo_femur1.write(poz_femur_initial);
  servo_tibie1.write(poz_tibie_initial);
}
