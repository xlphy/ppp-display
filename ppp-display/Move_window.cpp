//
//  Move_window.cpp
//  ppp-display
//
//  Created by Xin Li on 1/25/22.
//

#include "Move_window.hpp"

Move_window:: Move_window(int w, int h, const string& t)
: Window{w, h, t},
sh_left(true), mv_left(true),cd_left(true), ad_left(true)
{
    p1 = new Button{Point(100, 100), 50, 20, "show", cb_sh};
    p2 = new Button{Point(200, 100), 50, 20, "hide", cb_sh};
    
    mvp = new Button{Point(100, 200), 50 ,20, "move", cb_mv};
    
    cdp = new Button{Point(100, 300), 50 , 20, "create", cb_cd};
    
    adp1 = new Button{Point(100, 400), 50, 20, "activate", cb_ad};
    adp2 = new Button{Point(200, 400), 80 ,20, "deactivate", cb_ad};
    
    attach(*p1);
    attach(*p2);
    attach(*mvp);
    attach(*cdp);
    p2->hide();
    attach(*adp1);
}

// four callbacks, each makes pressed button disappear, and a new button appear
void Move_window::sh()  // hide a button, show another
{
    if(sh_left){
        p1->hide();
        p2->show();
    }else{
        p1->show();
        p2->hide();
    }
    sh_left = !sh_left;
}

void Move_window::mv() // move the button
{
    if(mv_left){
        mvp->move(100, 0);
    }else{
        mvp->move(-100, 0);
    }
    mv_left = !mv_left;
}

void Move_window::cd() // delete the button and create a new one
{
    cdp->hide();
    delete cdp;
    string lab = "create";
    int x = 100;
    if(cd_left){
        lab = "delete";
        x = 200;
    }
    cdp = new Button{Point(x, 300), 50, 20, lab, cb_cd};
    attach(*cdp);
    cd_left = !cd_left;
}

void Move_window::ad() // detach teh button from the window and attach its replacement
{
    if(ad_left){
        detach(*adp1);
        attach(*adp2);
    }else{
        detach(*adp2);
        attach(*adp1);
    }
    ad_left = !ad_left;
}


