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

int arm::clawClose(){
  this->claw = 115;
  return 115;
}

int arm::clawOpen(){
  this->claw = 25;
  return 25;
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
  this->aQ3 += diff1 + diff2;
  //cout << "(theta1, theta2) = (" << theta1 << ", " << theta2 << ")" << endl;

}

int arm::getQ1(){
  double temp = round(this->q1);
  int q1 = (int) temp;
  return q1+off1;
}

int arm::getQ2(){
  double temp = round(this->q2);
  int q2 = (int) temp;
  return q2+off2;
}

int arm::getQ3(){
  double temp = round(this->q3);
  int q3 = (int) temp;
  return q3+off3;
}

int arm::getAQ3(){
  double temp = round(this->aQ3);
  int aQ3 = (int) temp;
  return aQ3+off3;
}

void arm::setQ1(double q1){
  this->q1 = q1;
}

void arm::setQ2(double q2){
  this->q2 = q2;
}

void arm::setQ3(double q3){
  this->q3 = q3;
}

void arm::setQ2andQ3(double theta1, double theta2){
  double diff1, diff2;
  diff1 = theta1 - this->q2;
  diff2 = theta2 - this->q3;
  this->q2 = theta1;
  this->q3 = theta2;
  this->aQ3 += diff1 + diff2;
}

//claw status returns true if open and false if closed
bool arm::clawStatus(){
  if(this->claw == 25){
    return true;
  }
  else{
    return false;
  }
}
