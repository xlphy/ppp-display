# ppp-display
Learning Programming Principles and Practice Using C++ (PPP), 2nd Ed, [amazon book](https://www.amazon.com/Programming-Principles-Practice-Using-2nd/dp/0321992784). Ch.12 - 16, basic concepts of graphics and GUI programming. 

## FLTK setup in Xcode
[FLTK](https://www.fltk.org), Fast Light Tool Kit, provides basic utilities to use operating system facilities to perform GUI and graphics programming.

[Youtube guide](https://www.youtube.com/watch?v=HGLeX4AyTXw); [stackoverflow](https://stackoverflow.com/questions/25879961/setup-xcode-and-fltk)

You need configure building settings in the following 3 fields after installing FLTK: Header Search Paths; Library Search Paths; Other Linker Flags

Test a basic example, [more doc](https://www.fltk.org/doc-1.3/basics.html)

```
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
 
int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(340,180);
  Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");
  box->box(FL_UP_BOX);
  box->labelfont(FL_BOLD+FL_ITALIC);
  box->labelsize(36);
  box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show(argc, argv);
  return Fl::run();
}

```






