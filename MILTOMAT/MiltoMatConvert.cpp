#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/core/core.hpp>+
#include <opencv2/imgproc.hpp>

#include "mil.h"

#include <iostream>
#include <cstdio>

using namespace cv;
using namespace std;

MIL_ID MilApplication;
MIL_ID MilSystem;
MIL_ID MilDigitizer;
MIL_ID MilGrabBuffer;

MIL_INT SizeBit;
MIL_INT SizeBand = 3;
MIL_INT ImageSizeBand, ColorMode, InputMode, ScanMode;
MIL_DOUBLE FrameRate;
MIL_INT64 ImageWidth, ImageHeight;

int main()
{
	MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, M_NULL, &MilDigitizer, M_NULL);

	MdigInquire(MilDigitizer, M_SIZE_X, &ImageWidth);
	MdigInquire(MilDigitizer, M_SIZE_Y, &ImageHeight);
	MdigInquire(MilDigitizer, M_SIZE_BIT, &SizeBit);
	MdigInquire(MilDigitizer, M_SIZE_BAND, &ImageSizeBand);
	MdigInquire(MilDigitizer, M_INPUT_MODE, &InputMode);
	MdigInquire(MilDigitizer, M_COLOR_MODE, &ColorMode);
	MdigInquire(MilDigitizer, M_SCAN_MODE, &ScanMode);
	MdigInquire(MilDigitizer, M_SELECTED_FRAME_RATE, &FrameRate);

	// HW data Load
	MappControl(M_DEFAULT, M_ERROR, M_PRINT_DISABLE); // 에러 출력 방지

	//// Color Buffer 생성 (이미지 버퍼)
	MbufAllocColor(MilSystem,
		ImageSizeBand,
		ImageWidth,
		ImageHeight,
		8 + M_UNSIGNED,
		M_IMAGE + M_GRAB + M_PROC + M_DISP,
		&MilGrabBuffer);

	Mat frame;

	frame.create(ImageHeight, ImageWidth, CV_8UC3); // Mat frame 생성

	while (1) {
		MdigGrab(MilDigitizer, MilGrabBuffer);

		MbufGetColor2d(MilGrabBuffer, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, ImageWidth, ImageHeight, (void*)frame.data);

		imshow("example", frame);

		waitKey(60);

	}

}


