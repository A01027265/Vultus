#include "module1.hpp"
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp> // for cascade classifier
#include <iostream>

using namespace std;
using namespace cv;

Module1::Module1(const string path)
{
	FACEMODEL = path;
}

void Module1::detectFaces(vector<Rect> &faces, const Mat image)
{
	//Load cascade
	CascadeClassifier face_cascade;
	// Load classifiers
	if (!face_cascade.load(FACEMODEL))
	{
		cout << "Error loading face cascade\n"
				 << "Check path in \"module1.cpp\"\n";
	}
	else
	{
		// Detect faces
		face_cascade.detectMultiScale(image, faces);
		cout << "[Module 1] | Faces found: " << faces.size() << "\n";
	}
};
