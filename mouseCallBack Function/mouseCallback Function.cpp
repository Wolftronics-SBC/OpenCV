
#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>    
#include <opencv2/imgproc/types_c.h>   
#include <opencv2/core/core.hpp>          
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

cv::Mat src, img, tmp;
void on_mouse(int event, int x, int y, int flags, void *ustc)//mouse event, x,y mouse location


{
	static Point pre_pt = (-1, -1);//initial coordinate  
	static Point cur_pt = (-1, -1);//realtime coordinate  
	static Point3i rgb_pt = (0, 0, 0);//BGR value 
	char temp[16];//text shown on image


	if (event == CV_EVENT_LBUTTONDOWN)//when pressing the lbuttion  
	{
		img = src.clone();//copy src data to img 
		sprintf_s(temp, "(%d,%d,%d)", img.at<Vec3b>(y, x)[0], img.at<Vec3b>(y, x)[1], img.at<Vec3b>(y, x)[2]);
		pre_pt = Point(x, y);
		putText(img, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, 8);//show text where mouse points on the namedWindow 
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//draw circle 
		imshow("img", img);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//when mouse is moving
	{
		tmp = img.clone(); //copy img data to tmp 
		sprintf_s(temp, "(%d,%d,%d)", img.at<Vec3b>(y, x)[0], img.at<Vec3b>(y, x)[1], img.at<Vec3b>(y, x)[2]);
		cur_pt = Point(x, y);
		putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));//show text when mouse is moving on the namedWindow 
		imshow("img", tmp);
		}
}


int main()
{
	src = imread("2.jpg");
	tmp = src.clone();
	img = src.clone();
	namedWindow("img");
	setMouseCallback("img", on_mouse, 0);//callback function
	imshow("img", tmp);
	cv::waitKey(0);
}

