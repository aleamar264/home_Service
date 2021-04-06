#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <visualization_msgs/Marker.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

  double pos_x_pick_up = 2.357;
  double pos_y_pick_up = -2.33988;
  double pos_x_delivery = -2.21858;
  double pos_y_delivery = 5.80944;

  bool delivery = false;
  bool pick_up = true;




double pos_x;
double pos_y;
double pos_z;
// double orientation_x  ;
// double orientation_y  ;
// double orientation_z  ;
double orientation_w  ;

// void marker_callback(visualization_msgs::Marker marker){
//  pos_x = marker.pose.position.x;
//  pos_y = marker.pose.position.x;
//  pos_z = marker.pose.position.x;
//  orientation_x = marker.pose.orientation.x;
//  orientation_y = marker.pose.orientation.y;
//  orientation_z = marker.pose.orientation.z;
//  orientation_w = marker.pose.orientation.w;

 
//  ROS_INFO("pos del marcador x %1.2f, y %1.2f ", (float)pos_x, (float) pos_y);
//   ROS_INFO("Recivido la posicion del objetivo ");
// }


void odometry_callback(nav_msgs::Odometry odom){
  
    pos_x = odom.pose.pose.position.x;
    pos_y = odom.pose.pose.position.y;
    pos_z = odom.pose.pose.position.z;
    orientation_w = odom.pose.pose.orientation.w;

}

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;
  ros::Rate loop_rate(10);
  // ros::Subscriber pos_object = n.subscribe("visualization_marker", 2, marker_callback);
      ros::Subscriber odom_sub = n.subscribe("odom", 10, odometry_callback);
  sleep(6);
  ROS_INFO("Esperando marcador ");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;





  while(ros::ok()){
      //we'll send a goal to the robot to move 1 meter forward
      goal.target_pose.header.frame_id = "map";
      goal.target_pose.header.stamp = ros::Time::now();


      if(pick_up){
        ROS_INFO("Enviando pos de recogida");
        goal.target_pose.pose.position.x = pos_x_pick_up;
        goal.target_pose.pose.position.y = pos_y_pick_up;
        goal.target_pose.pose.orientation.w = 1;
        goal.target_pose.pose.orientation.x = 0;
        goal.target_pose.pose.orientation.y = 0;
        goal.target_pose.pose.orientation.z = 0;
      }



      if(pos_x <= 2.60 &&  pos_x > 2.27 && pos_y <= 2.45 &&  pos_y > 2.15 ){
        sleep(5);
          pick_up = false;
          delivery = true;
          ROS_INFO("El robot ha llegado a la zona de recogida");
        }

      if(delivery){
        ROS_INFO("Enviando pos delivery");
        goal.target_pose.pose.position.x = pos_x_delivery;
        goal.target_pose.pose.position.y = pos_y_delivery;
        goal.target_pose.pose.orientation.w = 1;
        goal.target_pose.pose.orientation.x = 0;
        goal.target_pose.pose.orientation.y = 0;
        goal.target_pose.pose.orientation.z = 0;
      }


      if(pos_x < -5.5 &&  pos_x >= -5.9 && pos_y >= -2.2 &&  pos_y < -2.10  ){
          ROS_INFO("El robot ha llegado a la zona de entrega");
          delivery = false;
          sleep(5);
          }


      ROS_INFO("Sending goal");
      ac.sendGoal(goal);

      ac.waitForResult();

      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        {ROS_INFO("Hooray, the base moved 1 meter forward");}
      else
        {ROS_INFO("The base failed to move forward 1 meter for some reason");}
      
      
      ros::spinOnce();
      loop_rate.sleep();

  }



  return 0;
}
