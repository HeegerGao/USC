#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>

#include <thumb/Res.h>
using namespace std;
using namespace cv;



  
//     //运用迭代器访问矩阵元素  
//     MatIterator_<uchar> it_Cb = planes[1].begin<uchar>(),  
//                         it_Cb_end = planes[1].end<uchar>();  
//     MatIterator_<uchar> it_Cr = planes[2].begin<uchar>();  
//     MatIterator_<uchar> it_skin = skinArea.begin<uchar>();  
  
//     //人的皮肤颜色在YCbCr色度空间的分布范围:100<=Cb<=127, 138<=Cr<=170  
//     for( ; it_Cb != it_Cb_end; ++it_Cr, ++it_Cb, ++it_skin)  
//     {  
//         if (138 <= *it_Cr &&  *it_Cr <= 170 && 100 <= *it_Cb &&  *it_Cb <= 127)  
//             *it_skin = 255;  
//         else  
//             *it_skin = 0;  
//     }  
  
//     //膨胀和腐蚀，膨胀可以填补凹洞（将裂缝桥接），腐蚀可以消除细的凸起（“斑点”噪声）  
//     dilate(skinArea, skinArea, Mat(5, 5, CV_8UC1), Point(-1, -1));  
//     erode(skinArea, skinArea, Mat(5, 5, CV_8UC1), Point(-1, -1));  
//   } 

//   void imageCallback_depth(const sensor_msgs::ImageConstPtr& msg, cv::Mat &depth_image)
//   {
//     //第二个参数为深度图的引用
//     try
//     {
//     //将深度图复制出来
//     Mat test;
//     cv::resize(cv_bridge::toCvShare(msg)->image, test, cv::Size(512,512));;
//     for (int i=0;i<depth_image.rows;i++)        //遍历每一行每一列并设置其像素值
// 	    {
// 		    for (int j=0;j<depth_image.cols;j++)
// 		    {
// 			    depth_image.at<uchar>(i,j)=test.at<uchar>(i,j);
// 		    }
// 	    }


//       // int num = 0;
    
//     // cv::resize(image, image, cv::Size(32, 32));
//     // MatIterator_<uchar> it, end;
// 		// for (it = image.begin<uchar>(), end = image.end<uchar>(); it != end; ++it) {
// 		// 	cout << float(*it) << " ";
// 		// 	number++;
// 		// 	if (0 == number % (image.cols)) {
// 		// 		cout << endl;
// 		// 	}
// 		// }
// 		// cout << "***********************************" << endl;
//     // int number = 0;
//     // cv::Mat image = cv_bridge::toCvShare(msg/* , "bgr8"*/)->image;
//     // cv::imshow("view", image);


//void imageCallback(const sensor_msgs::ImageConstPtr& msg, dnn::Net net)
void imageCallback(const sensor_msgs::ImageConstPtr& msg, cv::Ptr<cv::BackgroundSubtractor> pMOG2,int* frame_number, ros::Publisher& res_pub)
{
    
    // const int POSE_PAIRS[20][2] =
    // {
    //   {0,1}, {1,2}, {2,3}, {3,4},         // thumb
    //   {0,5}, {5,6}, {6,7}, {7,8},         // index
    //   {0,9}, {9,10}, {10,11}, {11,12},    // middle
    //   {0,13}, {13,14}, {14,15}, {15,16},  // ring
    //   {0,17}, {17,18}, {18,19}, {19,20}   // small
    // };
    // int nPoints = 22;
    // float thresh = 0.01;

    // Mat frame = cv_bridge::toCvShare(msg, "bgr8")->image;
    // Mat frameCopy = frame.clone();
    // int frameWidth = frame.cols;
    // int frameHeight = frame.rows;

    // float aspect_ratio = frameWidth/(float)frameHeight;
    // int inHeight = 368;
    // int inWidth = (int(aspect_ratio*inHeight) * 8) / 8;

    // cout << "inWidth = " << inWidth << " ; inHeight = " << inHeight << endl;

    // double t = (double) cv::getTickCount();

    // Mat inpBlob = cv::dnn::blobFromImage(frame, 1.0 / 255, Size(inWidth, inHeight), Scalar(0, 0, 0), false, false);

    // net.setInput(inpBlob);

    // Mat output = net.forward();

    // double t1 = ((double)cv::getTickCount() - t)/cv::getTickFrequency();
    // cout << "Time Taken = " << t1 << endl;

    // int H = output.size[2];
    // int W = output.size[3];

    // // find the position of the body parts
    // vector<Point> points(nPoints);
    // for (int n=0; n < nPoints; n++)
    // {
    //     // Probability map of corresponding body's part.
    //     Mat probMap(H, W, CV_32F, output.ptr(0,n));
    //     resize(probMap, probMap, Size(frameWidth, frameHeight));

    //     Point maxLoc;
    //     double prob;
    //     minMaxLoc(probMap, 0, &prob, 0, &maxLoc);
    //     if (prob > thresh)
    //     {
    //         circle(frameCopy, cv::Point((int)maxLoc.x, (int)maxLoc.y), 8, Scalar(0,255,255), -1);
    //         cv::putText(frameCopy, cv::format("%d", n), cv::Point((int)maxLoc.x, (int)maxLoc.y), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 255), 2);

    //     }
    //     points[n] = maxLoc;
    // }

    // int nPairs = sizeof(POSE_PAIRS)/sizeof(POSE_PAIRS[0]);

    // for (int n = 0; n < nPairs; n++)
    // {
    //     // lookup 2 connected body/hand parts
    //     Point2f partA = points[POSE_PAIRS[n][0]];
    //     Point2f partB = points[POSE_PAIRS[n][1]];

    //     if (partA.x<=0 || partA.y<=0 || partB.x<=0 || partB.y<=0)
    //         continue;

    //     line(frame, partA, partB, Scalar(0,255,255), 8);
    //     circle(frame, partA, 8, Scalar(0,0,255), -1);
    //     circle(frame, partB, 8, Scalar(0,0,255), -1);
    // }
    // //计算大拇指的角度，使用12,13,14三对点计算角度取平均,注意图像的坐标上面小下面大
    // double angle_thumb = 0;
    
    // angle_thumb = -(atan2(points[2].y-points[1].y, points[2].x-points[1].x)+
    //               atan2(points[3].y-points[1].y, points[3].x-points[1].x)+
    //               atan2(points[4].y-points[1].y, points[4].x-points[1].x))* 180/(3.0*3.141592653);
    // //判断大拇指上下，1为上，0为中，-1为下
    // int up_down_flag = 0;
    // if(angle_thumb>30 && angle_thumb<150) up_down_flag = 1;
    // else if(angle_thumb>-150 && angle_thumb<-30) up_down_flag = -1;
    // else up_down_flag = 0;

    // t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();
    // cout << "Time Taken = " << t << endl;
    // cout << "The thumb's angle is:" <<angle_thumb<<endl;
    // if(up_down_flag == 1)
    //     cout<<"The thumb is up!"<<endl;
    // else if(up_down_flag == -1)
    //     cout<<"The thumb is down!"<<endl;
    // else
    //     cout<<"The thumb is horizontal!"<<endl;

    // imshow("Output-Keypoints", frameCopy);
    // imshow("Output-Skeleton", frame);
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
    
    thumb::Res res_msg;
    res_msg.angle = angle_thumb;
    if(up_down_flag == 1){
        cout<<"The thumb is up!"<<endl;
        res_msg.up_down = 1;
    }
    else if(up_down_flag == -1){
        cout<<"The thumb is down!"<<endl;
        res_msg.up_down = -1;
    }
    else{
        cout<<"The thumb is horizontal!"<<endl;
        res_msg.up_down = 0;
    }

    
    res_pub.publish(res_msg);


    imshow("raw_image", frame);
    imshow("mask", res);
    imshow("angle", show_img);


    // int number = 0;
    
    // cv::resize(imageU, imageU, cv::Size(32, 32));
    // MatIterator_<uchar> it, end;
	// 	for (it = imageU.begin<uchar>(), end = imageU.end<uchar>(); it != end; ++it) {
	// 		cout << float(*it) << " ";
	// 		number++;
	// 		if (0 == number % (imageU.cols)) {
	// 			cout << endl;
	// 		}
	// 	}
	// 	cout << "***********************************" << endl;
}

int main(int argc, char **argv)
{
    cv::Ptr<cv::BackgroundSubtractor> pMOG2;
    pMOG2 = cv::createBackgroundSubtractorMOG2(false);

    string protoFile = "/home/sangerlab/catkin_ws/src/thumb/pose_deploy.prototxt";
    string weightsFile = "/home/sangerlab/catkin_ws/src/thumb/pose_iter_102000.caffemodel";
    dnn::Net net = dnn::readNetFromCaffe(protoFile, weightsFile);

    int frame_number =0;
    

    ros::init(argc, argv, "get_image");
    ros::NodeHandle nh;

    cv::namedWindow("raw_image");
    cv::namedWindow("mask");
    cv::namedWindow("angle");

    cv::startWindowThread();

    ros::Publisher res_pub = nh.advertise<thumb::Res>("thumb_result", 5);

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/image_raw", 1, boost::bind(&imageCallback, _1,pMOG2,&frame_number,res_pub));


    ros::Rate rate(10);
    while(ros::ok())
    {
      ros::spinOnce();
      rate.sleep();
    }

    destroyAllWindows();
    // cv::namedWindow("view");
    // cv::startWindowThread();
      
    // cv::Mat depth_image(512,512,CV_8UC1);
    // for (int i=0;i<depth_image.rows;i++)        //遍历每一行每一列并设置其像素值
	  // {
		//   for (int j=0;j<depth_image.cols;j++)
		//   {
		// 	  depth_image.at<uchar>(i,j)=1;
		//   }
	  // }

    // image_transport::ImageTransport it(nh);

    // image_transport::Subscriber sub1 = it.subscribe("/camera/depth/image_raw", 1, boost::bind(&imageCallback_depth, _1, depth_image));
    // image_transport::Subscriber sub2 = it.subscribe("/image_raw", 1, boost::bind(&imageCallback_bgr, _1,depth_image));
      
      
    // ros::Rate rate(24);
    // while(ros::ok())
    // {
    //   ros::spinOnce();
    //   rate.sleep();
    // }
    // cv::destroyWindow("view");
}
