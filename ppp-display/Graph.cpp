//
//  Graph.cpp
//  ppp-display
//
//  Created by Xin Li on 1/16/22.
//

#include "Graph.hpp"

namespace Graph_lib {

//----------base class implementation-----------
Shape::Shape():  //default color and style
    lcolor(fl_color()),
    ls(0),
    fcolor(Color::invisible)  // no fill
{}

void Shape::draw_lines() const
{
    if (color().visibility() && 1 < points.size())
        for(unsigned int i = 1; i < points.size(); ++i)
            fl_line(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
}

void Shape::draw() const
{
    Fl_Color oldc = fl_color();
    // there is no good portable way of retrieving the current style
    fl_color(lcolor.as_int());   // set color
    fl_line_style(ls.style(), ls.width());  //set style
    draw_lines();
    fl_color(oldc);   // reset color (to previous)
    fl_line_style(0); // reset line style to default
}

void Shape::move(int dx, int dy)
{
    for (int i = 0; i < points.size(); ++i){
        points[i].x += dx;
        points[i].y += dy;
    }
}

//--------------concrete classes implementations---------
void Lines::add(Point p1, Point p2)
{
    Shape::add(p1);
    Shape::add(p2);
}

void Lines::add(const Line& l){add(l.point(0), l.point(1));}

// draw lines connecting pairs of points
void Lines::draw_lines() const
{
    if(color().visibility())
        for (int i = 1; i < number_of_points(); i += 2)
            fl_line(point(i-1).x, point(i-1).y, point(i).x, point(i).y);
}




}
