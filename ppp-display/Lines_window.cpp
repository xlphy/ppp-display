//
//  Lines_window.cpp
//  ppp-display
//
//  Created by Xin Li on 1/26/22.
//

#include "Lines_window.hpp"
#include <sstream>

/*Construct each widget in window and attach them*/
Lines_window::Lines_window(Point xy, int w, int h, const string& title)
: Graph_lib::Window{xy, w, h, title},
next_button{Point(x_max()-150, 0), 70, 20, "Next point",
    [](Graph_lib::Address, Graph_lib::Address pw){Graph_lib::reference_to<Lines_window>(pw).next();}
},
quit_button{Point(x_max()-70, 0), 70, 20, "Quit",
    [](Graph_lib::Address, Graph_lib::Address pw){Graph_lib::reference_to<Lines_window>(pw).quit();}
},
next_x{Point(x_max()-310, 0), 50, 20, "next x:"},
next_y{Point(x_max()-210, 0), 50, 20, "next y:"},
xy_out{Point(100, 0), 100, 20, "current (x,y):"},
color_menu{Point{x_max()-70, 30}, 70, 20, Graph_lib::Menu::vertical, "color"},
menu_button{Point{x_max()-80, 30}, 80, 20, "color menu", cb_menu}
{
    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    xy_out.put("no point");
    // attach buttons to color_menu
    color_menu.attach(new Graph_lib::Button{Point(0,0), 0, 0, "red", cb_red});
    color_menu.attach(new Graph_lib::Button{Point(0,0), 0, 0, "blue", cb_blue});
    color_menu.attach(new Graph_lib::Button{Point(0,0), 0, 0, "black", cb_black});
    attach(color_menu);
    color_menu.hide();
    attach(menu_button);
    attach(lines);
}

void Lines_window::quit() {hide();}

void Lines_window::next()
{
    int x = next_x.get_int();
    int y = next_y.get_int();
    lines.add(Point(x, y));
    
    // update current position readout
    std::ostringstream ss;
    ss << "(" << x << "," << y << ")";
    xy_out.put(ss.str());
    
    redraw();
}



