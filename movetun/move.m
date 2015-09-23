world = vrworld('move1.wrl');
open(world);
fig = view(world, '-internal');
get(world);
nodes(world);
L = vrnode(world,'Left');
L.translation = [0 2 20];
% R = vrnode(world,'Right');
t = 2.5 ;
direction = -1;
v=0.5;
while(1)
L.translation = L.translation + [0 0 -1]*v*direction;
vrdrawnow;
t = t + v*direction;
if(abs(t)>=2.5)
    direction = direction * (-1);
end
pause(0.1);
end