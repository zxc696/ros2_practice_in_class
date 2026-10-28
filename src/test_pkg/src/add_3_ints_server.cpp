#include "rclcpp/rclcpp.hpp"
#include "test_pkg/srv/add_three_ints.hpp"

#include <memory>

void add(const std::shared_ptr<test_pkg::srv::AddThreeInts::Request> request,
          std::shared_ptr<test_pkg::srv::AddThreeInts::Response>      response)
{
  response->sum = request->a * request->b * request->c;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld" " c: %ld",
                request->a, request->b, request->c);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("mul_3_ints_server");

  rclcpp::Service<test_pkg::srv::AddThreeInts>::SharedPtr service =
    node->create_service<test_pkg::srv::AddThreeInts>("add_3_ints", &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add 3 ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}