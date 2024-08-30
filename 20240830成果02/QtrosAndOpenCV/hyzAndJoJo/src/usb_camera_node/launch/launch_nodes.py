import launch
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # 启动摄像节点
        Node(
            package='usb_camera_node',
            executable='usb_camera_node',
            output='screen',
        ),

        # 启动OpenCV节点
        Node(
            package='opencv_node',
            executable='opencv_node',
            output='screen',
        ),

        # 启动rqt节点
        Node(
            package='rqt_display_node',
            executable='rqt_display_node',
            output='screen',
        ),
    ])
