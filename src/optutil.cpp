#include "stdafx.h"
#include "optutil.h"
#include <cv.h>

using namespace std;
using namespace cv;

/***************************************************************************************/
/*    根据TTC，标记是否为安全区域，暂定大于ttcAvg为安全1，反之，不安全0，然后再调整        
      cols 列数；ttc：计算的ttc数组；ttcAvg：ttc平均值；k：比例系数
      tagSafe : 通过比较规则获得是否安全，标记之                                       */
/***************************************************************************************/
void tagSafeAreaByTTC(int cols, float* ttc, float ttcAvg , float k,int *tagSafe){
	for (int i = 0; i < cols; i++)
	{
		if (ttc[i] > ttcAvg*k)
		{
			tagSafe[i] = 1;
		}
	}
}

/***************************************************************************************/
/*  判定标记是否准确。安全判定安全1，安全非安全2，非安全判定安全3，非安全判定非安全4    
  tagOrigin: 准确的tag标记； tagSafe：根据算法估计的tag标记；tags：根据上述原则判定结果
  函数返回：根据1-4结果，返回此光流方法避撞的评价指数,值越大性能越差                   */
/***************************************************************************************/
float compareTag(int *tagOrigin, int *tagSafe, int cols, int *tags){
	int tag_1 = 0, tag_2 = 0, tag_3 = 0, tag_4 = 0;
	for (int i = 0; i < cols; i++)
	{
		if (tagOrigin[i] == 1 && tagSafe[i] == 1)
		{
			tags[i] = 1;
			tag_1++;
		}else if (tagOrigin[i] == 1 && tagSafe[i] == 0)
		{
			tags[i] = 2;
			tag_2++;
		}else if (tagOrigin[i] == 0 && tagSafe[i] == 1)
		{
			tags[i] = 3;
			tag_3++;
		} 
		else if (tagOrigin[0] == 0 && tagSafe[i] == 0)
		{
			tags[i] = 4;
			tag_4++;
		}
	}
	return tag_1 + tag_2*1.5 + tag_3*2 + tag_4;//各比例项暂定1-1.5-2-1；
}

void drawFlow(CvPoint p, CvPoint q, IplImage* imgdst){
	double angle; 
	angle = atan2((double) p.y - q.y, (double) p.x - q.x);
	double hypotenuse; 
	hypotenuse = sqrt(((p.y - q.y)*(p.y - q.y) +(p.x - q.x)*(p.x - q.x))*1.0);
	
	q.x = (int) (p.x - 3 * hypotenuse * cos(angle));
	q.y = (int) (p.y - 3 * hypotenuse * sin(angle));
	cvLine(imgdst, p, q, CV_RGB(0,0,255),1);

	p.x = (int) (q.x + 2 * hypotenuse * cos(angle + CV_PI / 4));
	p.y = (int) (q.y + 2 * hypotenuse * sin(angle + CV_PI / 4));
	cvLine(imgdst, p, q, CV_RGB(0,0,255),1 );
	p.x = (int) (q.x + 2 * hypotenuse * cos(angle - CV_PI / 4));
	p.y = (int) (q.y + 2 * hypotenuse * sin(angle - CV_PI / 4));
	cvLine(imgdst, p, q, CV_RGB(0,0,255),1 );
	
}
void drawMatFlow(CvPoint p, CvPoint q, Mat framedst){
	double angle; 
	angle = atan2((double) p.y - q.y, (double) p.x - q.x);
	double hypotenuse; 
	hypotenuse = sqrt(((p.y - q.y)*(p.y - q.y) +(p.x - q.x)*(p.x - q.x))*1.0);

	q.x = (int) (p.x - 3 * hypotenuse * cos(angle));
	q.y = (int) (p.y - 3 * hypotenuse * sin(angle));
	line(framedst, p, q, CV_RGB(0,0,255),1);

	p.x = (int) (q.x + 2 * hypotenuse * cos(angle + CV_PI / 4));
	p.y = (int) (q.y + 2 * hypotenuse * sin(angle + CV_PI / 4));
	line(framedst, p, q,CV_RGB(0,0,255),1 );
	p.x = (int) (q.x + 2 * hypotenuse * cos(angle - CV_PI / 4));
	p.y = (int) (q.y + 2 * hypotenuse * sin(angle - CV_PI / 4));
	line(framedst, p, q, CV_RGB(0,0,255),1 );
}
float balanceControlLR(IplImage* imgdst, CvMat* velx, int leftSumFlow, int rightSumFlow, float k){
    if(isBigObstacle(imgdst, velx)){ //前方遇到同一色巨型障碍物，返回-2
        return -2*INT_FLOAT;
    }
    if(leftSumFlow == 0 || rightSumFlow == 0){
        return turnLRScale(leftSumFlow, rightSumFlow, k);
    }
    float gain = (rightSumFlow*INT_FLOAT)/(leftSumFlow*1.0);
    //return gain;
    if(gain < INT_FLOAT*k && gain > INT_FLOAT/k){
        return 0;
    }else{
        return turnLRScale(leftSumFlow, rightSumFlow, k);
    }
}
bool isBigObstacle(IplImage* imgdst, CvMat* velx){
   uchar *data = (uchar*)imgdst->imageData;
	int step = imgdst->widthStep / sizeof(uchar);
	int channels = imgdst->nChannels;
	int sumR = 0, sumG = 0, sumB = 0;
	int count = 0;
	for(int i = EDGE_OBS*HEIGHT; i < (1-EDGE_OBS)*HEIGHT; i++){
		for(int j = EDGE_OBS*WIDTH; j < (1-EDGE_OBS)*WIDTH; j++ ){
			sumB += (int)data[i*step+j*channels+0];
			sumG += (int)data[i*step+j*channels+1];
			sumR += (int)data[i*step+j*channels+2];
			count ++ ;
		}
	}
	int avgB = sumB / count;
	int avgG = sumG / count;
	int avgR = sumR / count;
	int timers;
	int timerCount = 0;
	int flowZeroCount = 0;
	for(int i = EDGE_OBS*HEIGHT; i < (1-EDGE_OBS)*HEIGHT; i++){
		for(int j = EDGE_OBS*WIDTH; j < (1-EDGE_OBS)*WIDTH; j++ ){
			timers = 0;
			if(abs((int)data[i*step+j*channels+0] - avgB) < COLOR_SCALE){
				timers += 1;
			}
			if(abs((int)data[i*step+j*channels+1] - avgG) < COLOR_SCALE){
				timers += 1;
			}
			if(abs((int)data[i*step+j*channels+2] - avgR) < COLOR_SCALE){
				timers += 1;
			}
			if (timers == 3)
			{
				timerCount ++;
				if (((int) cvGetReal2D(velx, i, j)) == 0)
				{
					flowZeroCount ++;
				}
			}
		}
	}
	float timerPro = (timerCount*1.0)/count;
	float flowZeroPro = (flowZeroCount*1.0)/timerCount;
	if (timerPro > THRESHOLD_TIMER && flowZeroPro > THRESHOLD_ZERO)
	{
		return true;
	}else{
		return false;
	}
}
float turnLRScale(float leftSumFlow, float rightSumFlow, float k){
    if(leftSumFlow == rightSumFlow){
        return 0;
    }else{
        if(K_FLAG){
            k = 1;
        }
        if(leftSumFlow > rightSumFlow){
            return ((leftSumFlow - k*rightSumFlow)*INT_FLOAT)/(leftSumFlow + rightSumFlow);
        }else{
            return ((k*leftSumFlow - rightSumFlow)*INT_FLOAT)/(leftSumFlow + rightSumFlow);
        }
    }
}




