#include "stdafx.h"
#include <cv.h>
#include "optutil.h"
#include "opticalflow.h"
#include "navigation.h"
#include "optcvmatutil.h"
#include "optfeatureutil.h"
#include "optmatutil.h"
#include "motioncolor.h"

using namespace cv;
using namespace std;

//�������ҹ���ƽ�ⷵ����1��2ǰ3ֹͣ4������Ϊimg���͵Ĺ����㷨
int imgBalance(ImgFunType funtype,IplImage* imgprev, IplImage* imgcurr, IplImage* imgdst){
	//���������ʼ������
	IplImage* imgprev_1 = imgResize(imgprev);
	IplImage* imgcurr_1 = imgResize(imgcurr);
	CvMat *velx, *vely;
	velx = cvCreateMat(HEIGHT, WIDTH, CV_32FC1);
	vely = cvCreateMat(HEIGHT, WIDTH, CV_32FC1);
	cvSetZero(velx);
	cvSetZero(vely);
	//1.�������
	int threshold = funtype(imgprev_1,imgcurr_1,velx,vely);

	// 2.����foe��
	//Vec2i vec2iFOE = foeForDenseCvMat(velx, vely);
	int result = balanceForDenseCvMat(velx, vely, imgdst, threshold);
	printf("balance result : %d\n", result);

	drawFlowForDenseCvMat(velx, vely, imgdst);

	cvReleaseImage(&imgprev_1);
	cvReleaseImage(&imgcurr_1);
	cvReleaseMat(&velx);
	cvReleaseMat(&vely);
	return 0;
}

void imgMotionToColor(ImgFunType funtype,IplImage* imgprev, IplImage* imgcurr, Mat &color){
	 //���������ʼ������
	 IplImage* imgprev_1 = imgResize(imgprev);
	 IplImage* imgcurr_1 = imgResize(imgcurr);
	 CvMat *velx, *vely;
	 velx = cvCreateMat(HEIGHT, WIDTH, CV_32FC1);
	 vely = cvCreateMat(HEIGHT, WIDTH, CV_32FC1);
	 cvSetZero(velx);
	 cvSetZero(vely);
	 //1.�������
	 funtype(imgprev_1,imgcurr_1,velx,vely);

	 motionCvMatToColor(velx, vely, color);

	 cvReleaseImage(&imgprev_1);
	 cvReleaseImage(&imgcurr_1);
	 cvReleaseMat(&velx);
	 cvReleaseMat(&vely);
 }

//�������ҹ���ƽ�ⷵ����1��2ǰ3ֹͣ4������Ϊmat���͵Ĺ����㷨,�������simpleflow�����������issf=true
int matBalance(MatFunType funtype, Mat frameprev, Mat framecurr, Mat framedst,bool issf){
	Mat frameprev_1, framecurr_1, flow;
	if (issf)
	{
		frameprev_1 = matColorResize(frameprev);
		framecurr_1 = matColorResize(framecurr);
	}else{
		frameprev_1 = matResize(frameprev);
		framecurr_1 = matResize(framecurr);
	}

	flow = funtype(frameprev_1, framecurr_1, flow);

	//drawFlowForDenseMat(flow, framedst);
	drawFlowForDenseMat(flow, framedst);

	framecurr_1.release();
	frameprev_1.release();
	flow.release();
	return 0;
}

void matMotionToColor(MatFunType funtype, Mat frameprev, Mat framecurr,Mat &color, bool issf){
	Mat frameprev_1, framecurr_1, flow;
	if (issf)
	{
		frameprev_1 = matColorResize(frameprev);
		framecurr_1 = matColorResize(framecurr);
	}else{
		frameprev_1 = matResize(frameprev);
		framecurr_1 = matResize(framecurr);
	}

	flow = funtype(frameprev_1, framecurr_1, flow);

	//drawFlowForDenseMat(flow, framedst);
	motionMatToColor(flow, color);

	framecurr_1.release();
	frameprev_1.release();
	flow.release();
}

//�������ҹ���ƽ�ⷵ����1��2ǰ3ֹͣ4��Ϊ�����������㷨
int imgFeatureBalance(ImgFeatureFunType funtype,IplImage* imgprev, IplImage* imgcurr, IplImage* imgdst){
	//1.�������
	IplImage* imgprev_1 = imgResize(imgprev);
	IplImage* imgcurr_1 = imgResize(imgcurr);
	IplImage* eig_image=cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_32F,1);
	IplImage* tmp_image=cvCreateImage(cvSize(WIDTH,HEIGHT),IPL_DEPTH_32F,1);
	CvPoint2D32f* cornersprev = new CvPoint2D32f[ MAX_CORNERS ];
	CvPoint2D32f* cornerscurr = new CvPoint2D32f[ MAX_CORNERS ];
	int corner_count = MAX_CORNERS;
	cvGoodFeaturesToTrack(
		imgprev_1,
		eig_image,
		tmp_image,
		cornersprev,
		&corner_count,
		0.01,
		5.0,
		0,
		3,
		0,
		0.04
		);
	cvFindCornerSubPix(
		imgprev_1,
		cornersprev,
		corner_count,
		cvSize(WINSIZE,WINSIZE),
		cvSize(-1,-1),
		cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03)
		);
	funtype(imgprev_1, imgcurr_1, cornersprev, cornerscurr);

	drawFlowForFeatureCvPoint(cornersprev, cornerscurr, imgdst);

	cvReleaseImage(&imgprev_1);
	cvReleaseImage(&imgcurr_1);
	cvReleaseImage(&eig_image);
	cvReleaseImage(&tmp_image);
	free(cornerscurr);
	free(cornersprev);

	return 0;
}

float imgStrategic(ImgFunType funtype, IplImage* imgprev, IplImage* imgcurr, IplImage* imgdst, Mat &color, int strategic){
	//���������ʼ������
	IplImage* imgprev_1 = imgResize(imgprev);
	IplImage* imgcurr_1 = imgResize(imgcurr);
	CvMat *velx, *vely;
	velx = cvCreateMat(HEIGHT, WIDTH, CV_32FC1);
	vely = cvCreateMat(HEIGHT, WIDTH, CV_32FC1);
	cvSetZero(velx);
	cvSetZero(vely);
	//�������
	float k = funtype(imgprev_1,imgcurr_1,velx,vely);

	float result  = 0;
	if ((strategic >> 0 & 1) == 1) //balance
	{
		result = balanceForDenseCvMat(velx, vely, imgdst, k);
		printf("balance result : %d\n", result);
	}    
	if ((strategic >> 1 & 1) == 1) //draw optflow
	{
		drawFlowForDenseCvMat(velx, vely, imgdst);
	}
	if ((strategic >> 2 & 1) == 1) //mation to color
	{
		motionCvMatToColor(velx, vely, color);
	}
	
	cvReleaseImage(&imgprev_1);
	cvReleaseImage(&imgcurr_1);
	cvReleaseMat(&velx);
	cvReleaseMat(&vely);

	return result;
}

int matStrategic(MatFunType funtype, Mat frameprev, Mat framecurr, Mat framedst,Mat &color, int strategic,bool issf){
	Mat frameprev_1, framecurr_1, flow;
	if (issf)
	{
		frameprev_1 = matColorResize(frameprev);
		framecurr_1 = matColorResize(framecurr);
	}else{
		frameprev_1 = matResize(frameprev);
		framecurr_1 = matResize(framecurr);
	}

	flow = funtype(frameprev_1, framecurr_1, flow);

	if ((strategic >> 0 & 1) == 1) //balance
	{
		
	}
	if ((strategic >> 1 & 1) == 1) //draw optflow
	{
		drawFlowForDenseMat(flow, framedst);
	}
	if ((strategic >> 2 & 1) == 1) //mation to color
	{
		motionMatToColor(flow, color);
	}

	framecurr_1.release();
	frameprev_1.release();
	flow.release();
	return 0;
}

