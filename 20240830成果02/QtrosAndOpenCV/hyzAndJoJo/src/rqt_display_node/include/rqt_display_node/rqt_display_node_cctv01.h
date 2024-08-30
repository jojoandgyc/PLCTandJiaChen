// #pragma once
#ifndef RQT_DISPLAY_NODE_H
#define RQT_DISPLAY_NODE_H


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

// class RqtDisplayNode : public rqt_gui_cpp::Plugin
// {
//     Q_OBJECT

// public:
//     RqtDisplayNode();
//     ~RqtDisplayNode();
//     // void initPlugin(qt_gui_cpp::PluginContext &context) override;
//     void  shutdownPlugin() override;
// // signals:
// //     void imageReceived(const sensor_msgs::msg::Image::SharedPtr &msg);

// // public slots:
// //     void processImage(const sensor_msgs::msg::Image::SharedPtr &msg);

// private:
//     void image_callback(const sensor_msgs::msg::Image::SharedPtr msg);
//     rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber_;
//     QLabel *image_label_;
//     std::shared_ptr<rclcpp::Node> node_;
// };
#endif // RQT_DISPLAY_NODE_H
