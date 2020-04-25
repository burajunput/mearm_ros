#include <cmath>
#ifndef ARM_H
#define	ARM_H

class arm{
  double q1 = 90, q2 = 90, q3 = 90, claw = 25; //q1 = base angle, q2 = base to l1 angle, q3 = l1 to l2 angle
                                                       //q2 = right. q3 = left.
  double aQ3 = 90; //this is the actual sent value of the joint angle accounting for the relationship between q2 and q3 and the new project joint.
                        //calculation for new joint is:
                        //diff1 = newQ2 - q2
                        //diff2 = newQ3 - q3
                        //actualQ3 = actualQ3 + diff1 + diff2
  double off1 = 0, off2 = 0, off3 = 0;  //offsets for the joints.
  double l1 = 79.3, l2 = 79.3;
  public:
    arm(); //default starting values
    arm (double q1, double q2, double q3); //also allow user to set starting values
    void print(); //print out current angles of joints, state of claw and the offsets
    void set_offset(double o_s1, double o_s2, double o_s3); //set the offsets of the joints
    void clawClose(); //close claw
    void clawOpen();  //open claw
    void new_pos(double x, double y);
};


#endif	/* ARM_H */
