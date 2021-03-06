
# Feature Extraction

## Authors
[Alejandra Nissan](https://github.com/AlejandraNissan) <br/>
[Carla Pérez](https://github.com/CarlaPerezGavilan) <br/>
[Carlos García](https://github.com/cxrlos)                                                                           

## Description
Module with two main functionalities: 

- return face descriptor when recieving face image (MAT)
- return if faces are the same or different comparing two face descriptors

Computer Vision related scripts, developed for Software Engineering course at "Tecnológico de Monterrey".

# Instructions and Tests 

## Running
- Clone repository
- Inside the Computer_Vision folder run the followinfg commands:
```bash
chmod +x run_container.run
./run_container.run
cd workspace
chmod +x opencv_dlib.run
./opencv_dlib.run
```
- To build the executable run the following commands:
```bash
cd workspace
chmod +x run_cmake
./run_cmake
cd source
make
```

- To run the executable run the following command:
```bash
./FaceDetection <name_second_image>.png <name_second_image>.png
```

- Create an instance of the class FeatureDetection passing the model you are using to call its methods. 
```bash
FeatureDetection *d = new FeatureDetection("net/dlib_face_recognition_resnet_model_v1.dat"); 
```

- Then call the methods:
  * Calculate face descriptor returned in MAT format 
     - using elbp -> getFeatures(Mat input) 
     - using dlib -> getFeatures(Mat input) 
   * Calculate double determining distance between two vector (the smaller teh value the more similar the two pictures are)-> compareFeatures(Mat input_A, Mat input_B, int method)
      - 0: Correlation
      - 1: Chi-Square
      - 2: Intersection 
      - 3: Battacharya
      - 6: Euclidian distance
* There are a total of four methods implemented to determine this distance, although we strongly suggest to use the Battacharya method. This previously-mentioned methods are the following:
    - Battacharya
    - Chi-Squared
    - Euclidian distance
    - Intersection
 
```bash
//This method uses the dlib library 
Mat result = d->getFeatures2(input);

// Calculate comparison between two descriptors with euclidian distance 
double final_result = d->compareFeatures(result, result2, 5);
```
-You can review an example of this in the main file. 
## Required
1. Download dlib
```bash
cd /opt/
git clone https://github.com/davisking/dlib
cd ~/workspace/
cp -r /opt/dlib/dlib/ 
```
2. Include the following "#include "feature_extraction.h"
3. Have the "dlib_face_recognition_resnet_model_v1.dat" model path 
4. Run in docker container
  - Pull
    ```bash
    docker pull https://hub.docker.com/repository/docker/robtry/opencv-420
    ```
  - enable 
  ```bash
    xhost +
   ```
  NOTE: if in mac, remember to download xquartz and open xquartz before running command: https://www.xquartz.org/
  - Run container (MAC)
  ```bash
 sudo docker run -it -v $(pwd):/root/workspace -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=docker.for.mac.host.internal:0 -p 5000:5000 -p 8888:8888 robtry/opencv-420
 ```

## File Structure
- main.cpp - test 
- feature_extraction.cpp- implementation of methods
- feature_extraction.cpp -declaration 
## Tests 
We used four methods to compare the histograms of the images, each of them has a different meaning in the return value. 
* Correlation goes from -1 (worst match) to 1 (best match)
* Chi square goes from 0 (best match) to infinity (worst match)
* Intersection goes from 0 (worst match) to infinity (best match)
* Bhattachrayyya goes from 0 (best match) to 1 (worst match)


|               | img1 - img1   | img1 - img2   | img1 - img3   |
| ------------- |:-------------:| -------------:| -------------:|          
| Correlation   | 1             | 0.590976      | 0.351282      |
| Chi square    | 0             | 216.88        | 57.1766       |
| Intersection  | 59.6146       | 51.6741       | 26.5458       |
| Bhattachrayya | 1.05467 e-8   | 0.305542      | 0.449666      |

## Comparison time

Tested in iMac (Retina 5K, 27-inch, Mid 2015)
Processor: 3.3 GHz Intel Core i5
Memory: 8 GB 1600 MHz DDR3

|  Method       | Time          | 
| ------------- |:-------------:|        
| Correlation   | 53096         | 
| Chi square    | 13846         | 
| Intersection  | 6474          | 
| Bhattachrayya | 34056         | 

## Tests using dlib library
We decided to use the eucledean method to compare de two image descriptors. The following table shows some tests with the usage of this method.
|               | img1 - img1   | img1 - img2   | img1 - img3   |
| ------------- |:-------------:| -------------:| -------------:|   
| Euclidiana    | 0             | 0.900375      | 0.717888      |


## New Library source
http://dlib.net/dnn_face_recognition_ex.cpp.html

## Requirements
### Non-Functional
* FENF-001 The main purpose of the segment of the system is to extract data from a MAT object into a processed MAT object
* FENF-002 The program depends on the following face recognizing libraries:
* opencv2/opencv.hpp
* opencv2/face.hpp
* opencv2/imgcodecs.hpp
* opencv2/highgui.hpp
* opencv2/imgproc.hpp
* dlib/image_processing.h
* dlib/opencv/cv_image.h
* dlib/dnn.h
* dlib/gui_widgets.h
* dlib/clustering.h
* dlib/string.h
* <dlib/image_io.h
* dlib/image_processing/frontal_face_detector.h
* dlib/opencv.h
* dlib/image_transforms.h
* LBP implementation found at https://github.com/bytefish/opencv/blob/master/lbp/lbp.cpp imported as a library

  * opencv2/opencv.hpp
  * opencv2/face.hpp
  * opencv2/imgcodecs.hpp
  * opencv2/highgui.hpp
  * opencv2/imgproc.hpp
  * dlib/image_processing.h
  * dlib/opencv/cv_image.h
  * dlib/dnn.h
  * dlib/gui_widgets.h
  * dlib/clustering.h
  * dlib/string.h
  * <dlib/image_io.h
  * dlib/image_processing/frontal_face_detector.h
  * dlib/opencv.h
  * dlib/image_transforms.h
  * LBP implementation found at https://github.com/bytefish/opencv/blob/master/lbp/lbp.cpp imported as a library
* FENF-003 MAT structures will be used
* FENF-004 The program will be written in C++
* FENF-005 The program must run on a 4GB RAM and Intel Core i3 computer
* FENF-006 All the information given by the client will remain confidential
* FENF-007 Working team: 3 people
* FENF-008 No inappropriate use of the electronic equipment during the development process
* FENF-009 Name: Vultus

### Functional
* FEF-001 The main purpose of the segment of the system is to extract data from a MAT object into a processed MAT object
* FEF-002 The entry interface recieves an aligned image represented as a MAT object
* FEF-003 The program will implement a developed dlib method to abstract the features from the input
* FEF-004 The system will provide a differential result between the two input images
* FEF-005 The histograms will be used to give the resultant difference between the two images
* FEF-006 The exit interface gives a MAT object containing the feature-extraction data. A MAT image after being processed by the LBPH algorithm
