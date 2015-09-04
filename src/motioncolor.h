/*
*  FILE motioncolor.h
*  AUTHOR Sarah
*  DATE 2015/08/14 20:17
*  TODO: 利用孟塞尔颜色系统，将用颜色光流显示出来。 
*/
#pragma once

#include "stdafx.h"
#include <cv.h>
#include "optutil.h"

using namespace cv;
using namespace std;

#ifndef util_MOTIONCOLOR_
#define util_MOTIONCOLOR_

/*
*  Method:     makeColorWheel
*  Description: 构建孟塞尔颜色系统系统
*               http://blog.csdn.net/zouxy09/article/details/8683859
*  Returns:    void. 
*  vector<Scalar> & colorwheel: Required = true. (孟塞尔颜色系统系统，程序执行结束之后被赋值)
*/
void makeColorWheel(vector<Scalar> &colorwheel);

/*
*  Method:     motionMatToColor
*  Description: 根据孟塞尔颜色系统，将光流（flow）转化为相应的颜色，参数类型为IplImage.
*  Returns:    void. 
*  Mat flow: Required = true. 光流. 
*  Mat & color: Required = true. (程序执行结束之后被赋值)
*/
void motionMatToColor(Mat flow, Mat &color);

/*
*  Method:     motionCvMatToColor
*  Description: 根据孟塞尔颜色系统，将光流(velx, vely) 转化为相应的颜色，参数类型为.
*  Returns:    void. 
*  CvMat * velx: Required = true. X方向上的光流.
*  CvMat * vely: Required = true. Y方向上的光流.
*  Mat & color: Required = true. (程序执行结束之后被赋值)
*/
void motionCvMatToColor(CvMat* velx, CvMat* vely, Mat &color);

#endif /* util_MOTIONCOLOR_ */