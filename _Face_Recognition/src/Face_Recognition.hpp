#ifndef FACE_RECOGNITION_HPP
#define FACE_RECOGNITION_HPP

#include <opencv2/core.hpp>

// Detection
#include "../../Face_Detection/source/FaceDetection.hpp"
#include "../../Face_Alignment/src/faceDetection/module1.hpp"
// Align
#include "../../Face_Alignment/src/faceAlignment/align.hpp"
// Feature Extraction
#include "../../Feature_Extraction/source/feature_detection.h"
// Database
#include "../../Database/src/include/DBManagerInterface.hpp"
#include "../../Database/src/include/Cuatec.hpp"

class FaceRecognition
{
private:
	FaceDetector *faceDetector;
	//Module1 *faceDetector;
	FaceAlignment *faceAligner;
	FeatureDetection *featureDetector;
	DBManagerInterface *db;
	double acceptance_rate;
	int near_neighbors;

	/** Integrate module 1,2 and 3 */
	bool getFeatureDescriptorsFromFrame(const cv::Mat &frame, cv::Mat &featureDescriptors);
	void showMat(const cv::Mat &image);
	void loadModels();

public:
	// Default constructor
	FaceRecognition();

	FaceRecognition(double acceptanceRate);

	/** 
	 * @param acceptanceRate => value > 0
	 * @param nearNeighbors => used in identify to return in result
	*/
	FaceRecognition(double acceptanceRate, int nearNeighbors);

	/**
	 * @param cascadeClassifier => path to haarcascade_frontalface_alt.xml
	 * @link https://github.com/opencv/opencv/blob/master/data/haarcascades/haarcascade_frontalface_alt.xml
	 * @param faceLandmark => path to shape_predictor_5_face_landmarks.dat
	 * @link https://github.com/davisking/dlib-models/blob/master/shape_predictor_5_face_landmarks.dat.bz2
	 * @link https://github.com/davisking/dlib-models/blob/master/shape_predictor_68_face_landmarks.dat.bz2
	 * @param resnetModel => path to dlib_face_recognition_resnet_model_v1.dat
	 * @link https://github.com/davisking/dlib-models/blob/master/dlib_face_recognition_resnet_model_v1.dat.bz2
	*/
	FaceRecognition(const std::string cascadeClassifier, const std::string faceLandmark, const std::string resnetModel);

	FaceRecognition(double acceptanceRate, int nearNeighbors, const std::string cascadeClassifier, const std::string faceLandmark, const std::string resnetModel);

	/** Default deconstructor */
	~FaceRecognition();

	/**
	 * Verify using ID
	 * @param frame => current captured image
	 * @param id => current student
	 * 
	 * @return response:
	 * * 0 : frame and id doesn't match
	 * * 1 : frame and id match
	 * * -1 : there is no face
	 * @return result: if response is 1, matched Cuatec
	*/
	void verify(const cv::Mat &frame, const std::string &id, int &response, Cuatec &result);

	/** 
	 * Identify without using ID
	 * @param frame => current captured image
	 * 
	 * @return response:
	 * * 0 : No identified Cuatec
	 * * 1 : Cuatec has been identified
	 * * -1 : Error in identification process
	 * @return result: matched Cuatect or possible
	*/
	void identify(const cv::Mat &frame, int &response, std::vector<Cuatec> &result);

	/** 
	 * Add new student to database
	 * @param frame => current captured image
	 * @param id => of the new student
	 * @param name => of the new student
	 * 
	 * @return response:
	 * * 0: Can not be created
	 * * 1: Created succesfully
	*/
	void enrollStudent(cv::Mat frame, const std::string id, const std::string name, const int age, int &response);
};

#endif