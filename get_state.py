#!/usr/bin/env python
import rospy
from std_msgs.msg import String


def callback(data):
    global state_pub
    state_pub.publish(data)


if __name__=="__main__":
    #get beaglebone data and send it to new topic "/openwearable_new"
    rospy.init_node('state_listener')
    rospy.Subscriber('/openwearable', String, callback)
    state_pub = rospy.Publisher('/openwearable_new', String, queue_size=10)
    rospy.spin()