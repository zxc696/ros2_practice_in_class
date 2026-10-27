#include <chrono>
#include <functional>
#include <memory>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "test_pkg/msg/laser_data.hpp" 

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("laser_publisher"),
      rng_distance_(std::random_device{}()),
      rng_angle_(std::random_device{}()),
      dist_distance_(1.0f, 5.0f),
      dist_angle_(0.0f, 1.0f)
    {
      publisher_ = this->create_publisher<test_pkg::msg::LaserData>("laser_topic", 1);
      timer_ = this->create_wall_timer(
        500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      auto message = test_pkg::msg::LaserData();
      message.distance = dist_distance_(rng_distance_); 
      message.angle = dist_angle_(rng_angle_);
      message.frame_id = "laser_frame"; 

      RCLCPP_INFO(
        this->get_logger(),
        "Publishing laser data -> Distance: '%.2f' m, Angle: '%.3f' rad, FrameID: '%s'",
        message.distance,
        message.angle,
        message.frame_id.c_str()
      );

      publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<test_pkg::msg::LaserData>::SharedPtr publisher_;

    std::mt19937 rng_distance_;
    std::mt19937 rng_angle_;

    std::uniform_real_distribution<float> dist_distance_;
    std::uniform_real_distribution<float> dist_angle_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}