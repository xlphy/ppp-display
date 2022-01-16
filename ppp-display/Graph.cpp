//
//  Graph.cpp
//  ppp-display
//
//  Created by Xin Li on 1/16/22.
//

#include "Graph.hpp"
#include <FL/fl_draw.H>

namespace Graph_lib {

void Shape::draw_lines() const
{
    for(unsigned int i = 1; i < points.size(); ++i)
        fl_line(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
}

void Shape::draw() const
{
    draw_lines();
}

void Shape::move(int dx, int dy)
{
    for (int i = 0; i < points.size(); ++i){
        points[i].x += dx;
        points[i].y += dy;
    }
}



}
