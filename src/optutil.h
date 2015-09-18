/*
*  FILE optutil.h
*  AUTHOR Sarah
*  DATE 2015/08/14 22:25
*  TODO: 光流计算方法处理光流的公共方�? 
*/
#pragma once

#include "stdafx.h"
#include <cv.h>

using namespace cv;
using namespace std;

#ifndef util_FOE_TTC_
#define util_FOE_TTC_

void tagSafeAreaByTTC(int cols, float* ttc, float ttcAvg , float k,int *tagSafe);

float compareTag(int *tagOrigin, int *tagSafe, int cols, int *tags);

/*
*  Method:     drawFlow
*  Description: p到q的连线，表示p像素的光流，参数类型为IplImage. 
*  Returns:    void
*  CvPoint p:   Required = true. 源点. 
*  CvPoint q:   Required = true. 目的�? q - p = 光流. 
*  IplImage * imgdst: Required = true. 在图像帧imgdst画光�?
*/
void drawFlow(CvPoint p, CvPoint q, IplImage* imgdst);

/*
*  Method:     drawMatFlow
*  Description: p到q的连线，表示p像素的光流，参数类型为cv::mat. 
*  Returns:    void
*  CvPoint p:   Required = true. 源点. 
*  CvPoint q:   Required = true. 目标点， q - p = 光流. 
*  Mat framedst: Required = true. 在图像帧framedst画光�?
*/
void drawMatFlow(CvPoint p, CvPoint q, Mat framedst);

float balanceControlLR(IplImage* imgdst, CvMat* velx, int leftSumFlow, int rightSumFlow, float k);

bool isBigObstacle(IplImage* imgdst, CvMat* velx);

float turnLRScale(float leftSumFlow, float rightSumFlow, float k);
#endif /* util_FOE_TTC_ */