#!/usr/bin/env python3
import rclpy, time
from std_msgs.msg import String

rclpy.init()
node = rclpy.create_node('python_hello_node')

while rclpy.ok():
    node.get_logger().info('Hello World')
    time.sleep(1)