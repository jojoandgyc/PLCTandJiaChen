#include <cstdio>
#include <cv_bridge/cv_bridge.h>
// int main(int argc, char ** argv)

class OpenCVNode : public rclcpp::Node
{
public:
    OpenCVNode() : Node("opencv_node")
    {
        // 订阅来自摄像节点的图像话题
        image_subscriber_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/image_raw", 10,
            std::bind(&OpenCVNode::image_callback, this, std::placeholders::_1));

        // 创建图像发布者
        image_publisher_ = this->create_publisher<sensor_msgs::msg::Image>(
            "/my_processed_image", 30);
    }

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        // 将ROS图像消息转换为OpenCV图像
        cv_bridge::CvImagePtr cv_ptr;
        try
        {


            RCLCPP_DEBUG(this->get_logger(), "jr1  excep");
            cv_ptr = cv_bridge::toCvCopy(msg);
            RCLCPP_DEBUG(this->get_logger(), "cg2  excep");
        }
        catch (cv_bridge::Exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;  // 如果转换失败，返回
        }

        // 图像处理示例：将图像转换为灰度图
        cv::Mat processed_image;
        //cv::cvtColor(cv_ptr->image, processed_image, cv::COLOR_BGR2GRAY);

        // 将处理后的OpenCV图像转换回ROS图像消息
        sensor_msgs::msg::Image::SharedPtr output_msg = cv_bridge::CvImage(
                                                            std_msgs::msg::Header(),
                                                            sensor_msgs::image_encodings::YUV422,
                                                            processed_image).toImageMsg();

        RCLCPP_DEBUG(this->get_logger(), "fb1  excep");
        // 发布处理后的图像

        // 显示图像
        cv::imshow("Subscribed Image", cv_ptr->image);
        cv::waitKey(1);
        image_publisher_->publish(*output_msg);


        RCLCPP_DEBUG(this->get_logger(), "fbcg2  excep");
    }

    // 订阅者和发布者
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_publisher_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);  // 初始化ROS 2
    rclcpp::spin(std::make_shared<OpenCVNode>());  // 运行节点
    rclcpp::shutdown();  // 关闭ROS 2
    return 0;
}
