#include <iostream>
#include <cmath>
#include "arm.h"
using namespace std;

double l1 = 79.3, l2 = 79.3; //Lengths of the links(mm). l1 is the link from base to the elbow. l2 is the link from elbow to end effector.

//function for calculating forward kinematics. Theta1 is the joint connecting l1 and the base. Theta2 is the joint connecting l1 and l2.
void fk(double choice1, double choice2){
  double x2, y2; //x1, y1 are the coordinates of where the elbow joint is located in space. x2, y2 are the coordinates of where the end effector is located in space.
  double theta1 = (M_PI/180)*choice1, theta2 = (M_PI/180)*choice2; //angle converted to radians.

  double l3; //does not actually exist but is the link from q1 to the end effector which forms a triangle with l1 and l2;
  double thetaA, thetaB; //thetaA + thetaB = theta1. thetaA is the angle above l3. thetaB is the angle below l3;
  l3 = sqrt( pow(l1, 2) + pow(l2, 2) - 2*l1*l2*cos(theta2));
  thetaA = asin( (sin(theta2)*l2)/l3 );
  thetaB = theta1 - thetaA;
  y2 = l3*sin(thetaB);
  x2 = sqrt(pow(l3, 2) - pow(y2, 2));

  cout << "(X2, Y2) = (" << x2 << ", " << y2 << ")" << endl;

}


//function for calculating inverse kinematics. Theta1 is the joint connecting l1 and the base. Theta2 is the joint connecting l1 and l2.
void ik(double x, double y){
  double theta1, theta2, h; //theta1 and theta2 angles to be found. hypotenuse is the link between base and end effector.
  h = sqrt( pow(x, 2) + pow(y, 2) );
  theta2 = acos( (pow(h, 2) - pow(l1, 2) - pow(l2, 2))/((-2)*l1*l2) );
  theta1 = asin( y/h ) + asin( (l2*sin(theta2))/h );
  theta1 = theta1 * (180/M_PI);
  theta2 = theta2 * (180/M_PI);

  cout << "(theta1, theta2) = (" << theta1 << ", " << theta2 << ")" << endl;

}



int main(){
  //double start_val = 90.0;
  arm mearm;

  double choice1, choice2;
  cout << "Enter x: " << endl;
  cin >> choice1;
  cout << "Enter y: " << endl;
  cin >> choice2;
  mearm.new_pos(choice1, choice2);
  mearm.print();
}
