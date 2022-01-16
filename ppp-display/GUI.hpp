//
//  GUI.hpp
//  ppp-display
//
//  Created by Xin Li on 1/16/22.
//

#ifndef GUI_hpp
#define GUI_hpp

#include "Window.hpp"

namespace Graph_lib {

typedef void* Address; //Address is a synonym for void*
typedef void(*Callback)(Address, Address); // FLTK's required function type for all callbacks

template<class W> W& reference_to(Address pw)
// treat an address as a reference to a W, so we can use class W functions directly instead of working with raw address
{
    return *static_cast<W*>(pw);
}

class Widget {
    // Widget is a handle to an Fl_widget - it is *not* an Fl_widget
    // We try to keep our interface classes at arm's length from FLTK
public:
    
    Widget(Point xy, int w, int h, const string& s, Callback cb)
    : loc(xy), width(w), height(h), label(s), do_it(cb){}
    
    virtual void move(int dx, int dy){
        hide();
        pw->position(loc.x += dx, loc.y += dy);
        show();
    }
    virtual void hide() {pw->hide();}
    virtual void show() {pw->show();}
    virtual void attach(Window&) = 0; // attach a concrete Widget to Window, creating an using underlying Fl_Widget here
    
    Point loc;
    int width;
    int height;
    string label;
    Callback do_it;
    
    virtual ~Widget(){}
    
    
protected:
    Window* own;    // every Widget belongs to a Window
    Fl_Widget* pw;  // connection to the FLTK Widget
private:
    // prevent copying
    Widget(const Widget&);
    Widget& operator=(const Widget&);
};

struct Button: Widget{
    Button(Point xy, int w, int h, const string& label, Callback cb)
    : Widget(xy, w, h, label, cb){}
    
    void attach(Window&);
};


}




#endif /* GUI_hpp */
