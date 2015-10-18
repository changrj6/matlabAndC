#include "mex.h"
#include "opencv/cv.h"  
#include "opencv2/highgui/highgui.hpp"  
#include "stdafx.h"
#include "mcext.h"
#include "navigation.h"
#include "optmatutil.h"
#include "opticalflow.h"
#include "optutil.h"

using namespace cv;

void mexFunction(int nlhs,mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    char funcname[10];  
    int buflens =mxGetNumberOfElements(prhs[0]);  
    mxGetString(prhs[0], funcname, buflens+1);  
    Mat frame_1 = mxArray2cvMat8U3(prhs[1]);
    Mat frame_2 = mxArray2cvMat8U3(prhs[2]);
    int strategic = mxGetScalar(prhs[3]); 
    Mat frame_dst;
    resize(frame_2,frame_dst,Size(WIDTH,HEIGHT),0,0,1);
    Mat color;
    color.create(HEIGHT, WIDTH, CV_8UC3);
    float result;
    if (!strcmp(funcname, "FB"))
    {   
        result = matStrategic(FarneBack, frame_1, frame_2, frame_dst, color, strategic, false);
    }else if (!strcmp(funcname, "SF"))
    {
        result = matStrategic(SimpleFlow, frame_1, frame_2, frame_dst, color, strategic, true);
    }
    mexPrintf("%f \n", result/INT_FLOAT);
    //cvShowImage("img2",img_dst);
    plhs[0] = cvMat2mxArray8U3(frame_dst);
    plhs[1] = cvMat2mxArray8U3(color);
    plhs[2] = mxCreateDoubleMatrix(1, 1, mxREAL);
    double *turn;
    turn = mxGetPr(plhs[2]);
    *turn =  result/INT_FLOAT;

    frame_1.release();
    frame_2.release();
    frame_dst.release();
    color.release();
    
    return;
}

