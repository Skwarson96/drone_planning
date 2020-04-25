#pragma once

#include <sensor_msgs/point_cloud_conversion.h>
#include <boost/foreach.hpp>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseWithCovariance.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <octomap_msgs/Octomap.h>
#include <octomap/octomap.h>
#include <sensor_msgs/PointCloud2.h>
#include <nav_msgs/Path.h>

#include <octomap_ros/conversions.h>
#include <grid_map_octomap/GridMapOctomapConverter.hpp>
#include <grid_map_octomap/grid_map_octomap.hpp>
#include <moveit/ompl_interface/ompl_interface.h>
#include <ompl/geometric/planners/rrt/RRTConnect.h>
#include <ompl/geometric/planners/prm/LazyPRMstar.h>
#include <ompl/base/spaces/RealVectorStateSpace.h>

// Eigen
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

// Octomap conversions
#include <drone_planning/conversions.h>

// Boost
#include <boost/thread.hpp>

//standard
#include <mutex>
#include <iostream>
#include <thread>
#include <fstream>
#include <iomanip>


namespace drone_planning{

class Planner3D
{
public:
    /*!
     * Constructor
     * @param nodeHandle the ros node Handle.
     */
    Planner3D(ros::NodeHandle& _nodeHandle);

    /*!
    * Destructor
    */
    virtual ~Planner3D();

    /*!
     * plan path
     * @param globalOctoMap Octomap of enviroment
     * @param globalPointCloud point cloud of enviroment
     */
    nav_msgs::Path planPath(const octomap_msgs::Octomap& globalOctoMap, const sensor_msgs::PointCloud2& globalPointCloud );

private:
    /// node handle
    ros::NodeHandle& nodeHandle;
};

}
