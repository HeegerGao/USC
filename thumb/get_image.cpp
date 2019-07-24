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


void imageCallback(const sensor_msgs::ImageConstPtr& msg, cv::Ptr<cv::BackgroundSubtractor> pMOG2,int* frame_number, ros::Publisher& res_pub)
{

    Mat frame = cv_bridge::toCvShare(msg, "bgr8")->image;

    Mat foreground,test,frameycbcr,ycrcb[3],imageU,res,show_img;
	
    if(*frame_number>20)
        pMOG2->apply(frame, foreground);
    else
        pMOG2->apply(frame, foreground,0);
    *frame_number++;
    cv::erode(foreground,foreground,getStructuringElement(MORPH_RECT, Size(5, 5)));
    
    frame.copyTo(test, foreground);

    cvtColor(test, frameycbcr,CV_BGR2YCrCb);
    split(frameycbcr, ycrcb);
    imageU = ycrcb[1].clone();
    GaussianBlur(imageU,imageU,Size(5, 5),1);
    threshold(imageU,imageU,0,255,CV_THRESH_OTSU);

    frame.copyTo(res,imageU);

    frame.copyTo(show_img);

    vector<vector<Point> > contours;    
    vector<Vec4i> hierarchy;    
    
    //寻找轮廓    
    cv::findContours(imageU, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);    
    
    // 找到最大的轮廓    
    int index;    
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
    
            
        Moments moment = moments(imageU, true);    
        Point center(moment.m10/moment.m00, moment.m01/moment.m00);    
        circle(show_img, center, 8 ,Scalar(0, 0, 255), CV_FILLED);    
    
        // 寻找指尖    
        vector<Point> couPoint = contours[index];    
        vector<Point> fingerTips;    
        Point tmp;    
        int max=0, count=0, notice=0,dist=0;    
        for (int i = 0; i < couPoint.size(); i++)    
        {    
            tmp = couPoint[i];    
            dist = (tmp.x - center.x) * (tmp.x - center.x) + (tmp.y - center.y) * (tmp.y - center.y);    
            if(tmp.x>center.x)
                continue;
            if (dist > max)    
            {    
                max = dist;    
                notice = i;    
            }    
        }
          
        fingerTips.push_back(couPoint[notice]);    
        circle(show_img, couPoint[notice], 6 ,Scalar(0, 255, 0), CV_FILLED);    
        line(show_img, center, couPoint[notice], Scalar(255, 0, 0), 2);                 

    
    //计算大拇指的角度，注意图像的坐标上面小下面大
    double angle_thumb = 0;
    
    angle_thumb = -(atan2(couPoint[notice].y-center.y, couPoint[notice].x-center.x))* 180/3.141592653;
    //判断大拇指上下，1为上，0为中，-1为下
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

    imshow("raw_image", frame);
    imshow("mask", res);
    imshow("angle", show_img);


    
}

int main(int argc, char **argv)
{
    cv::Ptr<cv::BackgroundSubtractor> pMOG2;
    pMOG2 = cv::createBackgroundSubtractorMOG2(false);

    int frame_number =0;

    ros::init(argc, argv, "get_image");
    ros::NodeHandle nh;

    cv::namedWindow("raw_image");
    cv::namedWindow("mask");
    cv::namedWindow("angle");

    cv::startWindowThread();

    ros::Publisher res_pub = nh.advertise<std_msgs::String>("thumb_result", 5);

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/image_raw", 1, boost::bind(&imageCallback, _1,pMOG2,&frame_number,res_pub));


    ros::Rate rate(10);
    while(ros::ok())
    {
      ros::spinOnce();
      rate.sleep();
    }

    destroyAllWindows();
    
}

