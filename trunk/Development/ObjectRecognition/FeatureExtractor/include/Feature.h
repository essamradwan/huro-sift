#pragma once

/*!
	\defgroup FeatureExtractor FeatureExtractor module.
*/

#include <string>

#include "opencv2/opencv.hpp"

#include "Thread.h"

//! Abstract class for feature extraction.
/*!
	\ingroup FeatureExtractor
*/
extern "C++" class __declspec(dllexport) Feature : public Thread
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
	*/
	Feature(const std::string& name);

	//! Destructor.
	~Feature(void);

	//! Connects a frame to the feature extractor.
	/*!
		\param frame Output parameter for the current frame.
	*/
	void SetFrame(const cv::Mat& frame);

	std::vector<cv::KeyPoint> keyPoints;	//!< Stores keypoints, i.e. a point feature found by one of many available keypoint detectors.
    cv::Mat descriptors;					//!< The output matrix of descriptors.

protected:
    //! Virtual method for loading algorithm specific settings from the given storage.
	virtual void LoadSettingsFromFileStorage(void) = NULL;

	//! Virtual method for each feature extraction algorithm.
	virtual void Process(void) = NULL;

	//! Virtual method for drawing the extracted features.
	virtual void DrawFeatures(void) = NULL;

	std::string name_;	//!< Name of the current feature extraction procedure.
	cv::Mat frame_;		//!< The current frame.
	double procTime_;	//!< Processing time of the current feature extraction method.

private:
	//! Implemented virtual method for the algorithm.
	/*!
		\sa Thread::Run()
	*/
	void* Run(void);

	//! Visualizing the output of feature extractor.
    void Visualize(void);
};