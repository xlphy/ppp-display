//
//  Graph.hpp
//  ppp-display
//
//  Created by Xin Li on 1/16/22.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include <string>
#include <cmath>
#include <FL/fl_draw.H>
#include "Point.h"

namespace Graph_lib{

//Vector_ref, store both named and unnamed objects
template<class T>
class Vector_ref {
public:
    Vector_ref(){}
    Vector_ref(T& a) {push_back(a);}
    Vector_ref(T* a, T* b = nullptr, T* c = nullptr, T* d = nullptr){
        if(a) push_back(a);
        if(b) push_back(b);
        if(c) push_back(c);
        if(d) push_back(d);
    }
    
    ~Vector_ref(){
        // only delete owned pointers
        for(int i = 0; i < owned.size(); ++i)
            delete owned[i];
    }
    
    // T& not owned objects, save a copy of its pointer
    void push_back(T& s){ v.push_back(&s);}
    // T* owned objects, save a copy of its pointer and responsible for its lifetime
    void push_back(T* p){v.push_back(p); owned.push_back(p);}
    
    // access reference only not pointers
    T& operator[](int i) {return *v[i];}
    const T& operator[](int i) const {return *v[i];}
    
    int size() const {return v.size();}
private:
    std::vector<T*> v;
    std::vector<T*> owned;
};



// Color is the type we use to represent color, use Color::red
struct Color{
    // scoped enum class
    enum Color_type {
        red = FL_RED,
        blue = FL_BLUE,
        green = FL_GREEN,
        yellow = FL_YELLOW,
        white = FL_WHITE,
        black = FL_BLACK,
        magenta = FL_MAGENTA,
        cyan = FL_CYAN,
        dark_red = FL_DARK_RED,
        dark_green = FL_DARK_GREEN,
        dark_yellow = FL_DARK_YELLOW,
        dark_blue = FL_DARK_BLUE,
        dark_magenta = FL_DARK_MAGENTA,
        dark_cyan = FL_DARK_CYAN
    };
    
    enum Transparency {invisible = 0, visible = 255};
    
    // various constructors
    Color(Color_type cc): c(Fl_Color(cc)), v(visible){}
    Color(Color_type cc, Transparency vv): c(Fl_Color(cc)), v(vv){}
    Color(int cc): c(Fl_Color(cc)), v(visible) {}
    Color(Transparency vv): c(Fl_Color()), v(vv) {}
    Color():c(Fl_Color()), v(visible){} // default one
    
    int as_int() const {return c;}
    char visibility() const {return v;}
    void set_visibility(Transparency vv){v=vv;}
private:
    char v; // visible or invisible
    Fl_Color c;
};

// Line style: width and style
struct Line_style{
    enum Line_style_type {
        solid = FL_SOLID,           // -------
        dash = FL_DASH,             // - - - -
        dot = FL_DOT,               // ........
        dashdot = FL_DASHDOT,       // - . - . - .
        dashdotdot = FL_DASHDOTDOT, // -..-..-..
    };
    
    Line_style(Line_style_type ss): s(ss), w(0) {}
    Line_style(Line_style_type lst, int ww): s(lst), w(ww) {}
    Line_style(int ss): s(ss), w(0) {}
    Line_style():s(0), w(0){} // default
    
    int width() const {return w;}
    int style() const {return s;}
private:
    int s;
    int w;
};


// Shape is made of points, Shape can draw and move,
// Shape also has color and line styles
class Shape{
public:
    void draw() const;
    virtual void move(int dx, int dy);
    
    //line color
    void set_color(Color col){ lcolor = col;}
    Color color() const {return lcolor;}
    // line style
    void set_style(Line_style sty) {ls = sty;}
    Line_style style() const {return ls;}
    // fill color
    void set_fill_color(Color col) {fcolor = col;}
    Color fill_color() const {return fcolor;}
    // points
    Point point(int i) const {return points[i];}
    int number_of_points() const {return int(points.size());}
    Point first_point() const {return points[0];}
    Point last_point() const {return points[number_of_points()-1];}
    
    virtual ~Shape(){}
    
protected:
    Shape();  // default color and style
    virtual void draw_lines() const;
    void add(Point p) {points.push_back(p);}
    void set_point(int i, Point p){points[i] = p;}
private:
    std::vector<Point> points;      // shape is made of points
    Color lcolor; // color for lines
    Line_style ls;
    Color fcolor; // fill color
    
    // prevent copying
    Shape(const Shape&); // copy-constructor
    Shape& operator=(const Shape&); //copy-assignment
};

//---------------add more concrete shapes------------------

// struct default to public inheritance
// a Line is a Shape defined by two Points
struct Line: Shape {
    Line(Point p1, Point p2){
        add(p1);
        add(p2);
    }
};

// a set of lines, each line defined by two points
struct Lines: Shape {
    Lines(){}
    Lines(std::initializer_list<std::pair<Point, Point>> lst){
        for(const auto& p:lst) add(p.first, p.second);
    }
    
    void draw_lines() const override;
    void add(Point p1, Point p2); // add a line defined by two points
    void add(const Line& l);
};

// rectangle: top-left point, width and height
struct Rectangle : Shape {
    Rectangle(Point xy, int ww, int hh): w(ww), h(hh){add(xy);}
    Rectangle(Point top_left, Point bottom_right): w(bottom_right.x - top_left.x), h(bottom_right.y - bottom_right.y){
        add(top_left);
    }
    void draw_lines() const override;
    
    int height() const {return h;}
    int width() const {return w;}
private:
    int h;  // height
    int w;  // width
};

// Open polyline: open sequence of lines
struct Open_polyline : Shape {
    void add(Point p) {Shape::add(p);}
    void draw_lines() const override;
};

// Closed polyline: closed sequence of lines
struct Closed_polyline : Open_polyline {
    void draw_lines() const override;
};

// Polygon: closed sequence of non-intersecting lines
struct Polygon : Closed_polyline {
    void add(Point p);
    void draw_lines() const override;
};

// Marked polyline: is a Open_polyline with marks
struct Marked_polyline: Open_polyline {
    Marked_polyline(const std::string& m) : mark(m) {}
    void draw_lines() const override;
private:
    std::string mark;
};

// Marks: is a Marked_polyline without lines
struct Marks: Marked_polyline {
    Marks(const std::string& m): Marked_polyline(m){
        set_color(Color(Color::invisible));
    }
};

// Mark: is a Marks with one point and one char
struct Mark: Marks{
    Mark(Point xy, char c): Marks(std::string(1, c)){
        add(xy);
    }
};


// Circle: center and radius
struct Circle : Shape{
    Circle(Point p, int rr);
    
    void draw_lines() const override;
    
    Point center() const;
    int radius() const {return r;}
    void set_radius(int rr) {r=rr;}
private:
    int r;
};

// Ellipse: center, min and max distance from center
struct Ellipse: Shape {
    Ellipse(Point p, int ww, int hh): w(ww), h(hh){
        add(Point(p.x-w, p.y-h)); // store top-left point
    }
    
    void draw_lines() const override;
    
    Point center() const {return Point(point(0).x+w, point(0).y+h);}
    Point focus1() const {
        Point c=center();
        if(w >= h)
            return Point(c.x + int(std::sqrt(double(w*w-h*h))), c.y);
        else
            return Point(c.x, c.y + int(std::sqrt(double(h*h-w*w))));
    }
    Point focus2() const {
        Point c=center();
        if(w >= h)
            return Point(c.x - int(std::sqrt(double(w*w-h*h))), c.y);
        else
            return Point(c.x, c.y - int(std::sqrt(double(h*h-w*w))));
    }
    
    void set_major(int ww) {
        Point c=center();
        // maintain the center point
        set_point(0, Point(c.x-ww, c.y-h));
        w=ww;
    }
    int major() const {return w;}
    void set_minor(int hh) {
        Point c= center();
        // maintain the center point
        set_point(0, Point(c.x-w, c.y-hh));
        h=hh;
    }
    int minor() const {return h;}
    
private:
    int w;
    int h;
};

// Font used by Text
class Font{
public:
    enum Font_type {
        helvetica=FL_HELVETICA,
        helvetica_bold=FL_HELVETICA_BOLD,
        helvetica_italic=FL_HELVETICA_ITALIC,
        helvetica_bold_italic=FL_HELVETICA_BOLD_ITALIC,
        courier=FL_COURIER,
        courier_bold=FL_COURIER_BOLD,
        courier_italic=FL_COURIER_ITALIC,
        courier_bold_italic=FL_COURIER_BOLD_ITALIC,
        times=FL_TIMES,
        times_bold=FL_TIMES_BOLD,
        times_italic=FL_TIMES_ITALIC,
        times_bold_italic=FL_TIMES_BOLD_ITALIC,
        symbol=FL_SYMBOL,
        screen=FL_SCREEN,
        screen_bold=FL_SCREEN_BOLD,
        zapf_dingbats=FL_ZAPF_DINGBATS
    };
    
    Font(Font_type ff): f(ff) {}
    Font(int ff): f(ff) {}
    
    int as_int() const {return f;}
private:
    int f;
};

// Text: position point, label, font and font size
struct Text : Shape {
    // the point is the bottom left of the first letter
    Text(Point x, const std::string& s): lab(s), fnt(fl_font()), fnt_sz(fl_size()){add(x);}
    
    void draw_lines() const override;
    
    void set_label(const std::string& s){lab = s;}
    std::string label() const {return lab;}
    void set_font(Font f) {fnt = f;}
    Font font() const {return Font(fnt);}
    void set_font_size(int s){fnt_sz=s;}
    int font_size() const {return fnt_sz;}
    
private:
    std::string lab;
    Font fnt;
    int fnt_sz;
};

// Axis: axis line (two end points), notches (a set of lines, ticks), label(Text)
struct Axis: Shape {
    enum Orientation {x, y, z};
    Axis(Orientation d, Point xy, int length,
         int number_of_notches=0, std::string label="");
    
    void draw_lines() const override;
    void move(int dx, int dy) override;
    void set_color(Color c);
    
    Text label;
    Lines notches;
};

typedef double Fct(double); // a short-hand for function type

// Function: is also a Shape
struct Function : Shape {
    // the function parameters are not stored
    Function(Fct f, double r1, double r2, Point orig,
             int count=100, double xscale=25, double yscale=25);
};

// Image: is also a Shape, external image file
struct Suffix {
    enum Encoding {none, jpg, gif};
};

Suffix::Encoding get_encoding(const std::string& s);

struct Image : Shape {
    Image(Point xy, std::string file_name, Suffix::Encoding e= Suffix::Encoding::none);
    ~Image(){delete p;}
    void draw_lines() const override;
    void set_mask(Point xy, int ww, int hh){w=hh; h=hh; cx=xy.x; cy=xy.y;}
private:
    int w,h; // define "masking box" within image relative to position (cx,cy)
    int cx, cy;
    Fl_Image* p;
    Text fn;
};

struct Bad_image : Fl_Image{
    Bad_image(int h, int w): Fl_Image(h,w,0){}
    void draw(int x, int y, int, int, int, int) {draw_empty(x, y);}
};


}




#endif /* Graph_hpp */
