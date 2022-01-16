//
//  Window.cpp
//  ppp-display
//
//  Created by Xin Li on 1/14/22.
//

#include "Window.hpp"
#include "GUI.hpp"  // need Widget

namespace Graph_lib{

Window::Window(int ww, int hh, const string& title)
    : Fl_Window(ww, hh, title.c_str()), w(ww), h(hh)
{
    init();
}

Window::Window(const Point& xy, int ww, int hh, const string& title)
    : Fl_Window(xy.x, xy.y, ww, hh, title.c_str()), w(ww), h(hh)
{
    init();
}

void Window::init()
{
    resizable(this);
    show();
}

void Window::draw()
{
    Fl_Window::draw();
    for (unsigned int i=0; i<shapes.size(); ++i) shapes[i]->draw();
}

void Window::attach(Widget& w)
{
    begin();         // FTLK: begin attaching new Fl_Widgets to this window
    w.attach(*this); // let the Widget create its Fl_Widget
    end();           // FTLK: stop attaching new Fl_Widget to this window
}

void Window::detach(Widget& b)
{
    b.hide();
}

void Window::detach(Shape& s)
// guess that the last attached will be first released
{
    for (std::size_t i = shapes.size(); 0 < i; --i)
        if (shapes[i-1]==&s)
            shapes.erase(shapes.begin() + (i-1));
}

void Window::put_on_top(Shape &p)
{
    for (int i = 0; i < shapes.size(); ++i){
        if (&p == shapes[i]){
            for (++i; i < shapes.size(); ++i)
                shapes[i-1] = shapes[i];
            shapes[shapes.size()-1] = &p;
            return;
        }
    }
}

int gui_main(){ return Fl::run(); }  // enter FLTK event loop


}
