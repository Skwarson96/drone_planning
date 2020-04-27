
// ROS
#include <ros/ros.h>
#include "../include/drone_planning/drone_planning.hpp"

#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>


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



octomap_msgs::Octomap globalOctoMap; // To chyba przekazywac do funkcji z FCLa, bo to jest OcTree
sensor_msgs::PointCloud2 globalPointCloud; // Wspolrzedne zajetych voxeli
visualization_msgs::MarkerArray markerArray;

void octomapCallback(const octomap_msgs::OctomapPtr& octMap)
{

    globalOctoMap = *octMap;
    std::cout << "   " << "\n";
    std::cout << "globalMap Resolution: " << globalOctoMap.resolution << "\n";
    std::cout << "globalMap Binary: " << globalOctoMap.binary <<"\n";
    std::cout << "globalMap id: " << globalOctoMap.id << "\n";
    std::cout << "globalMap frameID: " << globalOctoMap.header.frame_id << "\n";



    //    for(int i=0; i < globalMap.data.size(); i++){
    //        std::cout << int(globalMap.data[i]) << "\n";
    //    }
}

void pointCloudCallback(const sensor_msgs::PointCloud2Ptr& cloud){

//    std::cout<<int(cloud.data[0])<< "\n";



    globalPointCloud = *cloud;
    std::cout << "   " << "\n";
    std::cout << "PointCloudFrameID: " << globalPointCloud.header.frame_id << "\n";
    std::cout << "PointCloudHeight: " << globalPointCloud.height << "\n";  ///Punkty sa unordered po height=1
    std::cout << "PointCloudWidth: " << globalPointCloud.width << "\n";



//    std::cout << int(globalPointCloud.data[0]) << "\n";
//    BOOST_FOREACH(const pcl::PointXYZ& pt, globalPointCloud.data)
}

void markerArrayCallback(const visualization_msgs::MarkerArrayPtr& mArray)
{
    markerArray = *mArray;


//    std::cout << "markerArray.markers.size: " << markerArray.markers.size() << "\n";
//    std::cout << "markerArray.markers[0].points.size(): " << markerArray.markers[0].points.size() << "\n";
//    for (int i=0; i<markerArray.markers.size(); i++)
//    {
//            std::cout << "markerArray.markers[i].points.size():" << markerArray.markers[i].points.size() << "\n";
//    }

}

int main(int argc, char **argv)
{
  // init ROS node
  ros::init(argc, argv, "drone_planner");

  // create node handler
  ros::NodeHandle node("~");
  drone_planning::Planner3D planner_(node);

  //setup ROS lopp rate
  ros::Rate loop_rate(1);

  //subscribers to full octomap, octomap point cloud and markerArray
  ros::Subscriber octomapFull_sub = node.subscribe("/octomap_full", 10, octomapCallback);
  ros::Subscriber octmapPointCloud_sub = node.subscribe("/octomap_point_cloud_centers", 10, pointCloudCallback); // Wspolrzedne zajetych voxeli
  ros::Subscriber occupied_cells_vis_array_sub = node.subscribe("/occupied_cells_vis_array", 10, markerArrayCallback);

  // path Publisher
  ros::Publisher path_pub = node.advertise<nav_msgs::Path>("my_path",1000);

  while (ros::ok()){
      nav_msgs::Path examplePath;

      // counting path
      examplePath = planner_.examplePath(globalOctoMap, globalPointCloud);

      // publishing path
      path_pub.publish(examplePath);

      ros::spinOnce();
      loop_rate.sleep();
}
    return 0;
//  ros::spin();
}
