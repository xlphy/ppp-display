//
//  Simple_window.cpp
//  ppp-display
//
//  Created by Xin Li on 1/16/22.
//

#include "Simple_window.hpp"
#include <iostream>

Simple_window::Simple_window(Point xy, int w, int h, const string& title) :
    Graph_lib::Window(xy, w, h, title),
    //next_button(Point(x_max() - 70, 0), 70, 20, "Next", cb_next),
    next_button(Point(x_max() - 70, 0), 70, 20, "Next",
                [](Graph_lib::Address, Graph_lib::Address pw){
        Graph_lib::reference_to<Simple_window>(pw).next();
    }),
    button_pushed(false)
{
    attach(next_button);
}

bool Simple_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
    
    while(!button_pushed)
        Fl::wait(); // Fl::wait() will trigger display, which will call window::draw() function, it also capture user actions and trigger callback functions, so button_pushed could be changed by a callback function.
    Fl::redraw();
    
    return button_pushed;
}

/*
void Simple_window::cb_next(Graph_lib::Address, Graph_lib::Address pw)
// call Simple_window::next() for the window located at pw
{
    Graph_lib::reference_to<Simple_window>(pw).next();
}
*/

void Simple_window::next()
// define the action once next button is pushed
{
    button_pushed = true;
    hide();
}
