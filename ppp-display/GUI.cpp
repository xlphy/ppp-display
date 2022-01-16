//
//  GUI.cpp
//  ppp-display
//
//  Created by Xin Li on 1/16/22.
//


#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include "GUI.hpp"

namespace Graph_lib {

void Button::attach(Window & win)
{
    pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
    pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window, execute the callback function do_it, which is supplied during the Widget construction
    own = &win;
}

}
