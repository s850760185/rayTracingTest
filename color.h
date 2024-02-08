#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"
#include "opencv2/opencv.hpp"
using color=vec3;
void write_color(std::ostream &out, color pixelColor,int samples_per_pixel){
	auto r=pixelColor.x();
	auto g=pixelColor.y();
	auto b=pixelColor.z();
	auto scale=1.0/samples_per_pixel;
	r*=scale;
	g*=scale;
	b*=scale;
	out<<static_cast<int>(255.99*pixelColor.x())<<' '
		<<static_cast<int>(255.99*pixelColor.y())<<' '
		<<static_cast<int>(255.99*pixelColor.z())<<'\n';
}
void write_opencv_color(cv::Mat m1,color c1, int i,int j,int samples_per_pixel){
		m1.at<cv::Vec3b>(j,i)[2]=static_cast<int>(255.999*c1.x());
		m1.at<cv::Vec3b>(j,i)[1]=static_cast<int>(255.999*c1.y());
		m1.at<cv::Vec3b>(j,i)[0]=static_cast<int>(255.999*c1.z());
	}
#endif