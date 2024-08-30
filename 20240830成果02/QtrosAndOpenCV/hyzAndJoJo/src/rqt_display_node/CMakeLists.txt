cmake_minimum_required(VERSION 3.8)
project(rqt_display_node)


# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)





if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package( QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package( Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set( PROJECT_SOURCES
     #   main.cpp
      #  mainwindow.cpp
     #   mainwindow.h
       # mainwindow.ui
       # ${TS_FILES}
)


# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

# set(CMAKE_PREFIX_PATH "/opt/ros/humble")

# find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)

# find_file(include/aaaa.h)
# find_path(include/rqt_display_node)

# find_package(rqt_display_node REQUIRED)




# find_package(rqt_gui REQUIRED)
find_package(rqt_gui_cpp REQUIRED)
# find_dependency()
# find_file(camera_pack rqt_display_node.h PATHS
#     ./include/)
# set(rqt_display_node_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
# set(rqt_display_node_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# set(rqt_display_node_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

# ${cv_bridge_INCLUDE_DIRS}   ${rqt_display_node_INCLUDE_DIRS} ./include
include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}/include

)

# set_target_properties(Qtview01 PROPERTIES
#     ${BUNDLE_ID_OPTION}
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )



#                     空的
#message( "555${include}555 " )
#/root/Desktop/QtrosAndOpenCV/hyzAndJoJo/   src    /rqt_display_node
#message( "57${CMAKE_CURRENT_SOURCE_DIR}/include555 " )
#/root/Desktop/QtrosAndOpenCV/hyzAndJoJo/   build   /rqt_display_node
#message( "58${rqt_display_node_INCLUDE_DIRS}555 " )

# add_library(rqt_display_node src/rqt_display_node.cpp)

ament_include_directories_order(
  camera_pack
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ./include/
    ${CMAKE_CURRENT_SOURCE_DIR}/include

)


# add_library(${PROJECT_NAME} src/rqt_display_node.cpp)
add_executable(camera_pack src/rqt_display_node.cpp)

    # ./include/rqt_display_node/rqt_display_node.h
    # ./include/aaaa.h
    # rclcpp
    # sensor_msgs
    # cv_bridge
    # OpenCV
    # ${CMAKE_CURRENT_SOURCE_DIR}

target_link_libraries(camera_pack PUBLIC
    # Qt${QT_VERSION_MAJOR}::Widgets
    # Qt${QT_VERSION_MAJOR}::Core
    # Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBRARIES}
    ${rclcpp_LIBRARIES})

# qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})


ament_target_dependencies(camera_pack PUBLIC
  rclcpp
  sensor_msgs
  # rqt_display_node
  # ${CMAKE_CURRENT_SOURCE_DIR}
  # rqt_display_node
  # rqt_gui
  # rqt_gui_cpp
  cv_bridge
  OpenCV
)
target_include_directories(camera_pack PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  # ${CMAKE_CURRENT_SOURCE_DIR}/include
  # ./include
  # /include
)
target_compile_features(camera_pack PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS camera_pack
  DESTINATION lib/${PROJECT_NAME}
  # BUNDLE DESTINATION .
  # LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  # RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# install(TARGETS Qtview01
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )



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




# include(GNUInstallDirs)




ament_package()
