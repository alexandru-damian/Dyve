#pragma once
#include <cv.h>
#include <highgui.h>
class Morphology
{
public:
	Morphology(void);
	~Morphology(void);
	cv::Mat ApplyMorphology(cv::Mat & original)
	{
		cv::Mat newcountoursimage = original.clone();
		cv::Mat gray, grayclone;
		cv::cvtColor(original, gray, CV_BGR2GRAY);
		cv::threshold(gray, gray, 100, 255, CV_THRESH_OTSU);
		grayclone = gray.clone();
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(gray, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
		for (int i = 0; i<contours.size(); i++)
		{
			cv::drawContours(newcountoursimage, contours, i, cv::Scalar(255, 0, 0), 2);
		}

		cv::dilate(grayclone, grayclone, cv::Mat(), cv::Point(-1, -1), 7);

		cv::findContours(grayclone, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
		for (int i = 0; i<contours.size(); i++)
		{
			cv::drawContours(newcountoursimage, contours, i, cv::Scalar(0, 0, 255), 2);
		}
		return newcountoursimage;
	}
};

