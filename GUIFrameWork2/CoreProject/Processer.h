#pragma once

#include<cv.h>
#include<highgui.h>
#include<vector>

#include"Contours.h"
#include"Histograms.h"
#include"Morphology.h"
class Processer
{
public:
	Processer(void);
	~Processer(void);

	cv::Mat ProcessImage(char* path)
	{

		cv::Mat original = cv::imread(path);
		cv::Mat invertedImage;
		cv::bitwise_not(original, invertedImage);
	
		return invertedImage;
	}

	cv::Mat ProcessAndSaveImage(char *path, char* pathtosave)
	{
		/*cv::Mat original = cv::imread(path);
		cv::Mat invertedImage;
		cv::Mat gauss;
		cv::GaussianBlur(original, gauss, cv::Size(5, 5), 2);

		cv::absdiff(original, gauss, gauss);
		cv::imwrite(pathtosave, gauss);

		return gauss;*/

		/*Contours c;
		cv::Mat original = cv::imread(path);
		cv::Mat processed = c.approximateContours(original);
		cv::imwrite(pathtosave, processed);*/

		//cv::Mat original = cv::imread(path);
		//Histograms h;

		////std::vector<float> hist = h.computeHistogram(original);
		//cv::Mat processed = h.imageSegmentation(original);

		//return processed;

		cv::Mat original = cv::imread(path);
		Morphology m;
		cv::Mat processedimage = m.ApplyMorphology(original);
		return processedimage;
	}

	cv::Mat ProcessVideo()
	{
		cv::Mat frame;
		if (!vc->isOpened())
			vc->open(0);
		if (vc->isOpened())
		{

			vc->retrieve(frame);
			cv::Canny(frame, frame, 50, 100);
		}

		return frame;
	};

private:
	int _counter;
	cv::VideoCapture *vc;
};

