cmake_minimum_required(VERSION 3.8)
project(test_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Num.msg"
  "msg/Sphere.msg"
  "msg/LaserData.msg"
  "srv/AddThreeInts.srv"
  "srv/MulThreeInts.srv"
  DEPENDENCIES geometry_msgs std_msgs
)

rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")

add_executable(hello_world_node src/hello_world.cpp)
add_executable(hello_world_1Hz src/hello_world_1Hz.cpp)
add_executable(talker src/talker.cpp)
add_executable(listener src/listener.cpp)
add_executable(laser_publisher src/laser_publisher.cpp)
add_executable(laser_subscriber src/laser_subscriber.cpp)
add_executable(temp_talker src/temp_talker.cpp)
add_executable(temp_listener src/temp_listener.cpp)
add_executable(server_2 src/add_two_ints_server.cpp)
add_executable(client_2 src/add_two_ints_client.cpp)
add_executable(server_3 src/add_3_ints_server.cpp)
add_executable(client_3 src/add_3_ints_client.cpp)
add_executable(server_mul src/mul_3_ints_server.cpp)
add_executable(client_mul src/mul_3_ints_client.cpp)

ament_target_dependencies(hello_world_node rclcpp)
ament_target_dependencies(hello_world_1Hz rclcpp)
ament_target_dependencies(talker rclcpp std_msgs)
ament_target_dependencies(listener rclcpp std_msgs)
ament_target_dependencies(laser_publisher rclcpp)
ament_target_dependencies(laser_subscriber rclcpp)
ament_target_dependencies(temp_talker rclcpp std_msgs)
ament_target_dependencies(temp_listener rclcpp std_msgs)
ament_target_dependencies(server_2 rclcpp example_interfaces)
ament_target_dependencies(client_2 rclcpp example_interfaces)
ament_target_dependencies(server_3 rclcpp example_interfaces)
ament_target_dependencies(client_3 rclcpp example_interfaces)
ament_target_dependencies(server_mul rclcpp example_interfaces)
ament_target_dependencies(client_mul rclcpp example_interfaces)

target_link_libraries(laser_subscriber "${cpp_typesupport_target}")
target_link_libraries(laser_publisher "${cpp_typesupport_target}")
target_link_libraries(server_3 "${cpp_typesupport_target}")
target_link_libraries(client_3 "${cpp_typesupport_target}")
target_link_libraries(server_mul "${cpp_typesupport_target}")
target_link_libraries(client_mul "${cpp_typesupport_target}")

install(TARGETS hello_world_node DESTINATION lib/${PROJECT_NAME})
install(TARGETS hello_world_1Hz DESTINATION lib/${PROJECT_NAME})
install(TARGETS talker DESTINATION lib/${PROJECT_NAME})
install(TARGETS listener DESTINATION lib/${PROJECT_NAME})
install(TARGETS laser_publisher DESTINATION lib/${PROJECT_NAME})
install(TARGETS laser_subscriber DESTINATION lib/${PROJECT_NAME})
install(TARGETS temp_talker DESTINATION lib/${PROJECT_NAME})
install(TARGETS temp_listener DESTINATION lib/${PROJECT_NAME})
install(TARGETS server_2 DESTINATION lib/${PROJECT_NAME})
install(TARGETS client_2 DESTINATION lib/${PROJECT_NAME})
install(TARGETS server_3 DESTINATION lib/${PROJECT_NAME})
install(TARGETS client_3 DESTINATION lib/${PROJECT_NAME})
install(TARGETS server_mul DESTINATION lib/${PROJECT_NAME})
install(TARGETS client_mul DESTINATION lib/${PROJECT_NAME})

install(PROGRAMS scripts/hello.py DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

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
