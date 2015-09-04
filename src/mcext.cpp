#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#include "mex.h"
#include "mcext.h"

using namespace cv;

IplImage* mxArray2IplImage8U3(const mxArray* mx){
	int r,c,sz;
	r = mxGetM(mx);
	c = mxGetN(mx);
    c = c/3;
	sz = r*c;

	double* img = mxGetPr(mx);

	IplImage* im = cvCreateImage(cvSize(c,r),IPL_DEPTH_8U,3);

	int step = im->widthStep/sizeof(uchar);
	uchar* imdata = (uchar* )im->imageData;

	for(int j=0;j<c;j++)
	{
		for(int i=0;i<r;i++)
		{
			imdata[i*step+j*3+2] = (uchar)img[i+j*r];
			imdata[i*step+j*3+1] = (uchar)img[i+j*r+sz];
			imdata[i*step+j*3+0] = (uchar)img[i+j*r+2*sz];
		}
	}
	return im;
}

mxArray* IplImage2mxArray8U3(IplImage* im)
{
	int r,c,sz;
	r = im->height;
	c = im->width;
	//c = c/3;
	sz = r*c;
	mwSize dims[3] = {r, c, 3};

	mxArray* mx = mxCreateNumericArray(3, dims, mxUINT8_CLASS, mxREAL);
	uchar* img = (uchar*)mxGetData(mx);

	int step = im->widthStep/sizeof(uchar);
	uchar* imdata = (uchar* )im->imageData;

	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			img[i+j*r] = imdata[i*step+j*3+2];
			img[i+j*r+sz] = imdata[i*step+j*3+1];
			img[i+j*r+2*sz] = imdata[i*step+j*3+0];
		}
	}
	return mx;
}

Mat mxArray2cvMat8U3(const mxArray* mx){
	int r,c,sz;
	r = mxGetM(mx);
	c = mxGetN(mx);
	c = c/3;
	sz = r*c;
	double* img = mxGetPr(mx);
	Mat mat(r, c, CV_8UC3); 

	for (int j = 0; j < c; j++)
	{
		for (int i = 0; i < r; i++)
		{
			mat.row(i).col(j).data[2] = (uchar)img[i+j*r];
			mat.row(i).col(j).data[1] = (uchar)img[i+j*r+sz];
			mat.row(i).col(j).data[0] = (uchar)img[i+j*r+2*sz];
		}
	}
	return mat;

}

mxArray* cvMat2mxArray8U3(Mat mat){
	int r,c,sz;
	r = mat.rows;
	c = mat.cols;
	//c = c/3;
	sz = r*c;
	mwSize dims[3] = {r, c, 3};
	mxArray* mx = mxCreateNumericArray(3, dims, mxUINT8_CLASS, mxREAL);
	uchar* img = (uchar*)mxGetData(mx);
	for (int j = 0; j < c; j++)
	{
		for (int i = 0; i < r; i++)
		{
			img[i+j*r] = (uchar)mat.row(i).col(j).data[2];
			img[i+j*r+sz] = (uchar)mat.row(i).col(j).data[1];
			img[i+j*r+2*sz] = (uchar)mat.row(i).col(j).data[0];
		}
	}
	return mx;
}

