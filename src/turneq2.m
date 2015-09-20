function [ stop, ori] = turneq2(funcname, fig, View1, strategic, ori, t, skip, result)
%MOVE Summary of this function goes here
%   Detailed explanation goes here
    turnSkip = 10; %在遇到同一色的巨型障碍物时，计算前turnSkip的turn之和来确定向左向右旋转90度
    start = 1;
    count = 1;
    if t/skip - turnSkip >= 0
        start = t/skip - turnSkip + 1;
    end
    turnSum = 0;
    for i=start:1:(t/skip)
        turnSum = turnSum + result(i,1);
    end
    while count < 3
        if turnSum < 0
            ori = ori + count*1.57;
        else
            ori = ori - count*1.57;
        end
        View1.orientation = [0 1 0 ori];
        View1.position = View1.position;
        vrdrawnow;
        ima = capture(fig);
        ima_1 = double(ima);
       [imt, color, turn] = mainCvMat(funcname, ima_1, ima_1, strategic);
       if turn == -2
           count =  count + 1;
       else
           break;
       end
    end
    stop = 0;
    if count == 4;
        stop = 1;
    end
end
