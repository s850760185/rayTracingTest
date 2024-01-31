
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "iostream"
// #include<bits/stdc++.h>

#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;
void initCode(){
	fast_io;
	#ifndef ONLINE_JUDGE
	// freopen("input.txt","r",stdin);
	freopen("output.ppm","w",stdout);
	#endif
}
bool hit_sphere(const point3& center, double radius, const ray& r){
	vec3 oc=r.origin()-center;
	auto a=dot(r.direction(),r.direction());
	auto b=2.0*dot(oc,r.direction());
	auto c=dot(oc,oc)-radius*radius;
	auto discriminant=b*b-4*a*c;
	return (discriminant>=0);
}
color rayColor(const ray& r){
	if (hit_sphere(point3(0,0,-1),0.5,r))
		return color(1,0,0);
	vec3 unit_direction=unit_vector(r.direction());
	auto a=0.5*(unit_direction.y()+1.0);
	return (1.0-a)*color(1.0,1.0,1.0)+a*color(0.5,0.7,1.0);
}
int main(){
	initCode();
	// image
	auto aspectRatio=16.0/9.0;
	int imageWidth=400;
	// Calculate the image height, and ensure that its at least 1.
	int imageHeight=static_cast<int>(imageWidth/aspectRatio);
	imageHeight=(imageHeight<1)?1:imageHeight;
	// camera;
	auto focalLength=1.0;
	auto viewportHeight=2.0;
	auto viewportWidth=viewportHeight*(static_cast<double>(imageWidth)/imageHeight);
	auto cameraCenter=point3(0,0,0);
	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	auto viewportU=vec3(viewportWidth,0,0);
	auto viewportV=vec3(0,-viewportHeight,0);
	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	auto pixeldeltaU=viewportU/imageWidth;
	auto pixeldeltaV=viewportV/imageHeight;
	// Calculate the location of the upper left pixel.
	auto viewportUpperLeft=cameraCenter-vec3(0,0,focalLength)-viewportU/2 - viewportV/2;
	auto pixel00Loc=viewportUpperLeft+0.5*(pixeldeltaU+pixeldeltaV);
	// Render
	cout<<"P3\n"<<imageWidth<<" "<<imageHeight<<"\n255\n";
	for (int j = 0; j < imageHeight; ++j)
	{
		clog<<"\rScanlines remaining: "<<(imageHeight-j)<<" "<<flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			auto pixelCenter=pixel00Loc+(i*pixeldeltaU)+(j*pixeldeltaV);
			auto rayDirection=pixelCenter- cameraCenter;
			ray r(cameraCenter,rayDirection);
			color pixelColor=rayColor(r);
			writeColor(cout,pixelColor);
		}
	}
}