function [ imt, color, pos] = movecvmat( funcname, fig, View1, varargin )
%MOVE Summary of this function goes here
%   Detailed explanation goes here
    strategic = 1;
    if nargin == 4
        strategic = varargin{1};
    end

    View1.position=[0 0 0];
    writerflow = VideoWriter('../video/flow.avi');
    writerflow.FrameRate = 20;
    open(writerflow);
    
    writercolor = VideoWriter('../video/color.avi');
    writercolor.FrameRate = 20;
    open(writercolor);
    turn  = 0;
    pos = zeros(500, 3);
    for t=0:2:470
        if turn == -2
            break;
        end
        View1.position = View1.position + [turn/10 0 -1];
        pos(t+1,:) = View1.position;
        vrdrawnow;
        ima = capture(fig);
        ima_1 = double(ima);
        View1.position = View1.position + [0 0 -1];
        pos(t+2,:) = View1.position;
        vrdrawnow;
        imb = capture(fig);
        imb_1 = double(imb);
        
        [imt, color, turn] = mainCvMat(funcname, ima_1, imb_1, strategic);
        subplot(2,1,1),imshow(imt), title('flow');
        subplot(2,1,2),imshow(color), title('color');
        writeVideo(writerflow, imt);
        writeVideo(writercolor, color);
    end
    close(writerflow);
    close(writercolor);
end
