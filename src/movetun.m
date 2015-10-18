function [ result] = movetun( funcname, fig, View1, varargin )
%MOVE Summary of this function goes here
%   Detailed explanation goes here
    %初始变量设置
    strategic = 7; % 控制使用哪些光流算法，1 - 左右光流策略；3 - 画光流图；7 - 将光流转化为颜色
    if nargin == 4
        strategic = varargin{1};
    end
    originX = 0; %View1.position初始x
    originY = 0; %View1.position初始y
    originZ = 4; %View1.position初始z
    skip = 1; %View1.position 每次运动步长
    distance = 280; % View1.position，
    width = 10; % 隧道宽度，用于计算视角的View1.orientation
    ori = 1.57; % 旋转90度
    gap = 10; %LK/HS 左右偏移大小缩减倍数
    if strcmp(funcname, 'BM') 
        gap = 10;
    end
    %获取视频
    View1.position=[originX originY originZ];
    writerflow = VideoWriter('../video/flow.avi');
    writerflow.FrameRate = 10;
    open(writerflow);
    View1.orientation = [0 0 1 0];
    writercolor = VideoWriter('../video/color.avi');
    writercolor.FrameRate = 10;
    open(writercolor);
    turn  = 0; %左右偏移量
    result = zeros(distance+10, 8); %存放turn,行走路线,和orientation
    degree = View1.fieldOfView/width;
    for t=0:0.1:31
        View1.position = View1.position;
        vrdrawnow;
        ima = capture(fig);
        ima_1 = double(ima);
        View1.position = View1.position - [0 0 t];
        vrdrawnow;
        imb = capture(fig);
        imb_1 = double(imb);
        %根据前后两帧图像获取光流并返回偏移量,左负右正
        if (strcmp(funcname, 'LK')||strcmp(funcname, 'HS')||strcmp(funcname, 'BM'))
            [imt, color, turn] = mainCvMat(funcname, ima_1, imb_1, strategic);
        elseif (strcmp(funcname, 'FB')||strcmp(funcname, 'SF'))
            [imt, color, turn] = mainMat(funcname, ima_1, imb_1, strategic);
        end
        subplot(2,1,1),imshow(imt), title('flow');
        subplot(2,1,2),imshow(color), title('color');
        writeVideo(writerflow, imt);
        writeVideo(writercolor, color);
    end
    for i=0:1:10
        writeVideo(writerflow, imt);
    end
    close(writerflow);
    close(writercolor);
end
