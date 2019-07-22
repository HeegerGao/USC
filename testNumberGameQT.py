#!/usr/bin/env python
# encoding=utf8

#import modules
import random
import rospy
import os
import sys
import time
import string
from std_msgs.msg import String
from qt_robot_interface.srv import *
from qt_gesture_controller.srv import *
from std_msgs.msg import Float64MultiArray
from sensor_msgs.msg import JointState
from thumb.msg import Res
#include IMU, button, orthosis
import rosbag

#gesture choose
def choose_behaviors(number):
    global right_pub, left_pub, head_pub, emotionShow_pub, gesturePlay_pub, speechSay_pub, audioPlay_pub
    #talking:1~6
    if(number == 1):
    #show_both_hands:6.5s
        emotionShow_pub.publish("QT/talking")
        left_arm = Float64MultiArray()
        right_arm = Float64MultiArray()
        left_arm.data = [10, -60, -15]
        left_pub.publish(left_arm)
        time.sleep(2)
        right_arm.data = [-10, -60, -15]
        right_pub.publish(right_arm)
        time.sleep(2)
        left_arm.data = [90, -60, -30]
        left_pub.publish(left_arm)
        right_arm.data = [-90, -60, -30]
        right_pub.publish(right_arm)
        time.sleep(2.5)    
    elif(number == 2):
    #hold:5s
        gesturePlay_pub.publish("QT/show_QT")
        emotionShow_pub.publish("QT/talking")
        time.sleep(5)
    elif(number == 3):
    #challenge:5s
        gesturePlay_pub.publish("QT/challenge")
        emotionShow_pub.publish("QT/talking")
        time.sleep(5)
    elif(number == 4):
    #show left and right:10s
        gesturePlay_pub.publish("QT/show_left")
        emotionShow_pub.publish("QT/talking")
        time.sleep(5)
        gesturePlay_pub.publish("QT/show_right")
        emotionShow_pub.publish("QT/talking")
        time.sleep(5)
    elif(number == 5):
    #pointing:6s
        emotionShow_pub.publish("QT/talking")
        left_arm = Float64MultiArray()
        right_arm = Float64MultiArray()
        left_arm.data = [110, -60, -10]
        right_arm.data = [0, -90, -10]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(3.5)
        left_arm.data = [90, -60, -30]
        right_arm.data = [-90, -60, -30]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(2.5)   
    elif(number == 6):
    #point each:8.5s
        emotionShow_pub.publish("QT/talking")
        left_arm = Float64MultiArray()
        right_arm = Float64MultiArray()
        left_arm.data = [0, -90, -10]
        left_pub.publish(left_arm)
        time.sleep(2)
        left_arm.data = [90, -60, -30]
        left_pub.publish(left_arm)
        time.sleep(2)
        emotionShow_pub.publish("QT/talking")
        right_arm.data = [0, -90, -10]
        right_pub.publish(right_arm)
        time.sleep(2)
        right_arm.data = [-90, -60, -30]
        right_pub.publish(right_arm)
        time.sleep(2.5) 


    #listening:7~8
    elif(number == 7):
    #nod:4s
        head = Float64MultiArray()
        emotionShow_pub.publish("QT/showing_smile")
        head.data = [0,-10]
        head_pub.publish(head)
        time.sleep(1)
        head.data = [0,10]
        head_pub.publish(head)
        time.sleep(1)
        head.data = [0,0]
        head_pub.publish(head)
        time.sleep(2)
    elif(number == 8):
    #arm back smile:7s
        emotionShow_pub.publish("QT/calming_down")
        time.sleep(1)
        gesturePlay_pub.publish("QT/bored")
        time.sleep(6)    


    #guessing:9~11
    elif(number == 9):
    #confused:8s
        right_arm = Float64MultiArray()
        right_arm.data = [40, -60, -90]
        right_pub.publish(right_arm)
        time.sleep(2)
        emotionShow_pub.publish("QT/confused")
        time.sleep(2)
        right_arm.data = [-90, -60, -30]
        right_pub.publish(right_arm)
        time.sleep(4)
    elif(number == 10):
    #touch head:11s
        left_arm = Float64MultiArray()
        right_arm = Float64MultiArray()
        left_arm.data = [-80, -40,-80]
        right_arm.data = [80, -40,-80]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(3)
        emotionShow_pub.publish("QT/confused")
        left_arm.data = [-100, -40,-80]
        right_arm.data = [100, -40,-80]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [-80, -40,-80]
        right_arm.data = [80, -40,-80]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [-100, -40,-80]
        right_arm.data = [100, -40,-80]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [-80, -40,-80]
        right_arm.data = [80, -40,-80]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [90, -60,-30]
        right_arm.data = [-90, -60,-30]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(4)
    elif(number == 11):
    #thinking:10s
        left_arm = Float64MultiArray()
        right_arm = Float64MultiArray()
        left_arm.data = [-90, -50, -30]
        right_arm.data = [-90, -45, -90]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(3.5)
        emotionShow_pub.publish("QT/confused")
        left_arm.data = [-90, -70, -40]
        right_arm.data = [-90, -45, -90]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [-90, -50, -30]
        right_arm.data = [-90, -45, -90]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [-90, -70, -40]
        right_arm.data = [-90, -45, -90]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [-90, -50, -30]
        right_arm.data = [-90, -45, -90]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [90, -60, -30]
        right_arm.data = [-90, -60, -30]
        left_pub.publish(left_arm)
        right_pub.publish(right_arm)
        time.sleep(2.5)  


    #feedback and encouragement:12~15
    elif(number == 12):
    #surprise:5.5s
        gesturePlay_pub.publish("QT/surprise")
        emotionShow_pub.publish("QT/surprise")
        time.sleep(5.5)
    elif(number == 13):
    #happy:5s
        gesturePlay_pub.publish("QT/happy")
        emotionShow_pub.publish("QT/happy")
        time.sleep(5)
    elif(number == 14):
    #hug:6s
        left_arm = Float64MultiArray()
        right_arm = Float64MultiArray()
        emotionShow_pub.publish("QT/happy")
        left_arm.data = [-20, -10, -15]
        left_pub.publish(left_arm)
        right_arm.data = [20, -10, -15]
        right_pub.publish(right_arm)
        time.sleep(3)
        left_arm.data = [90, -60, -30]
        left_pub.publish(left_arm)
        right_arm.data = [-90, -60, -30]
        right_pub.publish(right_arm)
        time.sleep(3)
    elif(number == 15):
    #hand clap:8.8s
        left_arm = Float64MultiArray()
        right_arm = Float64MultiArray()
        emotionShow_pub.publish("QT/happy")
        left_arm.data = [10, -90, -30]
        left_pub.publish(left_arm)
        right_arm.data = [-10, -90, -30]
        right_pub.publish(right_arm)
        time.sleep(1.8)
        left_arm.data = [10, -90, -90]
        left_pub.publish(left_arm)
        right_arm.data = [-10, -90, -90]
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [10, -90, -30]
        left_pub.publish(left_arm)
        right_arm.data = [-10, -90, -30]
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [10, -90, -90]
        left_pub.publish(left_arm)
        right_arm.data = [-10, -90, -90]
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [10, -90, -30]
        left_pub.publish(left_arm)
        right_arm.data = [-10, -90, -30]
        right_pub.publish(right_arm)
        time.sleep(1)
        left_arm.data = [90, -60, -30]
        left_pub.publish(left_arm)
        right_arm.data = [-90, -60, -30]
        right_pub.publish(right_arm)
        time.sleep(3)


    #special_function:16~18
    elif(number == 16):
    #hi/bye:7s
        gesturePlay_pub.publish("QT/hi")
        emotionShow_pub.publish("QT/happy")
        time.sleep(7)
    elif(number == 17):
    #fly kiss:7.5s
        gesturePlay_pub.publish("QT/kiss")
        time.sleep(1)
        emotionShow_pub.publish("QT/kiss")
        time.sleep(6.5)
    elif(number == 18):
    #yawn:6.8s
        gesturePlay_pub.publish("QT/yawn")
        time.sleep(0.8)
        emotionShow_pub.publish("QT/yawn") 
        time.sleep(6)
    
    #rest
    elif(number == 19):
    #
        abc =1
        
    
    else:
        print("Please use a correct number!")


def gesture_talk(num):
    i = 1
    while i <= num:
        choose_behaviors(random.randint(1, 6))
        i = i + 1
    
    
def gesture_listen(num):
    i = 1
    while i <= num:
        choose_behaviors(random.randint(7, 8))
        i = i + 1
    

def gesture_guess(num):
    i = 1
    while i <= num:
        choose_behaviors(random.randint(9, 11))
        i = i + 1


def gesture_encourage():
    choose_behaviors(random.randint(12, 15))


#encourage decision function
def encourage_score():
    score = 1
    return score


def dictionary_set():
    #setting up phrase dictionaries
    #to guess
    guess_dict = {1: 'Is your number {}?', #2.5 sec
                    2: 'I guess {}. Did I guess your number?', #5.5 sec
                    3: 'Ok I think I know your number. Is it {}?', #5.5 sec
                    4: 'Is {} right?'} #2.5 sec
    #higher or lower
    second_dict = {1: 'Hey {} ,is your number higher than mine? Show me yes or no.', #7 sec 
                    2: 'Oh no I didn’t get it. Did I guess higher than your number {}?', #7 sec
                    3: 'Hmm is your guess bigger than mine {}?'} #4 sec  
    #to encourage play during game 
    encourage_dict = {1:'Good job {}!', #2.5 sec
                    2:'Hooray! Let\'s play again {}!', #4.5 sec
                    3:'That was your best one so far! Keep up the good work {}!', #7 sec
                    4:'I can tell you are trying really hard {}, nice job!', #5 sec
                    5:'You are getting better at this {}, wow!', #4 sec
                    6:'I know this is hard {}, keep trying!'} #4.5 sec
    clarify_dict = {1: 'I didn’t see that {}, could you repeat that answer for me?', #6 sec
                    2: 'I think that was a {}. If I’m right could you make a thumbs up/down for me?', #6.5 sec
                    3: 'Could you show me that answer again {}?'} #4 sec 
    reward_dict = {1: 'Let’s dance.', #2 sec
                    2: 'I have a joke {}, why did a crocodile marry a chicken? Because crock-o-doodle-doodle is a good last name!', #9.5 sec
                    3: 'What is your favorite color {}? Mine is blue.', #5.5 sec
                    4: 'I like playing games with you {}, you’re very fun. Do you like playing with me?'} #8 sec
    return guess_dict,second_dict,encourage_dict,clarify_dict,reward_dict




if __name__=="__main__":
    guess_dict,second_dict,encourage_dict,clarify_dict,reward_dict = dictionary_set()
    rospy.init_node('qt_numbergame')
    #initialize publishers
    right_pub = rospy.Publisher('/qt_robot/right_arm_position/command', Float64MultiArray, queue_size=1)
    left_pub = rospy.Publisher('/qt_robot/left_arm_position/command', Float64MultiArray, queue_size=1)
    head_pub = rospy.Publisher('/qt_robot/head_position/command', Float64MultiArray, queue_size=1)
    emotionShow_pub = rospy.Publisher('/qt_robot/emotion/show', String, queue_size=10)
    gesturePlay_pub = rospy.Publisher('/qt_robot/gesture/play', String, queue_size=10)
    speechSay_pub = rospy.Publisher('/qt_robot/speech/say', String, queue_size=10)
    audioPlay_pub = rospy.Publisher('/qt_robot/audio/play', String, queue_size=10)

    #wait for publisher connections
    wtime_begin = rospy.get_time()
    while (audioPlay_pub.get_num_connections() == 0 or
        speechSay_pub.get_num_connections() == 0 or
        gesturePlay_pub.get_num_connections() == 0 or
        emotionShow_pub.get_num_connections() == 0 or
        right_pub.get_num_connections() == 0 or
        left_pub.get_num_connections() == 0 or
        head_pub.get_num_connections() == 0 ) :
        rospy.loginfo("waiting for subscriber connections")
        if rospy.get_time() - wtime_begin > 5.0:
            rospy.logerr("Timeout while waiting for subscribers connection!")
            sys.exit()
        rospy.sleep(1)

    while 1:
        #game always running, until shutdown by children
        # exit_msg = rospy.wait_for_message()
        # if exit_msg.flag == False:
        once_again = raw_input('play again?') #type a number
        if once_again == 'no':
            #game over
            speechSay_pub.publish("I had a great time with you today. Bye-bye!")
            choose_behaviors(16)
            break
        elif once_again == 'yes':
            #introduction
            speechSay_pub.publish("Hello, my name is Q T Robot. What is your name?") #6.5 sec
            choose_behaviors(16)
            name = raw_input('What is your name? ')
            speechSay_pub.publish("Hi   "+name+""",      I would like to play a guessing game with you. 
            In the game I get to ask you questions, and you get to answer yes or no
            only by using a thumbs up or a thumbs down gesture with your right arm.
            Let's practice. Can you show me a thumbs up to say yes?""") #22-25 sec
            gesture_talk(3)
            #configuration
            correctup = raw_input('Was it a good thumbs up? ')
            if correctup == 'yes':
            # maybe need to sleep some time to wait for input
            # msg = rospy.wait_for_message("/thumb_result", Res)
            # msg.up_down
            # ^ these two lines would be replaced by camera or IMU input, worst case experimenter prompts
            #we need a time limit they can answer in - 5 sec?
                speechSay_pub.publish("Awesome! Now can you show me a thumbs down to say no?") #6 sec
                gesture_talk(1)
            correctdown = raw_input('Was it a good thumbs down? ')
            if correctdown == 'yes':
            # ^ these two lines would be replaced by camera or IMU input, worst case experimenter prompts
                speechSay_pub.publish("""Cool! During the game, please keep your hand in the 
                    middle until I ask you a question. That means your thumb is pointing sideways, 
                    not up or down! Remember to try as hard as you can to show me thumbs up 
                    or thumbs down, so I can understand if you mean yes or no! If your thumb 
                    is going the wrong way, just push the red button to move it back to the 
                    middle. Remember to keep your hands in the middle when you are not answering 
                    a question.  And just do your best. Can you show me yes if that’s ok?""") #40.5 sec
                gesture_talk(5)
            rospy.sleep(5)
            #initialize variables
            nocounter = 0
            yescounter = 0
            high = 101
            low = -1

            #play game now
            speechSay_pub.publish("Let's play now! Please think of a number between 1 and 100.") #6.5 sec
            gesture_talk(1)
            rospy.sleep(5)
            start = input('What is your number? ')#type a number
            # ^ this line would be replaced by camera or IMU input, worst case experimenter prompts
            # we should in general have a way to incorporate this in game to track wrong answers
            speechSay_pub.publish("I'm thinking of your number.") #3 sec
            gesture_guess(1)
            while start < 101:
            #this line should be changed to a while loop without a prompt input
                half_range = int((high-low)/2)
                current = half_range+low
                random_add = random.randrange(-half_range,half_range) #never add on outside of the guessing range
                random_guess = random.randrange(1,len(guess_dict))
                QT = current+random_add
                speechSay_pub.publish(guess_dict[random_guess].format(QT))    
                gesture_talk(1)
                #encourage the child
                random_encourage = random.randrange(1,len(encourage_dict))
                speechSay_pub.publish(encourage_dict[random_encourage].format(name))
                gesture_talk(1)
                val = raw_input('Is my guess correct?')
                # ^ this line would be replaced by camera or IMU input, worst case experimenter prompts
                    # use # number = sys.stdin.readline() if prompt
                    # number.split()[0]
                
                if val == 'no':
                    speechSay_pub.publish(second_dict[random_guess].format(name))
                    speechSay_pub.publish("my guess is "+str(QT)
                    gesture_talk(1)
                    nocounter += 1
                    while True:
                        val2 = input('higher(1) or lower(0)? ')
                        # ^ this line would be replaced by camera or IMU input, worst case experimenter prompts
                            # use # number = sys.stdin.readline() if prompt
                        if val2 == 1:
                            low = QT
                            yescounter += 1
                            break
                        if val2 == 0:
                            high = QT
                            nocounter += 1
                            break
                        else:
                            print("wrong input!please input again.")
                elif val == 'yes':
                    speechSay_pub.publish('Hooray I got it! Thanks for playing with me. Let’s play again!') #8 sec
                    #should they play a minimum of 3 games mandatory, the rest optional?
                    choose_behaviors(13)
                    yescounter += 1
                    print("Number of yes: "+str(yescounter)+". Number of no: "+str(nocounter))
                    print('I got it!')
                    break
                else:
                    #break the game
                    speechSay_pub.publish("Hmm Okay, I wish to play with you next time.") #6.5 sec
                    gesture_talk(1)
                    break
        else:
            print("wrong input!please input again.")





