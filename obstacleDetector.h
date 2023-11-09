#ifndef OBSTACLE_DETECTOR_H
#define OBSTACLE_DETECTOR_H


#include <sensor_msgs/LaserScan.h>

class ObstacleDetector {
public:
    ObstacleDetector();
    bool isObstacleClose(const sensor_msgs::LaserScan::ConstPtr& scan);
    double nearestObstacleDistance(const sensor_msgs::LaserScan::ConstPtr& scan);

private:
    double closest_reading_ = std::numeric_limits<double>::infinity();
};

#endif // OBSTACLE_DETECTOR_H
