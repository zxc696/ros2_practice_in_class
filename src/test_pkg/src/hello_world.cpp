#include "rclcpp/rclcpp.hpp"

int main(int argc, char **argv){
    rclcpp::init(argc, argv); // ros2 node initialize

    auto node = rclcpp::Node::make_shared("hello_world_node"); // create Node

    if (argc == 1){
        RCLCPP_INFO(node->get_logger(), "hello world"); // Output, hello world
    }
    else if (argc == 2){
        RCLCPP_INFO(node->get_logger(), "hello %s !", argv[1]);
    }
    else if (argc == 3){
        RCLCPP_INFO(node->get_logger(), "hello %s and %s !", argv[1], argv[2]);
    }
    else{
        RCLCPP_INFO(node->get_logger(), "too long!");
    }

    rclcpp::shutdown();
    return 0;
}
