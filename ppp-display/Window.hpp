//
//  Window.hpp
//  ppp-display
//
//  Created by Xin Li on 1/14/22.
//

#ifndef Window_hpp
#define Window_hpp

#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "Point.h"
#include "Graph.hpp"


using std::string;
using std::vector;

namespace Graph_lib{

// forward declaration
// class Shape;
class Widget;

// a simpler Window class derived from Fl_Window
class Window: public Fl_Window{
public:
    // used by users
    // let the system pick the (x, y) location on screen;
    Window(int w, int h, const string& title);
    // top left corner in xy
    Window(const Point& xy, int w, int h, const string& title);
    
    virtual ~Window() {} // will be herited by other class
    
    int x_max() const {return w;}
    int y_max() const {return h;}
    
    void resize(int ww, int hh){w=ww; h=hh; size(ww, hh);}
    
    void set_label(const string& s){copy_label(s.c_str());}
    
    // attach Shape or Widget, need to be modified after attachments
    void attach(Shape& s){shapes.push_back(&s);}
    void attach(Widget& s);
    
    void detach(Shape& s);   // remove s from shapes
    void detach(Widget& w);  // remove w from window (deactivates callbacks)
    
    void put_on_top(Shape& p); // put p on top of other shapes
    
protected:
    // used by child class
    void draw();
private:
    // internal implementation for Window class
    vector<Shape*> shapes; // shapes attached to the window, Shape(Base class), we do not know what exatcly shapes will be attached
    int w, h;
    void init();
};

// helper functions
int gui_main(); // invoke GUI library's main event loop
inline int x_max() {return Fl::w();}  // width of screen in pixels
inline int y_max() {return Fl::h();}  // height of screen in pixels

}

#endif /* Window_hpp */
