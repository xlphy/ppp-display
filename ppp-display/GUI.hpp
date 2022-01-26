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
// first argument is the address of the GUI entity (Widget) for which the callback is triggered;
// second argument is the address of the window containing that Widget. 

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
    
    void attach(Window&) override;
};

struct In_box: Widget{
    In_box(Point xy, int w, int h, const string& s) : Widget(xy, w, h, s, 0){}
    int get_int();
    string get_string();
    
    void attach(Window& win) override;
};

struct Out_box: Widget{
    Out_box(Point xy, int w, int h, const string& s): Widget(xy, w, h, s, 0){}
    void put(int);
    void put(const string&);
    
    void attach(Window& win) override;
};

struct Menu: Widget{
    enum Kind {horizontal, vertical};
    Menu(Point xy, int w, int h, Kind kk, const string& label);
    
    // data member
    Vector_ref<Button> selection;
    Kind k;
    int offset;
    // methods
    int attach(Button& b);  // attach Button to Menu
    int attach(Button* p);  // attach new Button to Menu
    
    void show() override{ // show all buttons
        for (unsigned int i=0; i<selection.size(); ++i)
            selection[i].show();
    }
    void hide() override{ // hide all buttons
        for (unsigned int i=0; i<selection.size(); ++i)
            selection[i].hide();
    }
    void move(int dx, int dy) override{ // move all buttons
        for (unsigned int i=0; i<selection.size(); ++i)
            selection[i].move(dx, dy);
    }
    
    void attach(Window& win) override;  // attach all buttons to win
    
};


}




#endif /* GUI_hpp */
