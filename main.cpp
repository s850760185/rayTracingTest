#include "fstream"
#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include "iostream"
#include "camera.h"
#include "opencv2/opencv.hpp"

// #include<bits/stdc++.h>

#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;using namespace cv;
void initCode(){
	fast_io;
	#ifndef ONLINE_JUDGE
	// freopen("input.txt","r",stdin);
	freopen("output.ppm","w",stdout);
	#endif
}
void showppm(string s1);
int main(){
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
    world.add(make_shared<sphere>(point3(0,0,-1), 0.3));
	// camera;
    camera cam;
    cam.aspect_ratio=16.0/9.0;
    cam.image_width=400;
    cam.render_withCV(world);
	// cam.showppm("./output.ppm");
}
