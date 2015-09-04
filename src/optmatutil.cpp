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

int balanceForDenseMat(Mat flow, Mat framedst, int threshold, float k, int px, int py, float edge ){
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


