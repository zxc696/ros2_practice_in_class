#include "rclcpp/rclcpp.hpp"
#include "test_pkg/srv/mul_three_ints.hpp"

#include <memory>

void mul(const std::shared_ptr<test_pkg::srv::MulThreeInts::Request> request,
          std::shared_ptr<test_pkg::srv::MulThreeInts::Response>      response)
{
  response->product = request->a * request->b * request->c;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld" " c: %ld",
                request->a, request->b, request->c);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->product);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("mul_3_ints_server");

  rclcpp::Service<test_pkg::srv::MulThreeInts>::SharedPtr service =
    node->create_service<test_pkg::srv::MulThreeInts>("mul_3_ints", &mul);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to mul 3 ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}