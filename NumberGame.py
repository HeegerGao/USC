# -*- coding: utf-8 -*-
#!/usr/local/bin/python
#!/usr/bin/env python
# coding: utf-8

import rospy
from std_msgs.msg import String

frame = 0
state = 0
buttons = 0

def callback(data):
    strdata = str(data)

    # hacky split
    val = strdata.split(':')
    val = val[1].split('\\t');
    temp = val[0].split('"');
    
    global frame
    global state
    global buttons
    
    frame = int(temp[1])
    state = int(val[1])
    buttons = int(val[2])
    #print(frame, state, buttons)
    
def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber('openwearable', String, callback)
    rospy.sleep(3) #change sleep value to be amount of time to answer (5 sec?)

#initialize variables, import modules
import random
nocounter = 0
yescounter = 0
high = 101
low = -1
name = 'Catherine'

#setting up phrase dictionaries
#to guess
guess_dict = {1: 'Is your number {}?', #2.5 sec
                2: 'I guess {}. Did I guess your number?', #5.5 sec
                3: 'Ok I think I know your number. Is it {}?', #5.5 sec
                4: 'Is {} right?'} #2.5 sec
#higher or lower
second_dict = {1: 'Hey {} is your number higher than mine? Show me yes or no.', #7 sec 
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

#introduction
print("""In this game I get to ask you questions, and you get to answer yes or no
    only by using a thumbs up or a thumbs down gesture with your right arm.
    Let's practice. Can you show me a thumbs up to say yes?""") #use green button, pull from ow_subscriber.py
# listener()
if __name__ == '__main__':
    listener()
    if buttons is 1:
        print("Awesome! Now can you show me a thumbs down to say no?")
        listener()
        if buttons is -1:
            print("""Cool! During the game, please keep your hand in the 
        middle until I ask you a question. That means your thumb is pointing sideways, 
        not up or down! Remember to try as hard as you can to show me thumbs up 
        or thumbs down, so I can understand if you mean yes or no! If your thumb 
        is going the wrong way, just push the red button to move it back to the 
        middle. Remember to keep your hands in the middle when you are not answering 
        a question.  And just do your best. Can you show me yes if that’s ok?""")
            listener()
            if buttons is 1:
                print("Let's play now! Please think of a number between 1 and 100.") #6.5 sec
                print("I'm thinking of your number.")

#game play - use 0/1 or true/false instead of string
start = input('What is your number? ') #type a number <101
while start < 101:
    half_range = int((high-low)/2)
    current = half_range+low
    random_add = random.randrange(-half_range,half_range) #never add on outside of the guessing range
    QT = current+random_add
    random_guess = random.randrange(1,len(guess_dict))
    random_talk = random.randrange(1,5)
    random_listen = random.randrange(5,9)
    random_encourage = random.randrange(9,12)
    random_other = random.randrange(13,17)

    print(guess_dict[random_guess].format(QT))
    listener()
    if buttons is -1:
        print(second_dict[random_guess].format(name))
        val2 = input('higher(1) or lower(0)? ')
        nocounter += 1
        if val2 is 1:
            low = QT
            yescounter += 1
        if val2 is 0:
            high = QT
            nocounter += 1
    else:
        print('Hooray I got it! Thanks for playing with me. Let’s play again!')
        yescounter += 1
        print("Number of yes: "+str(yescounter)+". Number of no: "+str(nocounter))
        quit()
        



