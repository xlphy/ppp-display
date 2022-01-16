//
//  Simple_window.hpp
//  ppp-display
//
//  Created by Xin Li on 1/16/22.
//

#ifndef Simple_window_hpp
#define Simple_window_hpp

#include "GUI.hpp"

// Simple_window is a window with a button and a simple callback action
struct Simple_window: Graph_lib::Window {
    Simple_window(Point xy, int w, int h, const string& title);
    
    bool wait_for_button();  // simple event loop
    
private:
    Graph_lib::Button next_button;  // the "next" button
    bool button_pushed;
    
    static void cb_next(Graph_lib::Address, Graph_lib::Address); // callback for next_button
    
    void next();    // action to be done when next_button is pressed
};


#endif /* Simple_window_hpp */
