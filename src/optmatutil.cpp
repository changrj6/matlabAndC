#include "stdafx.h"
#include <cv.h>

#include "optutil.h"
#include "optmatutil.h"

using namespace cv;
using namespace std;

Vec2i foeForDenseMat(Mat flow){
	return Vec2i(0, 0);
}

float ttcForDenseMat(Mat flow, int foeY, float *ttc){
	return 0;
}

float balanceForDenseMat(Mat flow, Mat framedst, float k, int px, int py){
    
	return 0;
}

void drawFlowForDenseMat(Mat flow, Mat framedst){
	int gap = 10;
	for (int i = gap; i < HEIGHT; i += gap)
	{
		for(int j = gap; j < WIDTH; j += gap){
			Vec2i flow_at_point = flow.at<Vec2i>(i, j);
			float fx = flow_at_point[0];
			float fy = flow_at_point[1];
			if (fabs(fx) > UNKNOWN_FLOW_THRESH || fabs(fy) > UNKNOWN_FLOW_THRESH)
			{
				continue;
			}
			CvPoint p, q;
			p.x = j;
			p.y = i;
			q.x = fx + j;
			q.y = fy + i;
			//printf("p: (%d,%d). q :(%d, %d)\n", p.x, p.y, flow.at<Vec2i>(i, j)[0], flow.at<Vec2i>(i, j)[1]);
			drawMatFlow(p, q, framedst);
		}
	}
}

void drawMatFlow(CvPoint p, CvPoint q, Mat framedst){
	double angle; 
	angle = atan2((double) p.y - q.y, (double) p.x - q.x);
	double hypotenuse; 
	hypotenuse = sqrt(((p.y - q.y)*(p.y - q.y) +(p.x - q.x)*(p.x - q.x))*1.0);

	q.x = (int) (p.x - 3 * hypotenuse * cos(angle));
	q.y = (int) (p.y - 3 * hypotenuse * sin(angle));
	line(framedst, p, q, CV_RGB(0,0,255),1);

	p.x = (int) (q.x + 3 * cos(angle + CV_PI / 4));
	p.y = (int) (q.y + 3  * sin(angle + CV_PI / 4));
	line(framedst, p, q,CV_RGB(0,0,255),1 );
	p.x = (int) (q.x + 3 * cos(angle - CV_PI / 4));
	p.y = (int) (q.y + 3 * sin(angle - CV_PI / 4));
	line(framedst, p, q, CV_RGB(0,0,255),1 );
}


