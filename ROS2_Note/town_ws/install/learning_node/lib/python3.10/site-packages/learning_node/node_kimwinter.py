import rclpy
from rclpy.node import Node
import time

class Kim_Winter(Node):
    def __init__(self,name):
        super().__init__(name)
        while rclpy.ok():
            self.get_logger().info("Winter")
            time.sleep(1)

def main(args=None):
    rclpy.init(args=args)
    node = Kim_Winter("winter")
    #rclpy.spin(node)
    node.destroy_node()
    rclpy.destroy_node()