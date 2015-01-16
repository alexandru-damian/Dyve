#pragma once

#include <cv.h>
#include <highgui.h>
#include "Morphology.h"
class Processer
{
public:
	Processer(void);
	~Processer(void);

	cv::Mat ProcessImage(char *path)
	{
		cv::Mat original = cv::imread(path);
		Morphology m;
		cv::Mat processedimage = m.ApplyMorphology(original);
		return processedimage;
	};
	cv::Mat ProcessVideo()
	{
		cv::Mat frame;
		if (!vc->isOpened())
			vc->open(0);
		if (vc->isOpened())
		{
			
			vc->retrieve(frame);
			cv::Canny(frame,frame,50,100);
		}

		return frame;
	};
	cv::Mat ProcessAndSaveImage(char *path, char * savetopath)
	{
		cv::Mat original = cv::imread(path);
		cv::Mat invertedimage;
		cv::bitwise_not(original,invertedimage);

		cv::imwrite(savetopath, invertedimage);
		return invertedimage;
	};	
private :
	int _counter;
	cv::VideoCapture *vc;
};

