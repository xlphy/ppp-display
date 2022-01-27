//
//  Lines_window.hpp
//  ppp-display
//
//  Created by Xin Li on 1/26/22.
//

#ifndef Lines_window_hpp
#define Lines_window_hpp

#include "GUI.hpp"
#include "Window.hpp"
#include "Graph.hpp"

struct Lines_window: Graph_lib::Window{
    Lines_window(Point xy, int w, int h, const string& title);
private:
    // data
    Graph_lib::Open_polyline lines;
    
    // widgets
    Graph_lib::Button next_button;
    Graph_lib::Button quit_button;
    Graph_lib::In_box next_x;
    Graph_lib::In_box next_y;
    Graph_lib::Out_box xy_out;
    Graph_lib::Menu color_menu;
    Graph_lib::Button menu_button;
    
    void change(Graph_lib::Color c){lines.set_color(c);}
    void hide_menu(){color_menu.hide(); menu_button.show();}
    // actions invoked by callbacks
    void red_pressed() {change(Graph_lib::Color::red);hide_menu();}
    void blue_pressed() {change(Graph_lib::Color::blue);hide_menu();}
    void black_pressed() {change(Graph_lib::Color::black);hide_menu();}
    void menu_pressed() {menu_button.hide(); color_menu.show();}
    
    void next();
    void quit();
    
    // callback functions stubs
    static void cb_red(Graph_lib::Address, Graph_lib::Address pw){
        Graph_lib::reference_to<Lines_window>(pw).red_pressed();
    }
    static void cb_blue(Graph_lib::Address, Graph_lib::Address pw){
        Graph_lib::reference_to<Lines_window>(pw).blue_pressed();
    }
    static void cb_black(Graph_lib::Address, Graph_lib::Address pw){
        Graph_lib::reference_to<Lines_window>(pw).black_pressed();
    }
    static void cb_menu(Graph_lib::Address, Graph_lib::Address pw){
        Graph_lib::reference_to<Lines_window>(pw).menu_pressed();
    }
    // quit and next callbacks are implemented with lambdas
    
};





#endif /* Lines_window_hpp */
