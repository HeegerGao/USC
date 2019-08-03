# Orthoses And QTrobot:<br>Helping Children Express Nonverbal Intensions
## Project Introduction
Dystonia is a movement disorder in which a person's muscles contract uncontrollably. The contraction causes the affected body part to twist involuntarily, resulting in repetitive movements or abnormal postures.<br>Physical therapy is a common method of treating dystonia, but it requires a small number of specialists and is expensive. At the same time, these patients are often unable to communicate verbally, so understanding their nonverbal intentions and helping them express nonverbal intentions are essential.<br><br>
[Children with dystonia](https://youtu.be/RBSRPd_Cwuk)<br><br>
In this project, we conducted two experiments on children (around 11 years old) with dystonia: 
* Orthoses Experiment: if children with orthoses can express their nonverbal intentions better.
* QTrobot Experiment:  if children are more willing to interact with a humanoid robot than normal electronic equipment, for example, a screen.<br>

The experiment will go like this table:



 DAY1  | DAY2  
 ---- | ----- 
 Orthoses Power Off & Playing with a screen  | Orthoses Power Off & Playing with QTrobot
 Orthoses Power On & Playing with a screen   | Orthoses Power On & Playing with QTrobot 

We designed a set of “number games” for children to play with a robot called QTrobot and wearing orthoses to test the two metrics during the game and collect all kinds of data (raw video, audio etc.) for later analysis.<br> <br>During the game, QTrobot will do different speaking, listening, guessing and other kinds of gestures and a lot of emotions to interact with children, and we designed encouraging and rewarding feedback for QTrobot during the game to make children more comfortable. In addition, we also did the work of using the camera to identify the thumb orientation, which is used in the game.<br>

## File Location
* thumb: thumb detection algorithm files and installation instruction
* QTrobot: QTrobot gestures/emotions/numbergame
* pictures: all pictures in the projects
* videos: all demos of the projects

## Instructions for Astra Pro and Camera Algorithm
### Installation
* install some dependies
```
sudo apt-get install build-essential freeglut3 freeglut3-dev
```
* install astra camera ros packages (for using depth images)
```
sudo apt-get install ros-kinetic-astra-camera ros-kinetic-astra-launch
```
* install libuvc (for use rgb images)
```
cd ~
git clone https://github.com/ktossell/libuvc
cd libuvc
mkdir build
cd build
cmake ..
make && sudo make install
```
* install libvuc-ros (for use rgb images)
```
cd ~/catkin_ws/src
git clone https://github.com/ktossell/libuvc_ros
cd ..
catkin_make 
```
* Install [opencv-3.4.6](https://github.com/opencv/opencv/archive/3.4.6.zip) and follow [the instruction](https://docs.opencv.org/3.4.6/d7/d9f/tutorial_linux_install.html)
* Download folder "thumb" to your catkin workspace
* Change opencv location in CMakeLists.txt, remember it's the build folder. Example:
```
set(OpenCV_DIR /home/sangerlab/Downloads/opencv-3.4.6/my_build)
```
* cd to your catkin workspace
```
catkin_make
soure devel/setup.bash
```
### Running
* Now you can run the camera. If you want to connect with QTrobot, you need to do this first:
 * connect to QT104 wifi
 * export ROS_MASTER_URI=http://192.168.100.1:11311 (or write it into your ~/.bashrc file and source it)
 * export ROS_IP=YOUR IP ADDRESS  (example:export ROS_IP=10.42.0.250) (or write it into your ~/.bashrc file and source it)

```
roscore (if you are connecting with QTrobot, you don't need to do this)
rosrun libuvc_camera camera_node
roslaunch astra_launch astra.launch 
rosrun thumb get_image
rosrun thumb get_state.py
```
* Tips:
 * In case that ```rosrun libuvc_camera camera_node``` get the error message like this:<br>
 ![](https://github.com/HeegerGao/USC/raw/master/pictures/error_libuvc.png)
 
## Instruction for QTrobot
* QTrobot has two computers. The head computer runs ROS CORE and ROS MASTER, and ROS_MASTER_URI is http://192.168.100.1:11311
* If you want to connect body computer to another computer, you need to let the two computer both connected to QT104 wifi
* To run this project, you should first 
