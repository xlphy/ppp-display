//
//  Point.h
//  ppp-display
//
//  Created by Xin Li on 1/14/22.
//

#ifndef Point_h
#define Point_h

struct Point {
    int x, y;
    Point(int xx, int yy): x(xx), y(yy){}
    Point(): x(0), y(0) {}
};

inline bool operator==(const Point& a, const Point& b) {return a.x == b.x && a.y == b.y;}

inline bool operator!=(const Point& a, const Point& b){return !(a==b);}


#endif /* Point_h */
