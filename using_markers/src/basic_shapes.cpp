#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main (int argc, char** argv)
{
	ros::init(argc,argv,"basic_shapes");
	ros::NodeHandle n;
	ros::Rate r(1);
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
	
	uint32_t shape = visualization_msgs::Marker::SPHERE;

	float xxx = 0.0;
	float yyy = 0.0;
	float zzz = 0.0;

	uint8_t radius = 3;

	while(ros::ok())
	{
		visualization_msgs::Marker marker;
	
		//Set frame ID and Timestamp (look at TF tutorials
		marker.header.frame_id = "/map";
		marker.header.stamp = ros::Time::now();

		//declare namespace and id
		marker.ns = "basic_shapes";
		marker.id = 0;
		
		//Set type of marker
		marker.type = shape;

		//Action for marker, ADD, DELETE or DELETEALL
		 marker.action = visualization_msgs::Marker::ADD;

		//Set position
		marker.pose.position.x = xxx;
		marker.pose.position.y = yyy;
		marker.pose.position.z = zzz;
		marker.pose.orientation.x = 0;
		marker.pose.orientation.y = 0;
		marker.pose.orientation.z = 0;
		marker.pose.orientation.w = 1.0;

		//Colour
		marker.color.r = 0.0f;
		marker.color.g = 1.0f;
		marker.color.b = 0.0f;
		marker.color.a = 1.0f;

		//Scale
		marker.scale.x = 0.25;
		marker.scale.y = 0.25;
		marker.scale.z = 0.25;

		//How long the marker exists for
		marker.lifetime = ros::Duration();

		while (marker_pub.getNumSubscribers() < 1)
		{
			if(!ros::ok())
			{
				return 0;
			}
			
			ROS_WARN_ONCE("Please create a subscriber to the marker");
			sleep(1);
		}
		marker_pub.publish(marker);

		xxx = radius - (static_cast <float> (rand())/static_cast<float>(RAND_MAX/(radius*2)));
		yyy = radius - (static_cast <float> (rand())/static_cast<float>(RAND_MAX/(radius*2)));
		r.sleep();
	}
}
