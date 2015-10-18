function [ ] = mexall(func)%1-LK/HS/BM 2-FB/SF 3-pryLK
%GET Summary of this function goes here
%   Detailed explanation goes here
    switch func
        case 1
            mex mainCvMat.cpp mcext.cpp navigation.cpp motioncolor.cpp optcvmatutil.cpp optfeatureutil.cpp optmatutil.cpp opticalflow.cpp optutil.cpp stdafx.cpp
        case 2
            mex mainMat.cpp mcext.cpp navigation.cpp motioncolor.cpp optmatutil.cpp optcvmatutil.cpp optfeatureutil.cpp opticalflow.cpp optutil.cpp stdafx.cpp
        case 3
            mex mainMat.cpp mcext.cpp navigation.cpp motioncolor.cpp optcvmatutil.cpp optfeatureutil.cpp optmatutil.cpp opticalflow.cpp optutil.cpp stdafx.cpp
    end
end