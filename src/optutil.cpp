#include "stdafx.h"
#include "optutil.h"
#include <cv.h>

using namespace std;
using namespace cv;

/***************************************************************************************/
/*    ����TTC������Ƿ�Ϊ��ȫ�����ݶ�����ttcAvgΪ��ȫ1����֮������ȫ0��Ȼ���ٵ���        
      cols ������ttc�������ttc���飻ttcAvg��ttcƽ��ֵ��k������ϵ��
      tagSafe : ͨ���ȽϹ������Ƿ�ȫ�����֮                                       */
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
/*  �ж�����Ƿ�׼ȷ����ȫ�ж���ȫ1����ȫ�ǰ�ȫ2���ǰ�ȫ�ж���ȫ3���ǰ�ȫ�ж��ǰ�ȫ4    
  tagOrigin: ׼ȷ��tag��ǣ� tagSafe�������㷨���Ƶ�tag��ǣ�tags����������ԭ���ж����
  �������أ�����1-4��������ش˹���������ײ������ָ��,ֵԽ������Խ��                   */
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
	return tag_1 + tag_2*1.5 + tag_3*2 + tag_4;//���������ݶ�1-1.5-2-1��
}

float balanceControlLR(bool isBig, int leftSumFlow, int rightSumFlow, float k){
    if(isBig){ //ǰ������ͬһɫ�����ϰ������-2
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

Mat calibrate(Mat img)
{
	double mtx[3][3]={562.89836209,0,           314.41994795,0		   ,552.27825968,   160.37443571,0           ,0           ,1           };
	Mat matrix(Size(3,3),CV_64F,mtx);
	Mat img2;
	Vec<float,5> dist(-5.25438307e-01,3.76324874e-01,-4.78114662e-04,3.51717002e-04,-1.37709825e-01); 
	Mat newcameramtx; 
	newcameramtx = getOptimalNewCameraMatrix(matrix , dist ,Size(img.rows,img.cols), 0,Size(img.rows,img.cols));
	undistort(img,img2,matrix,dist,newcameramtx);
    matrix.release();
    img2.release();
    newcameramtx.release();
	return img2;
}

IplImage* calibrate(IplImage* iplimg)
{
	Mat img(iplimg,false);
	Mat img2 = calibrate(img);
	IplImage iplimg2 = img2;
    img.release();
    img2.release();
	return &iplimg2;
}







