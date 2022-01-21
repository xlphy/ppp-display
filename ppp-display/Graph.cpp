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

void Rectangle::draw_lines() const
{
    if(fill_color().visibility()){
        // fill
        fl_color(fill_color().as_int());
        fl_rectf(point(0).x, point(0).y, w, h);
    }
    
    if(color().visibility()){
        // lines on top of fill
        fl_color(color().as_int());
        fl_rect(point(0).x, point(0).y, w, h);
    }
}

void Open_polyline::draw_lines() const
{
    if(fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for(int i = 0; i < number_of_points(); ++i){
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());
    }
    
    if(color().visibility())
        Shape::draw_lines();
}

void Closed_polyline::draw_lines() const
{
    // draw "open poly line part" first
    Open_polyline::draw_lines();
    // then draw closing line: from the last to the first
    if(color().visibility())
        fl_line(last_point().x, last_point().y, point(0).x, point(0).y);
}



// does two lines (p1,p2) and (p3,p4) intersect?
// if se return the distance of the intersect point as distances from p1
inline std::pair<double,double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel)
{
    double x1 = p1.x;
    double x2 = p2.x;
    double x3 = p3.x;
    double x4 = p4.x;
    double y1 = p1.y;
    double y2 = p2.y;
    double y3 = p3.y;
    double y4 = p4.y;

    double denom = ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    if (denom == 0){
        parallel= true;
        return std::pair<double,double>(0,0);
    }
    parallel = false;
    return std::pair<double,double>(((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3))/denom,
                                    ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3))/denom);
}


//intersection between two line segments
//Returns true if the two segments intersect,
//in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection){
   bool parallel;
   std::pair<double,double> u = line_intersect(p1,p2,p3,p4,parallel);
   if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
   intersection.x = p1.x + u.first*(p2.x - p1.x);
   intersection.y = p1.y + u.first*(p2.y - p1.y);
   return true;
}

// make sure non-intersecting when adding points one by one
void Polygon::add(Point p)
{
    int np = number_of_points();

    // check that thenew line isn't parallel to the previous one
    if (np > 1) {
        if (p == last_point())
            throw std::runtime_error("polygon point equal to previous point");
        bool parallel;
        line_intersect(point(np-1),p,point(np-2),point(np-1),parallel);
        if (parallel)
            throw std::runtime_error("two polygon points lie in a straight line");
    }
    // check that new segment doesn't interset and old point
    for (int i = 1; i<np-1; ++i) {
        Point ignore(0,0);
        if (line_segment_intersect(point(np-1),p,point(i-1),point(i),ignore))
            throw std::runtime_error("intersect in polygon");
    }

    Closed_polyline::add(p);
}

void Polygon::draw_lines() const
{
    if (number_of_points() < 3)
        throw std::runtime_error("less than 3 points in a Polygon");
    Closed_polyline::draw_lines();
}

// draw a fixed-size (dx * dy) mark(char)
void draw_mark(Point xy, char c)
{
    static const int dx = 4;
    static const int dy = 4;

    std::string m(1,c);
    fl_draw(m.c_str(),xy.x-dx,xy.y+dy);
}

void Marked_polyline::draw_lines() const
{
    Open_polyline::draw_lines();
    for(int i=0; i<number_of_points(); ++i)
        draw_mark(point(i), mark[i % mark.size()]); // cycle through mark which is a string
}


// Circle
Circle::Circle(Point p, int rr): r(rr)
{
    // store top-left corner, but p is center point
    add(Point(p.x-r, p.y-r));
}

Point Circle::center() const{return Point(point(0).x + r, point(0).y + r);}

void Circle::draw_lines() const
{
    if(color().visibility())
        fl_arc(point(0).x, point(0).y, r+r, r+r, 0, 360);
}

void Ellipse::draw_lines() const
{
    if(color().visibility())
        fl_arc(point(0).x, point(0).y, w+w, h+h, 0, 360);
}

void Text::draw_lines() const
{
    int old_fnt = fl_font();
    int old_sz = fl_size();
    fl_font(fnt.as_int(), fnt_sz);
    fl_draw(lab.c_str(), point(0).x, point(0).y);
    fl_font(old_fnt, old_sz); // reset to default
}

Axis::Axis(Orientation d, Point xy, int length, int n, std::string lab):
    label(Point(0, 0), lab)
{
    if (length<0)
        throw std::runtime_error("bad axis length!");
    switch(d){
        case Axis::x:
        {
            // two end points of axis line, left -> right
            Shape::add(xy);
            Shape::add(Point(xy.x+length, xy.y));
            // add notches
            if(n>1){
                int dist = length / n;
                int x = xy.x + dist;
                for (int i=0; i<n; ++i){
                    notches.add(Point(x, xy.y), Point(x, xy.y-5)); // tick length = 5
                    x += dist;
                }
            }
            // label under the line
            label.move(xy.x+length/3, xy.y+20);
            break;
        }
        case Axis::y:
        {
            // two end points of axis line, bottom -> up
            Shape::add(xy);
            Shape::add(Point(xy.x, xy.y-length));
            // add notches
            if(n>1){
                int dist = length / n;
                int y = xy.y - dist;
                for(int i=0; i<n; ++i){
                    notches.add(Point(xy.x, y), Point(xy.x+5, y));
                    y -= dist;
                }
            }
            // label at top
            label.move(xy.x-10, xy.y-length-10);
            break;
        }
        case Axis::z:
        {
            throw std::runtime_error("z axis not implemented!");
        }
    }
    
}

void Axis::draw_lines() const
{
    Shape::draw_lines();
    notches.draw();
    label.draw();
}

void Axis::set_color(Color c)
{
    // set same color
    Shape::set_color(c);
    notches.set_color(c);
    label.set_color(c);
}

void Axis::move(int dx, int dy)
{
    // move together
    Shape::move(dx, dy);
    notches.move(dx, dy);
    label.move(dx, dy);
}








}
