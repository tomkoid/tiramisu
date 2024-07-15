#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

int get_framerate() {
  int num_sizes;
  Rotation current_rotation;

  Display *dpy = XOpenDisplay(NULL);
  Window root = RootWindow(dpy, 0);
  XRRScreenSize *xrrs = XRRSizes(dpy, 0, &num_sizes);
  //
  //     GET CURRENT RESOLUTION AND FREQUENCY
  //
  XRRScreenConfiguration *conf = XRRGetScreenInfo(dpy, root);
  short current_rate = XRRConfigCurrentRate(conf);
  SizeID current_size_id =
      XRRConfigCurrentConfiguration(conf, &current_rotation);

  int current_width = xrrs[current_size_id].width;
  int current_height = xrrs[current_size_id].height;
  std::cout << "X11: current monitor framerate: " << current_rate << std::endl;
  std::cout << "X11: current monitor width: " << current_width << std::endl;
  std::cout << "X11: current monitor height: " << current_height << std::endl;

  XCloseDisplay(dpy);

  return current_rate;
}
