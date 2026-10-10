#include <math.h>
#include <Servo.h>
int PinRightFrontLeg1_Hip=2;
int PinRightFrontLeg1_Knee=3;
int PinRightFrontLeg1_Foot=4;
Servo ServoRightFrontLeg1_Hip;
Servo ServoRightFrontLeg1_Knee;
Servo ServoRightFrontLeg1_Foot;
float RightFrontLeg1_Hip=90; //90
float RightFrontLeg1_Knee; //180
float RightFrontLeg1_Foot; //180
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
void setup() {
  Serial.begin(9600);
  ServoRightFrontLeg1_Hip.attach(PinRightFrontLeg1_Hip);
  ServoRightFrontLeg1_Knee.attach(PinRightFrontLeg1_Knee);
  ServoRightFrontLeg1_Foot.attach(PinRightFrontLeg1_Foot);
}

void loop() {
  l=sqrt(pow(y,2)+pow(z,2));
  Foot_angle=180-acos((pow(Thigh_length,2)+pow(Foot_length,2)-pow(l,2))/(2*Thigh_length*Foot_length))*rad_to_degree;
  Vb_angle=acos((pow(l,2)+pow(Thigh_length,2)-pow(Foot_length,2))/(2*l*Thigh_length))*rad_to_degree;
  Va_angle=atan(z/y)*rad_to_degree;
  Knee_angle=(Va_angle-Vb_angle);
  Serial.print(l);
  Serial.print(" ");
  Serial.print(Foot_angle);
  Serial.print(" ");
  Serial.print(Vb_angle);
  Serial.print(" ");
  Serial.print(Va_angle);
  Serial.print(" ");
  Serial.println(Knee_angle);
  ServoRightFrontLeg1_Hip.write(RightFrontLeg1_Hip);
  ServoRightFrontLeg1_Knee.write(Knee_angle);
  ServoRightFrontLeg1_Foot.write(Foot_angle);
  delay(500);
}
