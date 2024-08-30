cmake_minimum_required(VERSION 3.8)
project(usb_camera_node)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()








# # 设置 FFmpeg 的路径
# set(FFMPEG_INCLUDE_DIR "/usr/include/ffmpeg")
# set(FFMPEG_LIB_DIR "/usr/lib")

# # 添加头文件搜索路径
# include_directories(${FFMPEG_INCLUDE_DIR})


#pkg_check_modules(AVCODEC REQUIRED libavcodec)


find_package(PkgConfig REQUIRED)



# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.

# find_package(PkgConfig REQUIRED)
# pkg_check_modules(FFmpeg REQUIRED IMPORTED_TARGET libavcodec libavformat libavutil)
# target_link_libraries(your_target PkgConfig::FFmpeg)

#sudo find / -iname "FFmpegConfig.cmake" -o -iname "ffmpeg-config.cmake" -o -iname "*FFmpegConfig*"


#colcon build --symlink-install
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(usb_cam REQUIRED)

# find_package(FFmpeg REQUIRED)

set(FFMPEG_LIB_DIR "/usr/lib64/")
# set(FFmpeg_DIR "/usr/lib64/")
# find_package(FFmpeg REQUIRED)
pkg_check_modules(avutil REQUIRED libavutil)
pkg_check_modules(avcodec REQUIRED libavcodec)
pkg_check_modules(avformat REQUIRED libavformat)
pkg_check_modules(swscale REQUIRED libswscale)
# pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET libavcodec libavformat libavutil)

# pkg_check_modules(FFmpeg REQUIRED IMPORTED_TARGET libavcodec libavformat libavutil)

#${CMAKE_CURRENT_SOURCE_DIR}/include

# message(STATUS "1111$<include>22${include}33")

# set(YAML_CPP_INCLUDE_DIR "/usr/include/yaml-cpp")
# message(ST "1111${YAML_CPP_INCLUDE_DIR}3333")
# include_directories(${YAML_CPP_INCLUDE_DIR})

# include_directories(include)
# include_directories(camera_pack)
add_executable(camera_pack src/usb_camera_node.cpp

)
ament_target_dependencies(camera_pack
  rclcpp
  sensor_msgs
  usb_cam
)



target_include_directories(camera_pack PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>

  ${FFmpeg_INCLUDE_DIRS}
  ${avcodec_INCLUDE_DIRS}

)


target_link_libraries(camera_pack

  ${FFMPEG_LIB_DIR}/libavutil.so
  ${FFMPEG_LIB_DIR}/libavcodec.so
  ${FFMPEG_LIB_DIR}/libavformat.so
  ${FFMPEG_LIB_DIR}/libswscale.so
)



target_compile_features(camera_pack PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS camera_pack
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

ament_package()
