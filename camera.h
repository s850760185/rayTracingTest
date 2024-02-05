#ifndef CAMERA_H
#define CAMERA_H
#include "rtweekend.h"
#include "color.h"
#include "hittable.h"
#include "fstream"
#include "string"
#include "opencv2/opencv.hpp"
using namespace std;using namespace cv;
class camera
{
public:
	double aspect_ratio=1.0;
	int image_width=100;
	void render(const hittable& world){
		initialize();
		fstream f1;
		f1.open("output.ppm");
		if (f1.bad())
		{
			std::cerr<<"bad condition\n";
			return;
		}
		f1<<"P3\n"<<image_width<<' '<<image_height<<' '<<"\n255\n";
		for (int j = 0; j < image_height; ++j)
		{
			for (int i = 0; i < image_width; ++i)
			{
				auto pixel_center=pixel00_loc+(i*pixel_delta_u)+(j*pixel_delta_v);
				auto ray_direction=pixel_center-center;
				ray r(center,ray_direction);
				color pixel_color=ray_color(r,world);
				write_color(f1,pixel_color);
			}
		}
		f1.close();
		std::cout<<"Render complete\n";
	}
	void render_withCV(hittable_list& world){
		initialize();
		Mat img0=Mat(image_height,image_width,CV_8UC3);
		Mat img1=Mat(image_height,image_width,CV_8UC3);
		img0.copyTo(img1);
		for (int j = 0; j < image_height; ++j)
		{
			for (int i = 0; i < image_width; ++i)
			{
				auto pixel_center=pixel00_loc+(i*pixel_delta_u)+(j*pixel_delta_v);
				auto ray_direction=pixel_center-center;
				ray r(center,ray_direction);
				color pixel_color=ray_color(r,world);
				write_opencv_color(img0,pixel_color,i,j);
			}
		}
		imshow("test",img0);
		double x=0.0;
		double y=0.0;
		float index=1.0;
		while(1){
			int a=waitKey(100);
			if (a==191)
			{
				index+=0.1;
				resize(img0,img1,Size((int)image_width*index,(int)image_height*index));
			}else if (a==190)
			{
				index-=0.1;
				resize(img0,img1,Size((int)image_width*index,(int)image_height*index));
			}else if (a==27)
			{
				break;
			}
			else if (a=='a')
			{
				x-=0.1;
				world.objects.pop_back();
				world.add(make_shared<sphere>(point3(x,y,-1),0.3));
				for (int j = 0; j < image_height; ++j)
				{
					for (int i = 0; i < image_width; ++i)
					{
						auto pixel_center=pixel00_loc+(i*pixel_delta_u)+(j*pixel_delta_v);
						auto ray_direction=pixel_center-center;
						ray r(center,ray_direction);
						color pixel_color=ray_color(r,world);
						write_opencv_color(img1,pixel_color,i,j);
					}
				}
			}else if (a=='d')
			{
				x+=0.1;
				world.objects.pop_back();
				world.add(make_shared<sphere>(point3(x,y,-1),0.3));
				for (int j = 0; j < image_height; ++j)
				{
					for (int i = 0; i < image_width; ++i)
					{
						auto pixel_center=pixel00_loc+(i*pixel_delta_u)+(j*pixel_delta_v);
						auto ray_direction=pixel_center-center;
						ray r(center,ray_direction);
						color pixel_color=ray_color(r,world);
						write_opencv_color(img1,pixel_color,i,j);
					}
				}
			}
			else if (a=='w')
			{
				y+=0.1;
				world.objects.pop_back();
				world.add(make_shared<sphere>(point3(x,y,-1),0.3));
				for (int j = 0; j < image_height; ++j)
				{
					for (int i = 0; i < image_width; ++i)
					{
						auto pixel_center=pixel00_loc+(i*pixel_delta_u)+(j*pixel_delta_v);
						auto ray_direction=pixel_center-center;
						ray r(center,ray_direction);
						color pixel_color=ray_color(r,world);
						write_opencv_color(img1,pixel_color,i,j);
					}
				}
			}
			else if (a=='s')
			{
				y-=0.1;
				world.objects.pop_back();
				world.add(make_shared<sphere>(point3(x,y,-1),0.3));
				for (int j = 0; j < image_height; ++j)
				{
					for (int i = 0; i < image_width; ++i)
					{
						auto pixel_center=pixel00_loc+(i*pixel_delta_u)+(j*pixel_delta_v);
						auto ray_direction=pixel_center-center;
						ray r(center,ray_direction);
						color pixel_color=ray_color(r,world);
						write_opencv_color(img1,pixel_color,i,j);
					}
				}
			}
			else{continue;}
			imshow("test",img1);
		}
		waitKey(0);
		destroyAllWindows();
		std::cout<<"Render opencv complete\n";
	}

	void showppm(std::string s1){
		fstream f;
		f.open(s1);
		if(f.bad()) {
			clog<<"failed to open file\n";
			return;
		}
		string s2;
		int a,b,c,imageWidth,imageHeight;
		f>>s2>>imageWidth>>imageHeight>>c;
		Mat img0=Mat(imageHeight,imageWidth,CV_8UC3);
		for (int j = 0; j < imageHeight; ++j)
		{
			for (int i = 0; i < imageWidth; ++i)
			{
				f>>a>>b>>c;
				img0.at<Vec3b>(j,i)[0]=c;
				img0.at<Vec3b>(j,i)[1]=b;
				img0.at<Vec3b>(j,i)[2]=a;
			}
		}
		f.close();
		float index=1.0;
		imshow("test",img0);
		Mat img1(imageWidth,imageHeight,CV_8UC3);
		img0.copyTo(img1);
		while(1){
			a=waitKey(1000
				);
			if (a==191)
			{
				index+=0.1;
				resize(img0,img1,Size((int)imageWidth*index,(int)imageHeight*index));
				imshow("test",img1);
			}else if (a==190)
			{
				index-=0.1;
				resize(img0,img1,Size((int)imageWidth*index,(int)imageHeight*index));
				imshow("test",img1);
			}else if (a==27)
			{
				break;
			}
			else {
				imshow("test",img1);
			}
		}
		destroyAllWindows();
		return;
}
private:
	int image_height;
	point3 center;
	point3 pixel00_loc;
	vec3 pixel_delta_u;
	vec3 pixel_delta_v;
	void initialize(){
		image_height=static_cast<int>(image_width/aspect_ratio);
		image_height=(image_height<1)? 1 :image_height;
		center=point3(0,0,0);
		auto focal_length=1.0;
		auto viewport_height=2.0;
		auto viewport_width=viewport_height*(static_cast<double>(image_width)/image_height);
		auto viewport_u=vec3(viewport_width,0,0);
		auto viewport_v=vec3(0,-viewport_height,0);
		pixel_delta_u=viewport_u/image_width;
		pixel_delta_v=viewport_v/image_height;
		auto viewport_upper_left=center-vec3(0,0,focal_length)-viewport_u/2-viewport_v/2;
		pixel00_loc=viewport_upper_left+0.5*(pixel_delta_u+pixel_delta_v);
	}
	color ray_color(const ray& r,const hittable& world) const{
		hit_record rec;
		if (world.hit(r,interval(0,infinity),rec))
		{
			return 0.5*(rec.normal+color(1,1,1));
		}
		vec3 unit_direction=unit_vector(r.direction());
		auto a=0.5*(unit_direction.y()+1.0);
		return (1.0-a)*color(1.0,1.0,1.0)+a*color(0.5,0.7,1.0);
	}
	void write_opencv_color(Mat m1,color c1, int i,int j){
		m1.at<Vec3b>(j,i)[2]=static_cast<int>(255.999*c1.x());
		m1.at<Vec3b>(j,i)[1]=static_cast<int>(255.999*c1.y());
		m1.at<Vec3b>(j,i)[0]=static_cast<int>(255.999*c1.z());
	}
};
#endif