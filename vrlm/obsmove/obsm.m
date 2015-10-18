clear;clc;
world = vrworld('obsmove.wrl');
open(world);
fig = view(world, '-internal');
get(world);
nodes(world);
obs = vrnode(world,'obs'); %障碍物
view = vrnode(world,'view1');

%% 障碍物静止，视角朝障碍物运动
view.position = [0 1 0];
obs.translation = [0 0 30];
t = 0 ;
v2 = 0.5 ;
while(t<20)
view.position = view.position + [0 0 1]*v2;
vrdrawnow;
t = t + v2;
pause(0.1);
end

%% 障碍物右移，视角向前
% view.position = [0 1 0];
% obs.translation = [20 0 30];
% t = 0 ;
% v1=0.5;%速度
% v2=0.5;
% while(t<20)
% obs.translation = obs.translation - [1 0 0]*v1;
% view.position = view.position + [0 0 1]*v2;
% vrdrawnow;
% t = t + v2;
% pause(0.1);
% end

%% 障碍物与视角相向运动
% view.position = [0 1 0];
% obs.translation = [0 0 30];
% t = 0 ;
% v1=0.5;%速度
% v2=0.5;
% while(t<10)
% obs.translation = obs.translation - [0 0 1]*v1;
% view.position = view.position + [0 0 1]*v2;
% vrdrawnow;
% t = t + v2;
% pause(0.1);
% end