#ifndef CAMERA_PACK_H
#define CAMERA_PACK_H
#include <cstdio>
#include <rclcpp/rclcpp/rclcpp.hpp>
#include <sensor_msgs/sensor_msgs/msg/image.hpp>
#include <rqt_gui_cpp/rqt_gui_cpp/plugin.h>


#include "pluginlib/pluginlib/class_list_macros.hpp"
// 导出插件

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <cv_bridge/cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
class Camera_pack : public rclcpp::Node
{
public:
   Camera_pack();
private:
   void image_callback(const sensor_msgs::msg::Image::SharedPtr msg);
   rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber_;
};
#endif // CAMERA_PACK_H
