#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "arm.h"
#include <sstream>
using namespace std;




/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  arm mearm;
  mearm.set_offset(-10, -15, 0);
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "talker");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher q1 = n.advertise<std_msgs::Int32>("q1", 1000);
  ros::Publisher q2 = n.advertise<std_msgs::Int32>("q2", 1000);
  ros::Publisher q3 = n.advertise<std_msgs::Int32>("q3", 1000);
  ros::Publisher claw = n.advertise<std_msgs::Int32>("claw", 1000);

  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int request = 0;
  double x;
  double y;
  double z;
  std_msgs::Int32 msg;
  while (ros::ok())
  {
    std::cout << "Pick an option" << '\n';
    std::cout << "1: Rotate" << '\n';
    std::cout << "2: New X and Z Coordinates" << '\n';
    std::cout << "3: Set Q2 and Q3" << '\n';
    std::cout << "4: Claw Open/Close" << '\n';
    std::cout << "5: Exit" << '\n';
    std::cin >> request;
    if(request == 1){
      do{
        std::cout << "Input a new angle of rotation for the mearm. (Default is 90). (Range between 0 and 180)" << '\n';
        std::cin >> y;
        if(y > 180 || y < 0){
          std::cout << "Please enter a valid argument" << '\n' << endl;
        }
      }while (y > 180 || y < 0);
      mearm.setQ1(y);
      msg.data = mearm.getQ1();
      q1.publish(msg);
    }
    else if(request == 2){
      std::cout << "New x: ";
      std::cin >> x;
      std::cout << "New z: ";
      std::cin >> z;

      mearm.new_pos(x, z);
      msg.data = mearm.getQ2();
      q2.publish(msg);
      msg.data = mearm.getAQ3();
      q3.publish(msg);
      std::cout << endl;
    }
    else if(request == 3){
      std::cout << "New Q2: ";
      std::cin >> x;
      std::cout << "New Q3: ";
      std::cin >> z;

      mearm.setQ2andQ3(x, z);
      msg.data = mearm.getQ2();
      q2.publish(msg);
      msg.data = mearm.getAQ3();
      q3.publish(msg);
      std::cout << endl;
    }
    else if(request == 4){
      if(mearm.clawStatus()){
        std::cout << "Claw is open. Closing it." << '\n';
        msg.data = mearm.clawClose();
        claw.publish(msg);
      }
      else{
        std::cout << "Claw is closed. Opening it." << '\n';
        msg.data = mearm.clawOpen();
        claw.publish(msg);
      }

    }
    else if(request == 5){
      break;
    }


    ros::spinOnce();
  }


  return 0;
}




/**
 * This is a message object. You stuff it with data, and then publish it.
 */
/*std_msgs::String msg;

std::stringstream ss;
ss << "hello worlds " << count;
msg.data = ss.str();

ROS_INFO("%s", msg.data.c_str());

/**
 * The publish() function is how you send messages. The parameter
 * is the message object. The type of this object must agree with the type
 * given as a template parameter to the advertise<>() call, as was done
 * in the constructor above.
 */
/*chatter_pub.publish(msg);

ros::spinOnce();

loop_rate.sleep();
++count;*/
