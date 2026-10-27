#include <chrono>
#include <functional>
#include <memory>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("temp_talker"),
      rng_(std::random_device{}()),
      dist_(20.0f, 35.0f) 
    {
      publisher_ = this->create_publisher<std_msgs::msg::Float32>("temperature", 10);
      timer_ = this->create_wall_timer(
        500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::Float32();
      message.data = dist_(rng_); 

      RCLCPP_INFO(this->get_logger(), "Published temperature: '%.2f'", message.data);
      publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;

    std::mt19937 rng_;
    std::uniform_real_distribution<float> dist_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}