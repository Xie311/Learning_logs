from pymavlink import mavutil
import time
from OpenCV_detect import MAVLink_chassis_message
from OpenCV_detect import chassis_send

connect = mavutil.mavlink_connection("COM1", source_system=1, source_component=1)

# target_system = connect.target_system
# target_component = connect.target_component

# Define the structure for the chassis message
class MAVlink_message:
    def __init__(self):
        self.pos_x = 0.0
        self.pos_y = 0.0
        self.radius = 0.0
        self.theta = 0.0
        self.state = 0.0
        self.flag = 0.0


# Initialize the chassis message
chassis_msg = MAVLink_chassis_message(MAVlink_message)

# mission_request_list_message = connect.mav.mission_request_list_encode(target_system, target_component)

while True:
    chassis_msg.pos_x += 1
    chassis_msg.pos_y += 1

    # Encode the chassis message
    chassis_send(
        chassis_msg.timestamp,
        chassis_msg.pos_x,
        chassis_msg.pos_y,
        chassis_msg.radius,
        chassis_msg.theta,
        chassis_msg.state,
        chassis_msg.flag,
    )
    
    time.sleep(10)
