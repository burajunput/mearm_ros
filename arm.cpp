#include <iostream>
#include <cmath>
#include "arm.h"
using namespace std;

arm::arm(){}

arm::arm(double q1, double q2, double q3){
  this->q1 = q1;
  this->q2 = q2;
  this->q3 = q3;
}

void arm::print(){
  cout<< "q1 = " << this->q1 << endl;
  cout<< "q2 = " << this->q2 << endl;
  cout<< "q3 = " << this->q3 << endl;
  cout<< "aQ3 = " << this->aQ3 << endl;
}

void arm::set_offset(double o_s1, double o_s2, double o_s3){
  off1 = o_s1;
  off2 = o_s2;
  off3 = o_s3;
}

void arm::clawClose(){
  this->claw = 115;
}

void arm::clawOpen(){
  this->claw = 25;

}

//function for calculating inverse kinematics. Theta1 is the joint connecting l1 and the base. Theta2 is the joint connecting l1 and l2.
void arm::new_pos(double x, double y)
{
  double theta1, theta2, h; //theta1 and theta2 angles to be found. hypotenuse is the link between base and end effector.
  double diff1, diff2;
  h = sqrt( pow(x, 2) + pow(y, 2) );
  theta2 = acos( (pow(h, 2) - pow(l1, 2) - pow(l2, 2))/((-2)*l1*l2) );
  theta1 = asin( y/h ) + asin( (l2*sin(theta2))/h );
  theta1 = theta1 * (180/M_PI);
  theta2 = theta2 * (180/M_PI);

  diff1 = theta1 - this->q2;
  diff2 = theta2 - this->q3;

  this->q2 = theta1;
  this->q3 = theta2;
  aQ3 += diff1 + diff2;
  //cout << "(theta1, theta2) = (" << theta1 << ", " << theta2 << ")" << endl;

}
