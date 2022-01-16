//
//  Graph.hpp
//  ppp-display
//
//  Created by Xin Li on 1/16/22.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include "Point.h"

namespace Graph_lib{


class Shape{
    /*
     Shape is made of points
     Shape can draw and move
     */
public:
    void draw() const;
    virtual void move(int dx, int dy);
    
    Point point(int i) const {return points[i];}
    int number_of_points() const {return int(points.size());}
    
    virtual ~Shape(){}
    
protected:
    Shape(){}  // only created by concrete child classes
    virtual void draw_lines() const;
    void add(Point p) {points.push_back(p);}
    void set_point(int i, Point p){points[i] = p;}
private:
    std::vector<Point> points;      // shape is made of points
    
    // prevent copying
    Shape(const Shape&); // copy-constructor
    Shape& operator=(const Shape&); //copy-assignment
};

// a Line is a Shape defined by two Points
struct Line: Shape {
    Line(Point p1, Point p2){
        add(p1);
        add(p2);
    }
};



}




#endif /* Graph_hpp */
