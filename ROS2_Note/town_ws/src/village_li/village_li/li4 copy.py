import rclpy
from rclpy.node import Node
from std_msgs.msg import String,UInt32

class WriterNode(Node):
    def __init__(self,name):
        super().__init__(name)
        self.pub_novel=self.create_publisher(String,"girl",10)
        
        self.count=0
        
        self.timer_period=5
        self.timer=self.create_timer(self.timer_period,self.timer_callback)
        
        self_account=80
        
        self.sub_money=self.create_subscription(UInt32,"girl",self.recv_money_callback,10)
        
    def timer_callback(self):
        msg=String()
        msg.data="f'the theme of{self.count}"
        self.pub_novel.publish(msg)
        self.get_logger().info("f'publish {self.count} count of novel")
        self.count+=1
    
    def recv_money_callback(self,money):
        self.account+=money.data
        self.get_logger().info("f'now {self.account}")
        
        
def main(args=None):
    rclpy.init(args=args)
    li4_node=WriteNode('li4')
    rclpy.spin(li4_node)
    rclpy.shutdown()