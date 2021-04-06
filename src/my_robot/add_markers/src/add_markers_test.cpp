#include "ros/ros.h"
#include <visualization_msgs/Marker.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <iostream>
#include <string>
using namespace std;

bool pick_up_ = false;
bool delivery_ = true;
float pos_x=0;
float pos_y = 0;
float pos_z =0;
float orientation_w = 0;


visualization_msgs::Marker Crear_cubo(double pos_x = 0.0, double pos_y = 0.0, double pos_z = 0.0,
                                        double ori_x= 0.0 ,double ori_y = 0.0,double ori_z = 0.0,
                                        double ori_w = 1.0, string ns = "basic_shapes", int id = 0){
    uint32_t shape = visualization_msgs::Marker::CUBE;

    visualization_msgs::Marker marker;
        // Frame_ID y huella de tiempo.
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time::now()    ;
        // Id y nombre del marcador
        marker.ns = ns;
        marker.id = id;

        // Darle la forma al marcador
        marker.type = shape;

        marker.pose.position.x = pos_x;
        marker.pose.position.y = pos_y;
        marker.pose.position.z = pos_z;
        marker.pose.orientation.x = ori_x;
        marker.pose.orientation.y = ori_y;
        marker.pose.orientation.z = ori_z;
        marker.pose.orientation.w = ori_w;

        // Escala del marcador; dado en metros
        marker.scale.x = 0.10;
        marker.scale.y = 0.10;
        marker.scale.z = 0.10;

        // Ajustar el color

        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0f;

        marker.lifetime = ros::Duration();

        return marker;
}

visualization_msgs::Marker Mostrar_cubo(visualization_msgs::Marker marker){
    marker.action = visualization_msgs::Marker::ADD;
    return marker;
}

visualization_msgs::Marker Eliminar_cubo(visualization_msgs::Marker marker){
    marker.action = visualization_msgs::Marker::DELETE;
    return marker;
}

visualization_msgs::Marker cambiar_pos(visualization_msgs::Marker marker, double pos_x = 0.0, double pos_y = 0.0,
 double pos_z = 0.0){
        marker.pose.position.x = pos_x;
        marker.pose.position.y = pos_y;
        marker.pose.position.z = pos_z;

        return marker;


}


void odometry_callback(nav_msgs::Odometry odom){
    pos_x = odom.pose.pose.position.x;
    pos_y = odom.pose.pose.position.y;
    pos_z = odom.pose.pose.position.z;
    orientation_w = odom.pose.pose.orientation.w;

}


 int main( int argc, char** argv ){

    ros::init(argc, argv, "markers_example");
    ros::NodeHandle n;
    ros::Rate r(10);
    ros::Publisher marker_pub;
    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 2);
    sleep(5);
    ros::Subscriber odom_sub = n.subscribe("odom", 10, odometry_callback);

visualization_msgs::Marker pick_up = Crear_cubo(2.357, -2.33988, 0.01,  0.0 , 0.0 , 0.0, 1.0, "pick_up", 0);
visualization_msgs::Marker delivery = Crear_cubo(-2.21858,  5.80944, 0.01, 0.0 , 0.0 , 0.0, 1.0, "delivery", 1);

    while (ros::ok())
    {
            pick_up = Mostrar_cubo(pick_up);
            marker_pub.publish(pick_up); 
            sleep(5);
            pick_up = Eliminar_cubo(pick_up);
            marker_pub.publish(pick_up); 

            delivery = Mostrar_cubo(delivery);
            marker_pub.publish(delivery);
            sleep(5); 
            delivery = Eliminar_cubo(delivery);
            marker_pub.publish(delivery);
            break;
    }


    return 0;
    
}




