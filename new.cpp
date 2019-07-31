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

void depth_callback(const sensor_msgs::ImageConstPtr& msg, cv::Mat & depth_image,int& flag)
{ cout<<"depth"<<flag<<endl;
    if(flag == 0){
    Mat tmp = cv_bridge::toCvShare(msg, "32FC1")->image;
    // cout<<tmp.rows<<' '<<tmp.cols<<endl;
    // imshow("angle", depth_image);
    // int number = 0;
	imshow("raw_image", tmp);
	for (int i=0;i<tmp.rows;i++)
	{
		for (int j=0;j<tmp.cols;j++)
		{
            depth_image.ptr<float>(i)[j] = tmp.ptr<float>(i)[j];
			// depth_image.at<uchar>(i,j)=tmp.at<uchar>(i,j);
		}
	}
    // imshow("angle", depth_image);
    // cv::resize(depth_image, depth_image, cv::Size(), 0.05, 0.05);
	// int number = 0;
	
	// 	MatIterator_<uchar> it, end;
	// 	for (it = depth_image.begin<uchar>(), end = depth_image.end<uchar>(); it != end; ++it) {
	// 		cout << float(*it) << " ";
	// 		number++;
	// 		if (0 == number % (depth_image.cols)) {
	// 			cout << endl;
	// 		}
		
		
	// }
    flag = 1; 
   
    }
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg, cv::Ptr<cv::BackgroundSubtractor> pMOG2,int* frame_number, ros::Publisher& res_pub, Point& last_thumb,Point& last_center, double& last_angle,cv::Mat &depth_image,int& flag)
{
    cout<<"image"<<flag<<endl;
    if(flag == 1){
        
        
    
    // cv::Mat ttt = depth_image;
    // cv::resize(depth_image, ttt, cv::Size(), 0.03, 0.03);
	// int number = 0;
	
	// 	MatIterator_<uchar> it, end;
	// 	for (it = ttt.begin<uchar>(), end = ttt.end<uchar>(); it != end; ++it) {
	// 		cout << float(*it) << " ";
	// 		number++;
	// 		if (0 == number % (ttt.cols)) {
	// 			cout << endl;
	// 		}
	// }
    // cout<<"***************"<<endl;







    Mat frame = cv_bridge::toCvShare(msg, "bgr8")->image;

    Mat foreground,res,show_img;//imageU,test,frameycbcr,ycrcb[3],
	
    if(*frame_number>20){
        pMOG2->apply(frame, foreground);
        *frame_number++;
    }
    else
        pMOG2->apply(frame, foreground,0);
    
    cv::erode(foreground,foreground,getStructuringElement(MORPH_RECT, Size(5, 5)));
    
    // frame.copyTo(test, foreground);
    GaussianBlur(foreground,foreground,Size(5, 5),1);
    threshold( foreground, foreground, 50, 255,THRESH_BINARY);
    cv::dilate(foreground,foreground,getStructuringElement(MORPH_RECT, Size(7, 7)));
    cv::erode(foreground,foreground,getStructuringElement(MORPH_RECT, Size(7, 7)));
    
    // cout<<foreground.channels()<<endl;
    


    // cout<<foreground.type()<<endl;
    // cvtColor(foreground, foreground,CV_BGR2YCrCb);
    // threshold( foreground, imageU, 50, 255,THRESH_BINARY);
    // cvtColor(test, frameycbcr,CV_BGR2YCrCb);
    // split(frameycbcr, ycrcb);
    // imageU = ycrcb[1].clone();
    // GaussianBlur(imageU,imageU,Size(5, 5),1);
    // threshold(imageU,imageU,0,255,CV_THRESH_OTSU);
    // cout<<imageU.channels()<<endl;



    //use imageU as mask
    frame.copyTo(res,foreground);

    frame.copyTo(show_img);

    Mat ttt = depth_image;
    for (int i=0;i<ttt.rows;i++)
	{
		for (int j=0;j<ttt.cols;j++)
		{
              if(ttt.ptr<float>(i)[j]>100)
                foreground.ptr<uchar>(i)[j] = 0;
            //   else
            //       foreground.ptr<uchar>(i)[j] = 0;
		}
	}
    // imshow("angle", ttt);
    int number = 0;
	cv::resize(depth_image, ttt, cv::Size(), 0.03, 0.03);
		MatIterator_<uchar> it, end;
		for (it = ttt.begin<uchar>(), end = ttt.end<uchar>(); it != end; ++it) {
			cout << float(*it) << " ";
			number++;
			if (0 == number % (ttt.cols)) {
				cout << endl;
			}
		
		
	}
    cout<<"*****************"<<endl;


    // //using color 
    // Mat hsv_image;
    // cv::cvtColor(res, hsv_image, cv::COLOR_BGR2HSV);
    // // int number = 0;
    // // MatIterator_<Vec3b> it, end;
	// // 	for (it = hsv_image.begin<Vec3b>(), end = hsv_image.end<Vec3b>(); it != end; ++it) {
	// // 		cout << float((*it)[0])<<' ';
	// // 		number++;
	// // 		if (0 == number % (hsv_image.cols)) {
	// // 			cout << endl;
	// // 		}
	// // 	}
	// // cout << "***********************************" << endl;
    
    // cv::Mat red_mask;
    // cv::Mat yellow_mask;

    // cv::inRange(hsv_image, cv::Scalar(0, 100, 30), cv::Scalar(27, 255, 255), red_mask);
    // cv::inRange(hsv_image, cv::Scalar(28, 100, 30), cv::Scalar(32, 255, 255), yellow_mask);
    // cv::erode(red_mask,red_mask,getStructuringElement(MORPH_RECT, Size(7, 7)));
    // cv::dilate(red_mask,red_mask,getStructuringElement(MORPH_RECT, Size(7, 7)));
    // cv::erode(yellow_mask,yellow_mask,getStructuringElement(MORPH_RECT, Size(7, 7)));
    // cv::dilate(yellow_mask,yellow_mask,getStructuringElement(MORPH_RECT, Size(7, 7)));

    // Moments red_moment = moments(red_mask, true);    
    // Point red_center(red_moment.m10/red_moment.m00, red_moment.m01/red_moment.m00);    
    // circle(show_img, red_center, 8 ,Scalar(0, 0, 255), CV_FILLED); 

    // Moments yellow_moment = moments(yellow_mask, true);    
    // Point yellow_center(yellow_moment.m10/yellow_moment.m00, yellow_moment.m01/yellow_moment.m00);    
    // circle(show_img, yellow_center, 6 ,Scalar(0, 255, 0), CV_FILLED); 
    // line(show_img, red_center, yellow_center, Scalar(255, 0, 0), 2);  
    //cv::inRange(hsv_image, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), upper_red_hue_range);
    //cv::bitwise_and(red_mask,res,red_mask);

    // res.copyTo(res,lower_red_hue_range);

    vector<vector<Point> > contours;    
    vector<Vec4i> hierarchy;    
    
    //寻找轮廓    
    cv::findContours(foreground, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);    
    // 找到最大的轮廓    
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
    cout<<contours.size()<<endl;
    
    if(contours.size()>1){
    // 寻找指尖
    vector<Point> couPoint = contours[index];
    vector<Point> fingerTips;    
    Point tmp;    
    int max=0, count=0, notice=0;
    double dist=0, tmp_angle = 0;
    for (int i = 0; i < couPoint.size(); i++)
    {    
        tmp = couPoint[i];    
        dist = (tmp.x - center.x) * (tmp.x - center.x) + (tmp.y - center.y) * (tmp.y - center.y);    
        if(tmp.x>center.x)
            continue;

        if((last_thumb.x!= 0)&&(last_thumb.y!=0))
        {
            double last_dist=(last_thumb.x - last_center.x) * (last_thumb.x - last_center.x) + (last_thumb.y - last_center.y) * (last_thumb.y - last_center.y);
            if(abs(last_dist-dist)>0.5*last_dist)
                continue;

            if(last_angle!=1000)
            {
                tmp_angle = -(atan2(tmp.y-center.y, tmp.x-center.x))* 180/3.141592653;
                double angle_diff = (abs(tmp_angle-last_angle)<360-abs(tmp_angle-last_angle))?abs(tmp_angle-last_angle):360-abs(tmp_angle-last_angle);
                //cout<<angle_diff<<endl;
                if(angle_diff>30)
                    continue;
            }
        }
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
    // angle_thumb = -(atan2(red_center.y-yellow_center.y, red_center.x-yellow_center.x))* 180/3.141592653;
    last_angle = angle_thumb;
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
    last_thumb = couPoint[notice];
    }
    else
    {
        last_thumb.x = 0;
        last_thumb.y = 0;
        last_angle = 1000;
    }
    
    imshow("raw_image", ttt);
    imshow("mask", foreground);
    imshow("angle", show_img);
    // last_center = center;
    flag =0;
    }
    
}

int main(int argc, char **argv)
{
    cv::Ptr<cv::BackgroundSubtractor> pMOG2;
    pMOG2 = cv::createBackgroundSubtractorMOG2(false);
    cv::Mat depth_image(480, 640, CV_32FC1, Scalar(0));//cv::Mat::zeros(cv::Size(640,480), CV_32FC1);
    int frame_number =0;
    int flag = 0;//==0 could do depth;==1 could do image
    double last_angle = 1000;
    Point last_thumb, last_center;
    last_thumb.x = 0;
    last_thumb.y = 0;
    last_center.x = 0;
    last_center.y = 0;
    ros::init(argc, argv, "get_image");
    ros::NodeHandle nh;

    cv::namedWindow("raw_image");
    cv::namedWindow("mask");
    cv::namedWindow("angle");

    cv::startWindowThread();

    ros::Publisher res_pub = nh.advertise<std_msgs::String>("thumb_result", 5);

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/image_raw", 1, boost::bind(&imageCallback, _1,pMOG2,&frame_number,res_pub,last_thumb,last_center,last_angle,depth_image,flag));
    image_transport::Subscriber sub_depth = it.subscribe("/camera/depth/image", 1, boost::bind(&depth_callback, _1,depth_image,flag));


    ros::Rate rate(15);
    while(ros::ok())
    {
      ros::spinOnce();
      rate.sleep();
    }

    destroyAllWindows();
    
}

