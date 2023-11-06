#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/Imu.h>
#include <sensors_project/sensors_msg.h> // this is your custom message



void callback(const sensor_msgs::Image::ConstPtr& img, const sensor_msgs::Imu::ConstPtr& imu, ros::Publisher pub)
{
    sensors_project::sensors_msg msg;
    msg.header.stamp = ros::Time::now();
    msg.image_header = img->header;
    msg.imu_header = imu->header;
    msg.rand = img->header.stamp.sec + imu->header.stamp.nsec;  // Assuming this is a random number, you can modify as needed.

    pub.publish(msg);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "sensors_example_node");
    ros::NodeHandle nh;
    
    message_filters::Subscriber<sensor_msgs::Image> image_sub(nh, "image", 1);
    message_filters::Subscriber<sensor_msgs::Imu> imu_sub(nh, "imu", 1);
    ros::Publisher custom_pub = nh.advertise<sensors_project::sensors_msg>("pub_topic", 100);
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Imu> SyncPolicy;
    message_filters::Synchronizer<SyncPolicy> sync(SyncPolicy(50), image_sub, imu_sub);
    sync.registerCallback(boost::bind(&callback, _1, _2, custom_pub));

    ros::spin();
    
    return 0;
}