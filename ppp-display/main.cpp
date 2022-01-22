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
    win.attach(lines);
    win.attach(grid);
    win.attach(rect);
    
    // color palette
    Vector_ref<Rectangle> vr;
    int x0 = 250, y0 = 50;
    for(int i=0; i < 16; ++i)
        for(int j=0; j < 16; ++j){
            vr.push_back(new Rectangle{Point{x0+i*20, y0+j*20}, 20, 20});
            vr[vr.size() - 1].set_fill_color(Color(i*16+j));
            win.attach(vr[vr.size()-1]);
        }
    
    // marked polylines
    Marked_polyline mp{"abcd"};
    mp.add({50, 380});
    mp.add({70, 350});
    mp.add({100, 320});
    mp.add({150, 300});
    win.attach(mp);
    
    // circle and ellipse
    Circle c = Circle({100, 250}, 50);
    c.set_color(Color::red);
    c.set_style(Line_style(Line_style::solid, 2));
    
    Ellipse e = Ellipse({200, 300}, 100, 50);
    e.set_color(Color::black);
    e.set_style(Line_style(Line_style::dash, 2));
    win.attach(c);
    win.attach(e);
    
    // draw and display
    win.wait_for_button();
    
    // start a new window
    Simple_window win2{top_left, 1200, 800, "Canvas2"};
    // a new set of shapes to display
    // Text
    Text t{{10, 20}, "This is a text"};
    t.set_color(Color::blue);
    t.set_font(Font::helvetica_bold_italic);
    t.set_font_size(20);
    win2.attach(t);
    // Functions plots
    int xmax = win2.x_max();
    int ymax = win2.y_max();
    Point orig{xmax/2, ymax/2};
    double rmin = -10, rmax=11;
    int npoints = 100;
    double xscale = 30, yscale=30;
    Function s0{[](double){return 1.0;}, rmin, rmax, orig, npoints, xscale, yscale};
    Function s1{[](double x){return x/2;}, rmin, rmax, orig, npoints, xscale, yscale};
    Function s2{[](double x){return x*x;}, rmin, rmax, orig, npoints, xscale, yscale};
    Function s3{std::cos, rmin, rmax, orig, npoints, xscale, yscale};
    s3.set_style(Line_style(Line_style::dot));
    s3.set_color(Color::blue);
    
    win2.attach(s0);
    win2.attach(s1);
    win2.attach(s2);
    win2.attach(s3);
    
    // add xy axis
    int xlength = xmax - 40;
    int ylength = ymax - 40;
    
    Axis x{Axis::x, Point{20, orig.y}, xlength, int(xlength/xscale), "one notch == 1"};
    Axis y{Axis::y, Point{orig.x, ylength+20}, ylength, int(ylength/yscale), "one notch == 1"};
    x.set_color(Color::dark_red);
    y.set_color(Color::dark_red);
    win2.attach(x);
    win2.attach(y);
    
    // add image
    std::string img_dir = "/Users/xin/cpp/ppp-display/ppp-display/data/";
    Image img1 {Point{orig.x + 20, orig.y + 50}, img_dir + "done.jpg"};
    win2.attach(img1);
    win2.wait_for_button();
    
    return 0;
}
