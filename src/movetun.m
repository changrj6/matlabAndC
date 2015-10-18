function [ result] = movetun( funcname, fig, View1, varargin )
%MOVE Summary of this function goes here
%   Detailed explanation goes here
    %��ʼ��������
    strategic = 7; % ����ʹ����Щ�����㷨��1 - ���ҹ������ԣ�3 - ������ͼ��7 - ������ת��Ϊ��ɫ
    if nargin == 4
        strategic = varargin{1};
    end
    originX = 0; %View1.position��ʼx
    originY = 0; %View1.position��ʼy
    originZ = 4; %View1.position��ʼz
    skip = 1; %View1.position ÿ���˶�����
    distance = 280; % View1.position��
    width = 10; % �����ȣ����ڼ����ӽǵ�View1.orientation
    ori = 1.57; % ��ת90��
    gap = 10; %LK/HS ����ƫ�ƴ�С��������
    if strcmp(funcname, 'BM') 
        gap = 10;
    end
    %��ȡ��Ƶ
    View1.position=[originX originY originZ];
    writerflow = VideoWriter('../video/flow.avi');
    writerflow.FrameRate = 10;
    open(writerflow);
    View1.orientation = [0 0 1 0];
    writercolor = VideoWriter('../video/color.avi');
    writercolor.FrameRate = 10;
    open(writercolor);
    turn  = 0; %����ƫ����
    result = zeros(distance+10, 8); %���turn,����·��,��orientation
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
        %����ǰ����֡ͼ���ȡ����������ƫ����,������
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
