// Intermediate.h

#include<cv.h>
#include<highgui.h>
#include"../CoreProject/Processer.h"

#pragma once
#include "../CoreProject/Processer.h"
#pragma region namespaces
using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Runtime::InteropServices;
using namespace System::Windows;
using namespace System::Windows::Interop;
using namespace System::Windows::Media::Imaging;

#pragma endregion;

#pragma region API Import
[DllImportAttribute("gdi32.dll")]
extern bool DeleteObject(IntPtr handle);
#pragma endregion


namespace Intermediate {

	public ref class Mapper
	{
	public:
		Mapper()
		{
			_processer = new Processer();
		};
		~Mapper()
		{
			if (_processer != NULL)
			{
				delete _processer;
			}
		};

		static char* MapToCPPArrayChar(String^ imagePath);
		static BitmapSource^ ToBitmapSource(cv::Mat image);
		static BitmapSource^ ProcessImage(String^ path);
		static BitmapSource^ ProcessAndSaveImage(String^ path, String^ pathtosave);
		static BitmapSource^ ProcessVideoFrame();
		static array<System::Byte>^ ToByteArray(cv::Mat image);

	private:
		static Processer *_processer;
	};
}
