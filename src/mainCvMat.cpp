#include "mex.h"
#include "opencv/cv.h"  
#include "opencv2/highgui/highgui.hpp"  
#include "stdafx.h"
#include "mcext.h"
#include "navigation.h"
#include "optcvmatutil.h"
#include "opticalflow.h"
#include "optutil.h"

using namespace cv;

void mexFunction(int nlhs,mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    char funcname[10];  
    int buflens =mxGetNumberOfElements(prhs[0]);  
    mxGetString(prhs[0], funcname, buflens+1);  
  
    IplImage *img_1 = mxArray2IplImage8U3(prhs[1]);
    IplImage *img_2= mxArray2IplImage8U3(prhs[2]);
    int strategic = mxGetScalar(prhs[3]); 
    //mexPrintf("strategic: %d\n", strategic);
    IplImage *img_dst = cvCreateImage(cvSize(WIDTH,HEIGHT), img_2->depth , img_2->nChannels);
    cvResize(img_2, img_dst);
    
    Mat color;
    color.create(HEIGHT, WIDTH, CV_8UC3);
    float result;
    if (!strcmp(funcname, "LK"))
    {
        result = imgStrategic(Lucaskanade, img_1, img_2, img_dst, color, strategic);
    }else if (!strcmp(funcname, "HS"))
    {
        result = imgStrategic(HornSchunck, img_1, img_2, img_dst, color, strategic);
    }
    else if (!strcmp(funcname, "BM"))
    {
        result = imgStrategic(BlockMatch, img_1, img_2, img_dst, color, strategic);
    }
    mexPrintf("%f \n", result/INT_FLOAT);
    //cvShowImage("img2",img_dst);
    plhs[0] = IplImage2mxArray8U3(img_dst);
    plhs[1] = cvMat2mxArray8U3(color);
    plhs[2] = mxCreateDoubleMatrix(1, 1, mxREAL);
    double *turn;
    turn = mxGetPr(plhs[2]);
    *turn =  result/INT_FLOAT;

    cvReleaseImage(&img_1);
    cvReleaseImage(&img_2);
    cvReleaseImage(&img_dst);
    
    return;
}

