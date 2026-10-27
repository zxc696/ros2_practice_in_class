#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp" 
#include "test_pkg/msg/laser_data.hpp" 

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("laser_subscriber")
    {
      subscription_ = this->create_subscription<test_pkg::msg::LaserData>(
        "laser_topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const test_pkg::msg::LaserData & LaserData) const
    {
      RCLCPP_INFO(this->get_logger(), "Received laser data -> Distance: '%.2f' m, Angle: '%.3f' rad, Frame: '%s'",
        LaserData.distance,
        LaserData.angle,
        LaserData.frame_id.c_str());
    }

    rclcpp::Subscription<test_pkg::msg::LaserData>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}