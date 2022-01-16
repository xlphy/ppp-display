//
//  main.cpp
//  ppp-display
//
//  Created by Xin Li on 1/14/22.
//

#include <iostream>
#include "Simple_window.hpp"
#include "Graph.hpp"

int main(int argc, const char * argv[]) {
    // use your simple wrapper
    using namespace Graph_lib;
    
    Point top_left{100, 100};
    Simple_window win{top_left, 600, 400, "Canvas"};
    
    Line line{{0,0}, {200,200}};
    
    // put a shape (line) on window
    win.attach(line);
    win.wait_for_button();
    
    return 0;
}
