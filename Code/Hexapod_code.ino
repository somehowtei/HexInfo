#include <math.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver PWM1(0x40);
Adafruit_PWMServoDriver PWM2(0x41);

int chRightLeg1_Hip=0;
int chRightLeg1_Knee=1;
int chRightLeg1_Foot=2;
int chRightLeg2_Hip=3;
int chRightLeg2_Knee=4;
int chRightLeg2_Foot=5;
int chRightLeg3_Hip=6;
int chRightLeg3_Knee=7;
int chRightLeg3_Foot=8;

int chLeftLeg1_Hip=0;
int chLeftLeg1_Knee=1;
int chLeftLeg1_Foot=2;
int chLeftLeg2_Hip=3;
int chLeftLeg2_Knee=4;
int chLeftLeg2_Foot=5;
int chLeftLeg3_Hip=6;
int chLeftLeg3_Knee=7;
int chLeftLeg3_Foot=8;

float RightLeg1_Hip=90; //90
float RightLeg1_Knee; //180
float RightLeg1_Foot; //180
float Thigh_length=47;
float Foot_length=43;
float Knee_angle;
float Foot_angle;
float Va_angle;
float Vb_angle;
float y=45;
float z=55;
float l;
const float rad_to_degree=180.0/PI;
// convertest din 500-2500 impuls in 0-180 grade

void setup() {
  Wire.begin();
  PWM1.begin();
  PWM2.begin();
  PWM1.setPWMFreq(50);
  PWM2.setPWMFreq(50);
  Serial.begin(9600);
  
}

void loop() {
  PWM1.writeMicroseconds(0, 1500); //canal 0 pe modul, impuls 500-2500 care trb convertit in grade 0-180
  PWM2.writeMicroseconds(0, 1500); 
}
