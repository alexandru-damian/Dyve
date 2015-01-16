// This is the main DLL file.

#include "stdafx.h"

#include "Intermediate.h"

namespace Intermediate
{
	char* Mapper::MapToCPPArrayChar(String^ imagePath)
	{
		return (char*)(void*)Marshal::StringToHGlobalAnsi(imagePath);
	}

	BitmapSource^ Mapper::ProcessImage(String^ path)
	{
		char* pathchar = MapToCPPArrayChar(path);
		Processer p;
		cv::Mat image = p.ProcessImage(pathchar);

		return ToBitmapSource(image);
	}

	BitmapSource^ Mapper::ProcessAndSaveImage(String^ path,String^ pathtosave)
	{
		char* pathchar = MapToCPPArrayChar(path);
		char* pathtosavechar = MapToCPPArrayChar(pathtosave);
		Processer p;
		cv::Mat image = p.ProcessAndSaveImage(pathchar, pathtosavechar);

		return ToBitmapSource(image);
	}

	BitmapSource^ Mapper::ProcessVideoFrame()
	{
		cv::Mat image = _processer->ProcessVideo();
		return ToBitmapSource(image);
	}

	array<System::Byte>^ Mapper::ToByteArray(cv::Mat image)
	{
		if (image.channels() != 3)
		{
			cv::Mat auxImage = image.clone();
			image.create(image.size(), CV_8UC3);
			cv::cvtColor(auxImage, image, CV_GRAY2BGR);
		}

		if (image.cols % 4 != 0)
		{
			cv::resize(image.clone(), image, cvSize(image.cols - image.cols % 4, image.rows));
		}

		if (image.rows % 4 != 0)
		{
			cv::resize(image.clone(), image, cvSize(image.cols, image.rows - image.rows % 4));
		}

		int rows = image.rows;
		int cols = image.cols;

		array<System::Byte>^ data = gcnew array<System::Byte>(rows * cols);
		uchar* row;
		int arrayIndex = 0;
		for (int rowIndex = 0; rowIndex < rows; rowIndex++)
		{
			row = image.ptr<uchar>(rowIndex);
			for (int colIndex = 0; colIndex < cols; colIndex++)
			{
				data[arrayIndex++] = row[colIndex];
			}
		}

		return data;
	}

	BitmapSource^ Mapper::ToBitmapSource(cv::Mat image)
	{
		if (image.channels() != 3)
		{
			cv::Mat auxImage = image.clone();
			image.create(image.size(), CV_8UC3);
			cv::cvtColor(auxImage, image, CV_GRAY2BGR);
		}

		if (image.cols % 4 != 0)
		{
			cv::resize(image.clone(), image, cvSize(image.cols - image.cols % 4, image.rows));
		}

		if (image.rows % 4 != 0)
		{
			cv::resize(image.clone(), image, cvSize(image.cols, image.rows - image.rows % 4));
		}

		bool isContinuous = image.isContinuous();
		int cols = image.cols;
		int rows = image.rows;
		int stride = image.cols*image.channels();
		int stride00 = image.step.buf[0];
		uchar* data = image.data;

		IntPtr pointer = IntPtr(const_cast<uchar*>(data));

		Bitmap ^bitmap = gcnew Bitmap(
			cols,
			rows,
			stride,
			PixelFormat::Format24bppRgb,
			pointer);

		IntPtr ip = bitmap->GetHbitmap();

		BitmapSource ^bitmapSource = System::Windows::Interop::Imaging::CreateBitmapSourceFromHBitmap(
			ip,
			IntPtr::Zero,
			Int32Rect::Empty,
			BitmapSizeOptions::FromEmptyOptions());

		DeleteObject(ip);
		return bitmapSource;
	}



}