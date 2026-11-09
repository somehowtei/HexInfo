#include <math.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver PWM_left(0x40); //vedere din fata(cum te uiti la hexapod)
Adafruit_PWMServoDriver PWM_right(0x41); //vedere din fata(cum te uiti la hexapod)

int chRightLeg1_Hip=0;
int chRightLeg1_Knee=1;
int chRightLeg1_Foot=2;
int chRightLeg2_Hip=4;
int chRightLeg2_Knee=5;
int chRightLeg2_Foot=6;
int chRightLeg3_Hip=8;
int chRightLeg3_Knee=9;
int chRightLeg3_Foot=10;

int chLeftLeg1_Hip=0;
int chLeftLeg1_Knee=1;
int chLeftLeg1_Foot=2;
int chLeftLeg2_Hip=4;
int chLeftLeg2_Knee=5;
int chLeftLeg2_Foot=6;
int chLeftLeg3_Hip=8;
int chLeftLeg3_Knee=9;
int chLeftLeg3_Foot=10;

float Thigh_length=47;
float Foot_length=43;

const float rad_to_degree=180.0/PI;

struct HipState
{
  float angle;
  int direction;
  unsigned long LastUpdate;
};

HipState hip[6]=
{
  {90,1,0}, //foot 1-left
  {90,1,0}, //foot 2-left
  {90,1,0}, //foot 3-left
  {90,1,0}, //foot 1-right
  {90,1,0}, //foot 2-right
  {90,1,0} //foot 3-right
};

void SetAngle(Adafruit_PWMServoDriver &pwm, int channel, float angle)
{
  angle=constrain(angle, 0, 180);
  int pulse=1000+(angle/180)*1000; //modificam in functie de motor
  pwm.writeMicroseconds(channel, pulse);
}

void MoveHip(Adafruit_PWMServoDriver &pwm, int channel, HipState &hip)
{
  if(millis()-hip.LastUpdate>=15)
  {
    hip.LastUpdate=millis();
    hip.angle=hip.angle+hip.direction;
    if(hip.angle>=135)
    {
      hip.angle=135;
      hip.direction=-1;
    }
    else if(hip.angle<=45)
    {
      hip.angle=45;
      hip.direction=1;
    }
    SetAngle(pwm, channel, hip.angle);
  }
}

void Position1(Adafruit_PWMServoDriver &pwm, int chKnee, int chFoot) 
{
  float Va_angle;
  float Vb_angle;
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
  SetAngle(pwm, chKnee, Knee_angle);
  SetAngle(pwm, chFoot, Foot_angle);
} 

void Position2(Adafruit_PWMServoDriver &pwm, int chKnee, int chFoot) 
{
  float Va_angle;
  float Vb_angle;
  float Knee_angle;
  float Foot_angle;
  float l;
  float y=Thigh_length+Foot_length;
  float z=0;
  l=sqrt(pow(y,2)+pow(z,2));
  Foot_angle=acos((pow(Thigh_length,2)+pow(Foot_length,2)-pow(l,2))/(2*Thigh_length*Foot_length))*rad_to_degree;
  Vb_angle=acos((pow(l,2)+pow(Thigh_length,2)-pow(Foot_length,2))/(2*l*Thigh_length))*rad_to_degree;
  Va_angle=atan(z/y)*rad_to_degree;
  Knee_angle=180-(Va_angle-Vb_angle);
  SetAngle(pwm, chKnee, Knee_angle);
  SetAngle(pwm, chFoot, Foot_angle);
} 

void setup() 
{
  Wire.begin();
  PWM_left.begin();
  PWM_right.begin();
  PWM_left.setPWMFreq(50);
  PWM_right.setPWMFreq(50);
  Serial.begin(9600);
}

void loop() 
{
  MoveHip(PWM_left, chLeftLeg1_Hip, hip[0]);
  Position1(PWM_left, chLeftLeg1_Knee, chLeftLeg1_Foot);
}
