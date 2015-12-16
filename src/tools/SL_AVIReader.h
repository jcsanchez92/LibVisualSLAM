/*
 * SL_AviReader.h
 *
 *  Created on: 2010-11-7
 *      Author: Danping Zou
 *		E-mail: dannis.zou@gmail.com
 */

#ifndef SL_AVIREADER_H_
#define SL_AVIREADER_H_
#include <string>
#include "SL_VideoReader.h"

class AVIReader:public VideoReader {
protected:
	uint32_t _timestamp;
	cv::VideoCapture videoCap;
public:
	std::string filePath;
public:
	AVIReader() :
		videoCap(){
			avi = true;
	}
	virtual void open();
	virtual void grabFrame();
	virtual void skip(int nSkippedFrame);
	virtual int getTotalFrame();
	virtual void readCurFrameRGB(cv::Mat& imgdata);
	virtual void readCurFrameGray(cv::Mat& grayImgData);
	virtual void readCurFrame(cv::Mat& rgbdata, cv::Mat&  graydata);
	virtual uint32_t getTimeStamp();

	void grabReadFrame(int Frame, cv::Mat& imgdata);
	void releaseCamera();
};
#endif /* SL_AVIREADER_H_ */
