/*
*  FILE stdafx.h
*  AUTHOR Sarah
*  DATE 2015/08/14 22:27
*  TODO: 标准系统包含文件的包含文件，或是经常使用但不常更改的特定于项目的包含文件
*/
#pragma once

#include <stdio.h>

/*
*  ROWS: 数组申请内存空间大小，大于等于HEIGHT.
*  COLS: 数组申请内存空间大小，大于等于WIDTH.
*  HEIGHT: 重置图像后的�?
*  WIDTH: 重置图像后的�?
*  MAX_CORNERS: PyrLK计算特征点数�?
*  WINSIZE: 窗口大小.
*  DRAWGAP: 画光流的间隔.
*  UNKNOWN_FLOW_THRESH: 大于此�?得光流认为是error光流. 
*/
#define ROWS 350
#define COLS 350
#define HEIGHT 190  
#define WIDTH 288
#define MAX_CORNERS  300
#define WINSIZE 5
#define DRAWGAP 15
#define UNKNOWN_FLOW_THRESH 1e8
#define LK_K 6
#define HS_K 4.3
#define BM_K 1.4
#define FB_K 2
#define SF_K 3
#define INT_FLOAT 100.0 //matlab��int����floatת�������⣬���Խ����100������ʱ�ٳ�100.
#define K_FLAG true  //�ڱ�ײƫ�����У�false��ʾkȡ1����������*_K����
#define EDGE 0 //0.1429
#define EDGE_OBS 0.33
#define COLOR_SCALE 20
#define THRESHOLD_TIMER 0.75 //ͬɫ��ռ������������ͼ���75%������Ϊ��ǽ��ֹͣ��
#define THRESHOLD_ZERO 0.8

