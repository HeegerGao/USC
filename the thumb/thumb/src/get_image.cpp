#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp>
#include <iostream>
#include <string>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
#include "std_msgs/String.h"
#include <thumb/Res.h>
using namespace std;
using namespace cv;

void depth_callback(const sensor_msgs::ImageConstPtr& msg,cv::Mat& depth_mask)
{
    Mat depth_image = cv_bridge::toCvShare(msg, "32FC1")->image;
    threshold( depth_image, depth_mask,0.75, 255,1);
    cv::dilate(depth_mask,depth_mask,getStructuringElement(MORPH_RECT, Size(15, 15)));
    cv::erode(depth_mask,depth_mask,getStructuringElement(MORPH_RECT, Size(15, 15)));
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg,ros::Publisher& res_pub,cv::Mat &depth_mask)
{  
    imshow("raw_image", depth_mask);
    Mat frame = cv_bridge::toCvShare(msg, "bgr8")->image;

    Mat foreground,res,show_img;
    
    foreground = depth_mask;
    
    foreground.convertTo(foreground, CV_8UC1);

    frame.copyTo(show_img);

    vector<vector<Point> > contours;    
    vector<Vec4i> hierarchy;    
    
    //find the contours    
    cv::findContours(foreground, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);    
    // find the max contour
    int index=0;    
    double area, maxArea(0);    
    for (int i=0; i < contours.size(); i++)    
    {    
        area = contourArea(Mat(contours[i]));    
        if (area > maxArea)    
        {    
            maxArea = area;    
            index = i;    
        }               
    }    
    
            
    Moments moment = moments(foreground, true);    
    Point center(moment.m10/moment.m00, moment.m01/moment.m00);    
    circle(show_img, center, 8 ,Scalar(0, 0, 255), CV_FILLED);    
    
    if(contours.size()>=1){
    // find fingertips
    vector<Point> couPoint = contours[index];
    vector<Point> fingerTips;    
    Point tmp;    
    int max=0, count=0, notice=0;
    double dist=0, tmp_angle = 0;
    for (int i = 0; i < couPoint.size(); i++)
    {    
        tmp = couPoint[i];    
        dist = (tmp.x - center.x) * (tmp.x - center.x) + (tmp.y - center.y) * (tmp.y - center.y);    
        
        if (dist > max)
        {    
            max = dist;    
            notice = i;    
        }    
    }
        
    fingerTips.push_back(couPoint[notice]);    
    circle(show_img, couPoint[notice], 6 ,Scalar(0, 255, 0), CV_FILLED);    
    line(show_img, center, couPoint[notice], Scalar(255, 0, 0), 2);                 

    
    //compute the angle for thumb
    double angle_thumb = 0;
    
    angle_thumb = -(atan2(couPoint[notice].y-center.y, couPoint[notice].x-center.x))* 180/3.141592653;
    
    //judgement, 1 == up,-1 == down, 0==normal
    int up_down_flag = 0;
    if(angle_thumb>30 && angle_thumb<150) up_down_flag = 1;
    else if(angle_thumb>-150 && angle_thumb<-30) up_down_flag = -1;
    else up_down_flag = 0;
    cout << "The thumb's angle is:" <<angle_thumb<<endl;
    
    std_msgs::String res_msg;
    if(up_down_flag == 1){
        cout<<"The thumb is up!"<<endl;
        res_msg.data = std::to_string(1)+'+'+std::to_string(angle_thumb);
    }
    else if(up_down_flag == -1){
        cout<<"The thumb is down!"<<endl;
        res_msg.data = std::to_string(-1)+'+'+std::to_string(angle_thumb);
    }
    else{
        cout<<"The thumb is horizontal!"<<endl;
        res_msg.data = std::to_string(0)+'+'+std::to_string(angle_thumb);
    }

    
    res_pub.publish(res_msg);
    
    }

    imshow("angle", show_img);

}

int main(int argc, char **argv)
{
    cv::Mat depth_mask(480,640,CV_32FC1,Scalar(0));
    int frame_number =0;
    
    double last_angle = 1000;
    Point last_thumb, last_center;
    last_thumb.x = 0;
    last_thumb.y = 0;
    last_center.x = 0;
    last_center.y = 0;
    ros::init(argc, argv, "get_image");
    ros::NodeHandle nh;

    cv::namedWindow("raw_image");
    cv::namedWindow("angle");

    cv::startWindowThread();

    ros::Publisher res_pub = nh.advertise<std_msgs::String>("thumb_result", 5);

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/image_raw", 1, boost::bind(&imageCallback, _1,res_pub,depth_mask));
    image_transport::Subscriber sub_depth = it.subscribe("/camera/depth/image", 1, boost::bind(&depth_callback, _1,depth_mask));


    ros::Rate rate(15);
    while(ros::ok())
    {
      ros::spinOnce();
      rate.sleep();
    }

    destroyAllWindows();
    
}

