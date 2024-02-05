#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"
using color=vec3;
void write_color(std::ostream &out, color pixelColor){
	out<<static_cast<int>(255.99*pixelColor.x())<<' '
		<<static_cast<int>(255.99*pixelColor.y())<<' '
		<<static_cast<int>(255.99*pixelColor.z())<<'\n';
}
#endif