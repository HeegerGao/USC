#!/usr/bin/env python
# encoding=utf8

#initialize variables, import modules, set up phrase lists
import random
import sys
import rospy
from std_msgs.msg import String
rospy.init_node('qt_robot_interface1') #unique node name
Talk = rospy.Publisher('/qt_robot/behavior/talkText', String, queue_size = 10)
Emotion = rospy.Publisher('/qt_robot/emotion/show', String, queue_size = 10)
Gesture = rospy.Publisher('/qt_robot/gesture/play', String, queue_size = 10)
while Talk.get_num_connections() == 0:
	rospy.loginfo("Waiting for subscriber to connect")
	rospy.sleep(1) #teaching it to wait

#phrase dictionaries
#introduction dict
intro_dict = {1:'Nice to meet you, I\'m QT! What\'s your name? Want to play a game? Always do max effort with your motions!', 
		        2:'Nice to meet you, I\'m QT! Let\'s play a game! Think of a number between 1 and 100. Always do max effort with your motions!',
		        3:'Hi I\'m QT! I think we\'ll have fun together. Can you think of a number between 1 and 100? Always do max effort with your motions!', 
		        4:'Remember I can talk but I don\'t understand what you are saying. Always do max effort with your motions!'}
#to encourage play during game 
encourage_dict = {1:'Good job!', 
                2:'Hooray! Let\'s play again!', 
                3:'Wow you\'re good at this!',
		        4:'You\'re doing a great job!',
		        5:'Wow this is hard you\'re good at this！'}
# #researcher can use this if participant not paying attention - needs button or researcher needs computer
# distraction_set = ['Hi please focus on me', 'Do you like to play games?',
# 		'Let\'s keep playing.', 'I am sad when you ignore me.', 
# 		'Why won\'t you play with me?','Don\'t touch me!',
# 		'Want to hear a joke? Show me yes or no with your hand.'] 
# #for when partipicant makes an unclear gesture - needs button or researcher needs computer
# confusion_set = ['I don’t think I understand could you repeat that motion?', 'Let\'s try again so I can be sure.', 'No talking just show me with your motions.']
# #for when the game is too hard for the participant - needs button or researcher needs computer
# end_set = ['Hm maybe we should play a different game.', 'Would you like to take a break?',
# 		'Let\'s take a break.', 'Don\'t be sad let\'s do something else!']



#introduction and explain rules
random_phrase = random.randrange(0,len(intro_dict))
#Talk.publish(intro_dict[random_phrase]) #QT says this
rospy.sleep(1) #allow QT to finish sentence
Talk.publish(encourage_dict[random_phrase]) #QT says this
rospy.sleep(1) #allow QT to finish sentence

Talk.publish(intro_dict[random_phrase]) #QT says this
rospy.sleep(3) #allow QT to finish sentence
Talk.publish(encourage_dict[random_phrase]) #QT says this
rospy.sleep(3) #allow QT to finish sentence

Talk.publish(intro_dict[random_phrase]) #QT says this
rospy.sleep(10) #allow QT to finish sentence
Talk.publish(encourage_dict[random_phrase]) #QT says this
rospy.sleep(10) #allow QT to finish sentence

#start = input('Let\'s start! ') #type ok

# #play the game
# while start is 'ok':
# 	Talk.publish('Is my guess correct?')
# 	rospy.sleep(1)
# 	val = input('Is my guess correct? ')
# 	if val == 'no':
# 	#QT makes a sad face, or says something
# 		Emotion.publish('QT/sad')
# 		Talk.publish('Is your number higher than my guess?')
# 		rospy.sleep(2)
# 		val2 = input('yes or no? ')
# 		if val2 == 'yes':
# 			guess_list = [guess,100]
# 		if val2 == 'no':
# 			guess_list = [0,guess]
# 	 #    if val == 'c': #participant is confused, researcher types
# 		# 	Talk.publish(confusion_set[random_phrase_ix])
# 		#	Emotion.publish('ava_confused') #questioning face - needs special programming?
# 		# 	rospy.sleep(3)
# 		# if val == 'd': #participant is distracted, researcher types
# 		# 	Talk.publish(distraction_set[random_phrase_ix])
# 		#	Emotion.publish('ava_diqust') #disappointed face
# 		# 	rospy.sleep(3)
# 	  #   if val == 'e': #game is too hard
# 			# Talk.publish(end_set[random_phrase_ix])
# 			# Emotion.publish('ava_sad') #sad face
# 			# rospy.sleep(3)
# 		half_guess = int((guess_list[1]-guess_list[0])/2)
# 		guess = bisect.bisect(guess_list, half_guess)+half_guess
# 		newbound = guess+guess_list[0]
# 		Talk.publish('Is your guess' + str(newbound))
# 		Emotion.publish('QT/confused') #questioning face - needs special programming?
# 		rospy.sleep(2)
# 		Talk.publish(encourage_set[random_phrase_ix])
# 		Emotion.publish('QT/happy') #or happy, etc
# 		rospy.sleep(3)
# 	if val == 'yes':
# 		Talk.publish('I win!')
# 		Emotion.publish('QT/happy')
# 		Gesture.publish('QT/happy') #dance, victory 
# 		rospy.sleep(5)
# 		Talk.publish('Bye bye!')
# 		quit()
# 	if val == 'c': #participant is confused, researcher types
# 		Talk.publish(confusion_set[random_phrase_ix])
# 		Emotion.publish('QT/confused') #questioning face - needs special programming?
# 		rospy.sleep(3)
# 	if val == 'd': #participant is distracted, researcher types
# 		Talk.publish(distraction_set[random_phrase_ix])
# 		Emotion.publish('QT/bored') #disappointed face
# 		rospy.sleep(3)
# 	if val == 'e': #game is too hard
# 		Talk.publish(end_set[random_phrase_ix])
# 		Emotion.publish('QT/sad') #sad face
# 		rospy.sleep(3)
		

