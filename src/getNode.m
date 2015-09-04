function [ world, fig, node ] = getNode( wrlFile, nodeName )
%GET Summary of this function goes here
%   Detailed explanation goes here
    world = vrworld(wrlFile);
    open(world);
    fig = view(world, '-internal');
    get(world);
    nodes(world);
    node = vrnode(world, nodeName);
end

