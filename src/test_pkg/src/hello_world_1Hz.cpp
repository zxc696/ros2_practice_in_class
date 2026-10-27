#include "rclcpp/rclcpp.hpp"

int main(int argc, char **argv){
    rclcpp::init(argc, argv); // ros2 node initialize

    auto node = rclcpp::Node::make_shared("hello_world_1Hz"); // create Node

    rclcpp::Rate rate(1);
    rclcpp::Rate rate1(1);

    while(rclcpp::ok){
        RCLCPP_INFO(node->get_logger(), "hello world from loop_node");
        rate.sleep();
        RCLCPP_INFO(node->get_logger(), "hello world from loop_node10");
        rate1.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
