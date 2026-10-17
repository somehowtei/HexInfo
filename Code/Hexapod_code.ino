#include <math.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver PWM_left(0x40); 
Adafruit_PWMServoDriver PWM_right(0x41); 

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

float Thigh_length=47;
float Foot_length=43;

const float rad_to_degree=180.0/PI;

void SetAngle(Adafruit_PWMServoDriver &pwm, int channel, float angle) //conversie de la grade la impuls
{
  angle=constrain(angle, 0, 180);
  int pulse=1000+(angle/180)*1000; //modificam in functie de motor
  pwm.writeMicroseconds(channel, pulse);
}

void Position1(Adafruit_PWMServoDriver &pwm, int chHip, int chKnee, int chFoot) 
{
  float Va_angle;
  float Vb_angle;
  float Hip_angle=90;
  float Knee_angle;
  float Foot_angle;
  float l;
  float y=45;
  float z=55;
  l=sqrt(pow(y,2)+pow(z,2));
  Foot_angle=acos((pow(Thigh_length,2)+pow(Foot_length,2)-pow(l,2))/(2*Thigh_length*Foot_length))*rad_to_degree;
  Vb_angle=acos((pow(l,2)+pow(Thigh_length,2)-pow(Foot_length,2))/(2*l*Thigh_length))*rad_to_degree;
  Va_angle=atan(z/y)*rad_to_degree;
  Knee_angle=180-(Va_angle-Vb_angle);
  SetAngle(pwm, chHip, Hip_angle);
  SetAngle(pwm, chKnee, Knee_angle);
  SetAngle(pwm, chFoot, Foot_angle);
} 

void setup() 
{
  Wire.begin();
  PWM1.begin();
  PWM2.begin();
  PWM_left.setPWMFreq(50);
  PWM_right.setPWMFreq(50);
  Serial.begin(9600);
}

void loop() 
{
  Position1(PWM1, chRightLeg1_Hip, chRightLeg1_Knee, chRightLeg1_Foot);
}
