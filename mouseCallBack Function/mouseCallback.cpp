
#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>    
#include <opencv2/imgproc/types_c.h>   
#include <opencv2/core/core.hpp>          
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

cv::Mat org, img,tmp;
void on_mouse(int event, int x, int y, int flags, void *ustc)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号 


{
	static Point pre_pt = (-1, -1);//初始坐标  
	static Point cur_pt = (-1, -1);//实时坐标  
	static Point3i rgb_pt = (0, 0, 0);
	char temp[16];
	static int i = 0;
	//if (event == CV_EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处划圆  
	//{
	//	i++;
	//	org.copyTo(img);//将原始图片复制到img中  
	//	sprintf_s(temp, "(%d,%d)", x, y);
	//	pre_pt = Point(x, y);
	//	putText(img, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255), 1, 8);//在窗口上显示坐标  
	//	circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//划圆  
	//	cout << "the" << i << "th point BGR value is: " << img.at<Vec3b>(y, x)[0] << " " << img.at<Vec3b>(y, x)[1] << " " << img.at<Vec3b>(y, x)[2] << endl;
	//	imshow("img", img);
	//}
	if (event == CV_EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处划圆  
	{
		org.copyTo(img);//将原始图片复制到img中  
		sprintf_s(temp, "(%d,%d,%d)", img.at<Vec3b>(y, x)[0], img.at<Vec3b>(y, x)[1], img.at<Vec3b>(y, x)[2]);
		pre_pt = Point(x, y);
		putText(img, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, 8);//在窗口上显示坐标  
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//划圆  
		imshow("img", img);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//左键没有按下的情况下鼠标移动的处理函数
	{
		img.copyTo(tmp);//将img复制到临时图像tmp上，用于显示实时坐标  
		sprintf_s(temp, "(%d,%d,%d)", img.at<Vec3b>(y, x)[0], img.at<Vec3b>(y, x)[1], img.at<Vec3b>(y, x)[2]);
	cur_pt = Point(x, y);
	putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));//只是实时显示鼠标移动的坐标 
	imshow("img", tmp);
	}
}


int main()
{
	org = imread("2.jpg");
	org.copyTo(tmp);
	org.copyTo(img);
	namedWindow("img");//定义一个img窗口  
	setMouseCallback("img", on_mouse, 0);//调用回调函数  
	imshow("img", tmp);
	cv::waitKey(0);
}

