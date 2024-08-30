cmake_minimum_required(VERSION 3.8)
project(camera_pack)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package( QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package( Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
set( TS_FILES Qtview01_zh_CN.ts)






if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package( ament_cmake REQUIRED)


# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

# find_package(PkgConfig REQUIRED)
# pkg_check_modules(MYLIB REQUIRED rclcpp)  没有pc文件 无法find

# include(GNUInstallDirs)
# find_package(
#   roscpp
#   rclcpp
#   std_msgs
#   REQUIRED
# )

# 查找依赖包
# 手动新增的 pack 在XMl里配置
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

find_package(OpenCV REQUIRED)
find_package(octomap REQUIRED)
# set(CMAKE_PREFIX_PATH "/opt/ros/humble")

# find_library(TESTROS2_LIB rclcpp HINTS
#     ${rclcpp_INCLUDE_DIRS}/rclcpp  )



message(DEPRECATION " 555${OpenCV_LIBS}555 " )

# 连接目录 指定头文件的搜索路径。    配置重复 无法读取
# include_directories(
#     ${rclcpp_INCLUDE_DIRS}
#     ${std_msgs_INCLUDE_DIRS}

# )

# 添加可执行文件
add_executable( camera_ros2_opencv4
./src/camera_ros2_opencv4.cpp  )

# add_executable(camera_ros2_opencv4
#     ${PROJECT_SOURCES}
# )       QT生成的

# 链接依赖
ament_target_dependencies(camera_ros2_opencv4 rclcpp std_msgs)

# 连接库  可执行文件或库
target_link_libraries( camera_ros2_opencv4
    ${OpenCV_LIBS}
    ${octomap_LIBS}

    ${rclcpp_LIBRARIES}
    ${std_msgs_LIBRARIES}
)


# 目标的包含目录     INTERFACE 接口 interface   CURRENT current 当前
target_include_directories(camera_ros2_opencv4 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>

)
# 指定目标所需的编译特性。
# target_compile_features(camera_ros2_opencv4 PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

# 安装目标
install(TARGETS camera_ros2_opencv4
  DESTINATION lib/${PROJECT_NAME})



if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)

  ament_lint_auto_find_test_dependencies()
endif()


# 其他设置
ament_package()
