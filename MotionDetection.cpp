#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using namespace cv;
using namespace std;

void devideVideoFrame(VideoCapture cap);
vector<Mat> grayScale(vector<Mat> frames);
vector<Mat> loadFrames(int framesID);
float compareFrame(Mat frameA, Mat frameB, bool verbose);
vector<Mat> gaussianFilter(vector<Mat> pics, int strideX, int strideY, int kernelSize, float sigma, bool verbose);

const float PI = 3.14159265359;

int main(int argc, char** argv)
{
	
	string videoPath = "E:\\Universit‡Magistrale\\secondoSemestre\\PDSProject\\SPR_Project_Unipi\\sample\\testFootage.mp4";
	VideoCapture cap(videoPath);

	//cout << cap.get(CAP_PROP_FRAME_COUNT) << endl;

	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	devideVideoFrame(cap);
	cap.release();
	
	vector<Mat> frames = loadFrames(175);	
	frames = grayScale(frames);
	//imwrite(("E:\\Universit‡Magistrale\\secondoSemestre\\PDSProject\\SPR_Project_Unipi\\sample\\befF.jpg"), frames.at(0));
	
	frames = gaussianFilter(frames, 3, 3, 5, 2,true);
	//imwrite(("E:\\Universit‡Magistrale\\secondoSemestre\\PDSProject\\SPR_Project_Unipi\\sample\\afF.jpg"), frames.at(0));

	cout << "0" << endl;
	Mat base = frames.at(0).clone();
	int totDifference = 0;
	
	for (int f = 0; f < frames.size(); f++) {
		float difference = compareFrame(base, frames.at(f),false);
		cout << difference << endl;
		if (difference > 20) {
			base = frames.at(f).clone();
			totDifference++;
		}
			
	}

	
	cout << "Motion detected in: " << totDifference<<" frames out of "<< frames.size() << endl;
	
	waitKey(0);

	//destroyAllWindows();
	return 0;
}

void devideVideoFrame(VideoCapture cap){

	int fID = 0;
	bool control = true;
	while (control) {
		Mat frame;
		cap >> frame;

		if (frame.empty())
			break;

		string filename = to_string(fID) + ".jpg";
		imwrite(("E:\\Universit‡Magistrale\\secondoSemestre\\PDSProject\\SPR_Project_Unipi\\sample\\"+ filename), frame);

		char c = (char)waitKey(25);

		if (c == 27)
			control = false;
		fID++;

	}
}

vector<Mat> loadFrames(int framesID) {
	vector<Mat> frames;

	for (int i = 0; i < framesID; i++) {
		string filename = to_string(i) + ".jpg";
		frames.push_back( imread("E:\\Universit‡Magistrale\\secondoSemestre\\PDSProject\\SPR_Project_Unipi\\sample\\" + filename ));
	}
	
	return frames;
}

vector<Mat> gaussianFilter(vector<Mat> pics, int strideX, int strideY, int kernelSize, float sigma, bool verbose) {
	
	if (verbose)
		cout << "starting kernel cal phase" << endl;
	
	if (kernelSize % 2 == 0)
		kernelSize++;

	vector<vector<float>> kernelMatrix;
	int offset = kernelSize / 2;
	for (int r = 0; r < kernelSize; r++) {
		
		vector<float> v1;
		for(int c = 0; c < kernelSize; c++){					
			float value = (1 / (2 * PI * powf(sigma, 2))) * (expf(-((powf(r-offset, 2) + powf(c - offset, 2)) / (2 * powf(sigma, 2)))));
			v1.push_back(value);			
		}
		kernelMatrix.push_back(v1);
		
	}
	
	if (verbose) {
		for (int i = 0; i < kernelSize; i++) {
			for (int j = 0; j < kernelSize; j++)
				cout << kernelMatrix[i][j] << " ";
			cout << endl;
		}
	}

	if (verbose)
		cout << "starting convolution phase" << endl;

	vector<Mat> output;
	for (int fID = 0; fID < pics.size();fID++) {
		Mat pic = pics.at(fID);
		//convolution
		for (int r = offset; r < pic.rows; r++) {
			for (int c = offset; c < pic.cols; c++) {
				if (c < pic.cols - kernelSize && r < pic.rows - kernelSize)
				{
					float newRGB = 0;
					for (int rK = 0; rK < kernelSize; rK++) {
						for (int cK = 0; cK < kernelSize; cK++) {

							newRGB += pic.at<Vec3b>(r + rK - 1, c + cK - 1)[0] * kernelMatrix[rK][cK];
						}
					}

					Vec3b pixel = pic.at<Vec3b>(r, c);
					pixel[0] = newRGB;
					pixel[1] = newRGB;
					pixel[2] = newRGB;
					pic.at<Vec3b>(r, c) = pixel;
				}

			}
		}

		output.push_back(pic);
	}
	 
	
	return output;
}

vector<Mat> grayScale(vector<Mat> frames) {

	vector<Mat> grayFrames;
	for (int fID = 0; fID < frames.size(); fID++) {
		Mat frame = frames.at(fID);
		for (int r = 0; r < frame.rows; ++r) {
			for (int c = 0; c < frame.cols; ++c) {
				Vec3b pixel = frame.at<Vec3b>(r, c);
				float av = pixel[0] + pixel[1] + pixel[2];
				av /= 3;
				pixel[0] = av;
				pixel[1] = av;
				pixel[2] = av;
				frame.at<Vec3b>(r, c) = pixel;
			}
		}
		grayFrames.push_back(frame);		
	}

	return grayFrames;	
}


float compareFrame(Mat frameA, Mat frameB, bool verbose) {
	float differencePercentage = 0;
	destroyAllWindows();
	Mat cpya = frameB.clone();
	for (int r = 0; r < frameA.rows; ++r) {
		for (int c = 0; c < frameA.cols; ++c) {
			Vec3b pixelA = frameA.at<Vec3b>(r, c);
			Vec3b pixelB = frameB.at<Vec3b>(r, c);
			if (pixelA[0] > pixelB[0]+7 || pixelA[0] < pixelB[0]-7)
			{			
				differencePercentage++;
				if (verbose) {
					cpya.at<Vec3b>(r, c)[0] = 0;
					cpya.at<Vec3b>(r, c)[1] = 0;
					cpya.at<Vec3b>(r, c)[2] = 255;
				}
			}

		}
	}
	
	if (verbose) {

		imshow("aaa",cpya);
		//cpya.release();	
		waitKey(0);
	}
	
	int nPixel = frameA.rows * frameA.cols;
	return (differencePercentage/nPixel)*100;
}
