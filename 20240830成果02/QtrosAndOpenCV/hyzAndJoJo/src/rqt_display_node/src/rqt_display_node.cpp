#include <rclcpp/rclcpp/rclcpp.hpp>
#include <sensor_msgs/sensor_msgs/msg/image.hpp>
// #include <rqt_gui_cpp/rqt_gui_cpp/plugin.h>


// #include "pluginlib/pluginlib/class_list_macros.hpp"
// 导出插件

// #include <QLabel>
// #include <QVBoxLayout>
// #include <QWidget>
#include <cv_bridge/cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
// #include <opencv2/opencv.hpp>
// #include "../include/rqt_display_node/camera_pack.h"
// #include "../include/rqt_display_node/rqt_display_node_cctv01.h"

class RqtDisplayNode : public rclcpp::Node
{
public:
    RqtDisplayNode() : Node("image_subscriber")
    {
        // 订阅 /imgwar 主题
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/my_processed_image", 10, std::bind(&RqtDisplayNode::topic_callback, this, std::placeholders::_1));

        // 发布 /image_topic 主题
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("/image_topic", 10);
    }

    // 在图像左上角绘制一个正方形
    void draw_triangle(cv_bridge::CvImagePtr cv_ptr)
    {
        // 获取图像的尺寸
        // int width = cv_ptr->image.cols;
        // int height = cv_ptr->image.rows;

        // 定义正方形的顶点
        cv::Point pt1(0, 0);             // 顶点1
        cv::Point pt2(0, 50);      // 顶点2
        cv::Point pt3(50, 50);     // 顶点3
        cv::Point pt4(50, 0);

        // 绘制正方形
        cv::line(cv_ptr->image, pt1, pt2, cv::Scalar(0, 255, 0), 2); // 绿色线条
        cv::line(cv_ptr->image, pt2, pt3, cv::Scalar(0, 255, 0), 2);
        cv::line(cv_ptr->image, pt3, pt4, cv::Scalar(0, 255, 0), 2);
        cv::line(cv_ptr->image, pt4, pt1, cv::Scalar(0, 255, 0), 2);
    }

private:
    void topic_callback( sensor_msgs::msg::Image::SharedPtr msg)
    {
        // 将ROS2图像消息转换为OpenCV图像
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge1 exception: %s", e.what());
            return;
        }

       // 绘制正方形
        draw_triangle(cv_ptr);
        // 显示图像
        cv::imshow("Subscribed Image", cv_ptr->image);
        cv::waitKey(1);

        // 发布图像到新的主题
        publisher_->publish(*msg);
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RqtDisplayNode>());
    rclcpp::shutdown();
    return 0;
}

// class RqtDisplayNode : public rqt_gui_cpp::Plugin
// {

//     Q_OBJECT
// public:

//     RqtDisplayNode() : rqt_gui_cpp::Plugin()
//     {
//         setObjectName("RqtDisplayNode");  // 设置插件名称
//     }

//     // ~RqtDisplayNode() override;
//     ~RqtDisplayNode() override {
//         // 清理代码
//     }
//     void  shutdownPlugin() override  {
//           // 清理代码
//     }




//     void passInNode(std::shared_ptr<rclcpp::Node> node) override
//     {
//         node_ = node;
//     }


//     // RqtDisplayNode::~RqtDisplayNode(){}

//  //   RqtDisplayNode::~RqtDisplayNode() {  }
//     // 插件初始化
//     void initPlugin(qt_gui_cpp::PluginContext &context)
//     {
//         // 创建插件界面
//         QWidget *widget = new QWidget();
//         QVBoxLayout *layout = new QVBoxLayout(widget);
//         image_label_ = new QLabel();  // 创建标签用于显示图像
//         layout->addWidget(image_label_);
//         context.addWidget(widget);  // 将插件添加到上下文中

//         // 订阅处理后的图像话题
//         // 创建节点的正确方式是通过 std::make_shared<rclcpp::Node>("node_name")
//         //


//         //image_subscriber_ = rclcpp::create_node("rqt_display_node")->create_subscription<sensor_msgs::msg::Image>(

//         // node01my = std::make_shared<Camera_pack>();

//         image_subscriber_ = node_1->create_subscription<sensor_msgs::msg::Image>(
//             "/my_processed_image", 10,
//             [this](const sensor_msgs::msg::Image::SharedPtr msg) {
//                 // 处理接收到的消息
//                 RCLCPP_INFO(this->node_->get_logger(), "Received image with width: %d", msg->width);

//                 // 将ROS图像消息转换为OpenCV图像
//                 cv_bridge::CvImagePtr cv_ptr;
//                 try
//                 {
//                     cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO8);
//                     // 显示图像
//                     cv::imshow("Processed Image", cv_ptr->image);
//                     cv::waitKey(1);  // 等待1毫秒以更新图像
//                 }
//                 catch (cv_bridge::Exception& e)
//                 {
//                     RCLCPP_ERROR(rclcpp::get_logger("rqt_display_node"), "cv_bridge exception: %s", e.what());
//                 }


//             }
//             );

//            // std::bind( &RqtDisplayNode::image_callback, this, std::placeholders::_1));

//         // image_subscriber_ =node01my.create_subscription<sensor_msgs::msg::Image>
//         //     ( "/my_processed_image", 10,
//         //     std::bind(&RqtDisplayNode::image_callback,
//         //               this, std::placeholders::_1));


//     }
// // signals:
// //     void imageReceived(const sensor_msgs::msg::Image::SharedPtr &msg);  // 定义信号

// // public slots:
// //     void processImage(const sensor_msgs::msg::Image::SharedPtr &msg);  // 定义槽
// private:

//     void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
//     {
//         // 将ROS图像消息转换为OpenCV图像
//         cv_bridge::CvImagePtr cv_ptr;
//         try
//         {
//             cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO8);
//             // 显示图像
//             cv::imshow("Processed Image", cv_ptr->image);
//             cv::waitKey(1);  // 等待1毫秒以更新图像
//         }
//         catch (cv_bridge::Exception& e)
//         {
//             RCLCPP_ERROR(rclcpp::get_logger("rqt_display_node"), "cv_bridge exception: %s", e.what());
//         }
//     }

//     // 订阅者和标签
//     rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber_;
//     // rclcpp::Node node01my;
//     // RqtDisplayNode mynode02;
//     std::shared_ptr<rclcpp::Node> node_1;  // 使用智能指针
//     QLabel *image_label_;

// };

// int main(int argc, char **argv)
// {
//     rclcpp::init(argc, argv);  // 初始化ROS 2
//     rclcpp::spin(std::make_shared<RqtDisplayNode>());  // 运行节点
//     rclcpp::shutdown();  // 关闭ROS 2
//     return 0;
// }


// PLUGINLIB_EXPORT_CLASS(RqtDisplayNode, rqt_gui_cpp::Plugin)
