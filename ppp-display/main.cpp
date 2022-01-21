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
    
    //construct concrete shapes
    Line line{{0,0}, {200,200}};
    Lines lines;
    lines.add(line);
    lines.add({0, 200}, {200,0});
    
    int x_size = win.x_max();
    int y_size = win.y_max();
    int dx = 80, dy = 40;
    Lines grid;
    for(int x = dx; x < x_size; x += dx)
        grid.add({x, 0}, {x, y_size});
    for(int y = dy; y < y_size; y += dy)
        grid.add({0, y}, {x_size, y});
    
    grid.set_color(Color::blue);
    grid.set_style(Line_style::dash);
    
    Rectangle rect({10, 20}, 200, 100);
    rect.set_color(Color::black);
    rect.set_style(Line_style(Line_style::solid, 2));
    rect.set_fill_color(Color::blue);
    
    
    // put a shape (line) on window
    win.attach(grid);
    win.attach(rect);
    win.wait_for_button();
    
    return 0;
}
