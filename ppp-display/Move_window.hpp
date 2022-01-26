//
//  Move_window.hpp
//  ppp-display
//
//  Created by Xin Li on 1/25/22.
//

#ifndef Move_window_hpp
#define Move_window_hpp

/*Move_window is a test window to move button around
 four ways to make it appear that a button moves around
 show/hide, change location, create new one, and attach/detach
 */
#include "GUI.hpp"
using namespace Graph_lib;

class Move_window: public Graph_lib::Window{
public:
    Move_window(int w, int h, const string& t);
    
    Button* p1; // show/hide
    Button* p2;
    bool sh_left;
    
    Button* mvp; // move
    bool mv_left;
    
    Button* cdp; // create/destroy
    bool cd_left;
    
    Button* adp1; // activate/deactivate
    Button* adp2;
    bool ad_left;
    
    void sh();  // actions
    void mv();
    void cd();
    void ad();
    
    // callbacks
    static void cb_sh(Address, Address addr){reference_to<Move_window>(addr).sh();}
    static void cb_mv(Address, Address addr){reference_to<Move_window>(addr).mv();}
    static void cb_cd(Address, Address addr){reference_to<Move_window>(addr).cd();}
    static void cb_ad(Address, Address addr){reference_to<Move_window>(addr).ad();}
    
};


#endif /* Move_window_hpp */
