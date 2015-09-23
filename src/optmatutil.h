/*
*  FILE optmatutil.h
*  AUTHOR Sarah
*  DATE 2015/08/15 10:42
*  TODO: SF/FB 稠密光流公共方法如左右光流平衡�?画光流�?求FOE、TTC�?
*/
#pragma once

#include "stdafx.h"
#include <cv.h>

#include "optutil.h"

using namespace cv;
using namespace std;

#ifndef util_OPT_MAT_
#define util_OPT_MAT_


Vec2i foeForDenseMat(Mat flow);

float ttcForDenseMat(Mat flow, int foeY, float *ttc);

/*
*  Method:     balanceForDenseMat
*  Description: 左右光流平衡. 
*  Returns:    int. 控制指令. 1 - �? 2 - �? 3 - �? 4 - 停止. 
*  Mat flow: Required = true. 光流.
*  Mat framedst: Required = true. 目标图像�?
*  int threshold: Required = true. 阈�?，当光流大于此阈值时，返回控制指�?.
*  float k: Required = false. 左右光流平衡的权�? 当左右差距在权�?范围内时，返�?.
*  int px: Required = false. 左右光流的分界线.
*  int py: Required = false. 上下光流的分界线.
*  float edge: Required = false. 忽略上下左右edge倍的边界. 
*/
float balanceForDenseMat(Mat flow, Mat framedst, float k, int px = WIDTH/2, int py = HEIGHT/2);

/*
*  Method:     drawFlowForDenseMat
*  Description: 在framedst图像帧上画光�? 
*  Returns:    void. 
*  Mat flow: Required = true. 光流. 
*  Mat framedst: Required = true. 目标图像�?
*/
void drawFlowForDenseMat(Mat flow, Mat framedst);

/*
*  Method:     drawMatFlow
*  Description: p到q的连线，表示p像素的光流，参数类型为cv::mat. 
*  Returns:    void
*  CvPoint p:   Required = true. 源点. 
*  CvPoint q:   Required = true. 目标点， q - p = 光流. 
*  Mat framedst: Required = true. 在图像帧framedst画光�?
*/
void drawMatFlow(CvPoint p, CvPoint q, Mat framedst);
#endif