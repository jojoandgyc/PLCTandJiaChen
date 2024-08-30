#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <usb_cam/usb_cam.hpp>
// #include <../include/usb_camera_node/usb_cam.hpp>

class UsbCameraNode : public rclcpp::Node
{
public:
    UsbCameraNode() : Node("usb_camera_node")
    {

        this->get_logger().set_level(rclcpp::Logger::Level::Debug);

        // 创建图像发布者
        image_publisher_ = this->create_publisher<sensor_msgs::msg::Image>(
            "/usb_cam/image_raw", 888880);



        this->usb_cam_instance =new usb_cam::UsbCam();
        // 创建 USB 摄像头实例
        // this->usb_cam_instance = std::make_shared<usb_cam::UsbCam>();

        // 加载参数
        this->declare_parameter<std::string>("device", "/dev/video0");
        this->declare_parameter<int>("image_width", 640);
        this->declare_parameter<int>("image_height", 480);
        this->declare_parameter<int>("framerate", 500);
        this->declare_parameter<std::string>("pixel_format", "yuyv");

        // std::string video_device = "/dev/video0";
        // std::string io_method = "mmap";
        // std::string pixel_format = "yuyv";
        // int image_width = 640;
        // int image_height = 480;
        // int framerate = 30;





        RCLCPP_INFO(this->get_logger() ,"111s22" );


        try{
             usb_cam_instance->start();
            // usb_cam_instance_->start(video_device.c_str(), io_method.c_str(),
            //                           pixel_format.c_str(),
            //                          image_width, image_height, framerate);
        }
        catch (const std::runtime_error &e) {
            RCLCPP_ERROR(this->get_logger(), "Runtime error: %s", e.what());
        } catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Standard exception: %s", e.what());
        } catch (...) {
            RCLCPP_ERROR(this->get_logger(), "An unknown error occurred.");
        }

        RCLCPP_INFO(this->get_logger() ," abcd123 " );
        // 设置定时器定期发布图像
        // timer_ = this->create_wall_timer( std::chrono::milliseconds(300)
        //                                  ,std::bind(&UsbCameraNode::publish_image, this));
        try {
            timer_ = this->create_wall_timer(
                std::chrono::milliseconds(300),
                std::bind(&UsbCameraNode::publish_image, this)
                );
        } catch (const std::runtime_error &e) {
            RCLCPP_ERROR(this->get_logger(), "Runtime error: %s", e.what());
        }

    }

private:
    void publish_image()
    {

        // sensor_msgs::msg::Image::UniquePtr image_msg(new sensor_msgs::msg::Image());

        // usb_cam_instance_->grab_image(image_msg->data);

        // // Fill the image message
        // image_msg->header.stamp = this->get_clock()->now();
        // image_msg->header.frame_id = "camera_frame";
        // image_msg->height = usb_cam_instance_->get_height();
        // image_msg->width = usb_cam_instance_->get_width();
        // image_msg->encoding = "yuyv";
        // image_msg->is_bigendian = false;
        // image_msg->step = usb_cam_instance_->get_width() * 2; // YUYV format





        // auto message = std::make_shared<sensor_msgs::msg::Image>();

        // Capture or generate your image data here
        // cv::Mat frame = cv::imread("/path/to/your/image.jpg"); // For example, read an image from file

        // if (frame.empty()) {
        //     RCLCPP_ERROR(this->get_logger(), "Failed to load image");
        //     return;
        // }

        // Fill the sensor_msgs::msg::Image message
        // message->header.stamp = this->get_clock()->now();
        // message->header.frame_id = "camera_frame";
        // message->height = frame.rows;
        // message->width = frame.cols;
        // message->encoding = "bgr8"; // or "mono8", "rgb8", etc.
        // message->is_bigendian = false;
        // message->step = static_cast<sensor_msgs::msg::Image::_step_type>(frame.step);

        // // Copy data to the image message
        // size_t size = frame.step * frame.rows;
        // message->data.resize(size);
        // memcpy(&message->data[0], frame.data, size);


        // 获取图像消息
        // 假设 usb_cam_instance.get_image() 返回 char* 和图像的宽高
        char* image_data = usb_cam_instance->get_image();
        RCLCPP_ERROR(this->get_logger() ,"111222 %s aa" , image_data);

        int width = 500 /* 获取图像宽度 */;
        int height = 500 /* 获取图像高度 */;

        // 创建 Image 消息
        auto msg = std::make_shared<sensor_msgs::msg::Image>();
        msg->header.stamp = this->get_clock()->now();  // 设置时间戳
        msg->height = height;
        msg->width = width;
        msg->encoding = "jpeg";  // 根据你的图像格式设置
        msg->is_bigendian = 0;  // 小大端序
        msg->step = width * 3;  // 根据通道数设置步长 表示每一行图像数据的字节数
                                //值等于每行的像素宽度乘以每个像素的字节数
        //每个像素通常占用 3 个字节（红、绿、蓝），因此 step 可以计算为 width * 3。
        msg->data.assign(image_data, image_data + (width * height * 3));  // 假设是 RGB 格式



        if (msg) {
            // 发布图像消息
            image_publisher_->publish(*msg);
        }
    }

    // 发布者和定时器
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    usb_cam::UsbCam* usb_cam_instance;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);  // 初始化ROS 2
    rclcpp::spin(std::make_shared<UsbCameraNode>());  // 运行节点
    rclcpp::shutdown();  // 关闭ROS 2
    return 0;
}
