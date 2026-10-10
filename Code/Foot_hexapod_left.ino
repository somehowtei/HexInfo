#include <math.h>
#include <Servo.h>
int PinLeftFrontLeg1_Hip=2;
int PinLeftFrontLeg1_Knee=3;
int PinLeftFrontLeg1_Foot=4;
Servo ServoLeftFrontLeg1_Hip;
Servo ServoLeftFrontLeg1_Knee;
Servo ServoLeftFrontLeg1_Foot;
int LeftFrontLeg1_Hip=90; //90
int LeftFrontLeg1_Knee; //180
int LeftFrontLeg1_Foot; //180
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
  ServoLeftFrontLeg1_Hip.attach(PinLeftFrontLeg1_Hip);
  ServoLeftFrontLeg1_Knee.attach(PinLeftFrontLeg1_Knee);
  ServoLeftFrontLeg1_Foot.attach(PinLeftFrontLeg1_Foot);
}

void loop() {
  l=sqrt(pow(y,2)+pow(z,2));
  Foot_angle=acos((pow(Thigh_length,2)+pow(Foot_length,2)-pow(l,2))/(2*Thigh_length*Foot_length))*rad_to_degree;
  Vb_angle=acos((pow(l,2)+pow(Thigh_length,2)-pow(Foot_length,2))/(2*l*Thigh_length))*rad_to_degree;
  Va_angle=atan(z/y)*rad_to_degree;
  Knee_angle=180-(Va_angle-Vb_angle);
  Serial.print(l);
  Serial.print(" ");
  Serial.print(Foot_angle);
  Serial.print(" ");
  Serial.print(Vb_angle);
  Serial.print(" ");
  Serial.print(Va_angle);
  Serial.print(" ");
  Serial.println(Knee_angle);
  ServoLeftFrontLeg1_Hip.write(LeftFrontLeg1_Hip);
  ServoLeftFrontLeg1_Knee.write(Knee_angle);
  ServoLeftFrontLeg1_Foot.write(Foot_angle);
  delay(500);
}
