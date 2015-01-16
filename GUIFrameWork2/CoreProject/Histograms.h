#pragma once

#include<cv.h>
#include<highgui.h>
#include<vector>

class Histograms
{
public:
	Histograms();
	~Histograms();

	std::vector<float> computeHistogram(cv::Mat & original)
	{
		cv::Mat gray;
		cv::cvtColor(original, gray, CV_BGR2GRAY);
		std::vector<float> hist;
		hist.resize(256);

		for (int i = 0; i < gray.cols; ++i)
		{
			for (int j = 0; j < gray.rows; ++j)
			{
				uchar val = gray.at<uchar>(cv::Point(i, j));
				hist[val]++;
			}
		}

		double minval, maxval;

		cv::minMaxLoc(hist, &minval, &maxval);
		for (int i = 0; i < hist.size(); ++i)
		{
			hist[i] = hist[i] / (float)maxval;
		}

		return hist;
	}

	cv::Mat imageSegmentation(cv::Mat & original)
	{
		cv::Mat gray;

		cv::cvtColor(original, gray, CV_BGR2GRAY);
		cv::Mat segmentedImage = original.clone();
		std::vector<float > hist = computeHistogram(original);
		std::vector<cv::Point> contour;
		contour.resize(hist.size());
		
		for (int i = 0; i < hist.size(); ++i)
		{
			contour[i].x = i;
			contour[i].y = hist[i] * 255;
		}

		cv::approxPolyDP(contour, contour, contour.size()* 0.1, false);

		for (int t = 1; t < contour.size() - 1; ++t)
		{
			if (contour[t].y > contour[t - 1].y && contour[t].y > contour[t + 1].y)
			{
				//segment that region
				getRegions(gray, segmentedImage, contour[t - 1].x, contour[t + 1].x);
			}
		}

		return segmentedImage;
	}

	void getRegions(cv::Mat & gray, cv::Mat & segmentedImage, int minX, int maxX)
	{
		cv::Scalar color = cv::Scalar(rand() & 255, rand() & 255, rand() & 255);
		for (int i=0;i< gray.cols ;++i)
		for (int j = 0; j < gray.rows; ++j)
		{
			uchar val = gray.at<uchar>(cv::Point(i, j));
			if (val <= maxX && val >= minX)
			{
			
				segmentedImage.at<cv::Vec<uchar, 3>>(cv::Point(i, j)).val[0] = color.val[0];
				segmentedImage.at<cv::Vec<uchar, 3>>(cv::Point(i, j)).val[1] = color.val[1];
				segmentedImage.at<cv::Vec<uchar, 3>>(cv::Point(i, j)).val[2] = color.val[2];
			}
		}
	}

	cv::Mat displayHistogram(std::vector<float> & hist)
	{
		cv::Mat histogram(500, 255, CV_8UC1);
		histogram = cv::Scalar(255);

		for (int i = 0; i < hist.size(); ++i)
		{
			cv::line(histogram, cv::Point(i, 500), cv::Point(i, 500 * hist[i]), cv::Scalar(0));
		}

		return histogram;
	}
};

