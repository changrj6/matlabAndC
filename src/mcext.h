#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#include "mex.h"

using namespace cv;

IplImage* mxArray2IplImage8U3(const mxArray* mx);

mxArray* IplImage2mxArray8U3(IplImage* im);

Mat mxArray2cvMat8U3(const mxArray* mx);

mxArray* cvMat2mxArray8U3(Mat mat);

