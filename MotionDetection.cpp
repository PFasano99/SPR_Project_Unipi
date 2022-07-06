#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <atomic>
#include <future>
#include <thread>
#include <chrono>
#include <mutex>    
#include <omp.h>


using namespace cv;
using namespace std;

void devideVideoFrame(VideoCapture cap);
Mat grayScale(Mat frames);
vector<Mat> loadFrames(int framesID);
float compareFrame(Mat frameA, Mat frameB, bool verbose);
Mat gaussianFilter(Mat pic, vector<vector<float>> kernelMatrix);
vector<vector<float>> generateKernel(int kernelSize, float sigma, bool verbose);
void sequential(vector<Mat> frames);

void threadParalle(vector<Mat> frames, int nOfThreads);
vector<Mat> map_gray(vector<Mat> input, int nOfWorkers, function<Mat(Mat)>f);
vector<Mat> map_gaussianFilter(vector<Mat> input, int nOfWorkers, Mat(*f)(Mat, vector<vector<float>>));
float parallelCompare(Mat base, Mat frameB, int nOfWorkers, function<void(Mat, Mat, bool, int, int, int, int, float&)>f);
void compareFrame_Range(Mat frameA, Mat frameB, bool verbose, int startR, int startC, int endR, int endC, float &res);
void ffParallel(vector<Mat> frames, int nOfWorkers);
void openMpParallel(vector<Mat> frames, int nOfThreads);



const float PI = 3.14159265359;

int main(int argc, char** argv)
{
	
	auto loadTime = chrono::high_resolution_clock::now();
	string videoPath = "E:\\UniversitÓMagistrale\\secondoSemestre\\PDSProject\\SPR_Project_Unipi\\sample\\testFootage.mp4";
	VideoCapture cap(videoPath);

	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	devideVideoFrame(cap);	
	vector<Mat> frames = loadFrames(cap.get(CAP_PROP_FRAME_COUNT));
	

	auto loadEnd = chrono::high_resolution_clock::now();
	double load_time_taken = (chrono::duration_cast<chrono::nanoseconds>(loadEnd - loadTime).count())* 1e-9;
	cout << "Loading Time: " << fixed << load_time_taken << setprecision(9) << " sec" << endl;

	auto seqTime = chrono::high_resolution_clock::now();

	sequential(frames);

	auto seqTimeEnd = chrono::high_resolution_clock::now();
	double whole_time_taken = (chrono::duration_cast<chrono::nanoseconds>(seqTimeEnd - seqTime).count())*1e-9;
	cout << "Tot seq time: " << fixed << whole_time_taken+ load_time_taken << setprecision(9) << " sec" << endl;

	devideVideoFrame(cap);
	frames = loadFrames(cap.get(CAP_PROP_FRAME_COUNT));
	cout << endl;

	auto threadTime = chrono::high_resolution_clock::now();

	threadParalle(frames, 4);

	auto threadTimeEnd = chrono::high_resolution_clock::now();
	whole_time_taken = (chrono::duration_cast<chrono::nanoseconds>(threadTimeEnd - threadTime).count()) * 1e-9;
	cout << "Tot thread time: " << fixed << whole_time_taken + load_time_taken << setprecision(9) << " sec" << endl;
	cout << endl;

	auto ffTime = chrono::high_resolution_clock::now();

	ffParallel(frames,4);

	auto ffTimeEnd = chrono::high_resolution_clock::now();
	 whole_time_taken = (chrono::duration_cast<chrono::nanoseconds>(ffTimeEnd - ffTime).count()) * 1e-9;
	cout << "Tot FastFlow time: " << fixed << whole_time_taken + load_time_taken << setprecision(9) << " sec" << endl;

	cout << endl;
	auto ompTime = chrono::high_resolution_clock::now();

	openMpParallel(frames, 4);

	auto ompTimeEnd = chrono::high_resolution_clock::now();
	whole_time_taken = (chrono::duration_cast<chrono::nanoseconds>(ompTimeEnd - ompTime).count()) * 1e-9;
	cout << "Tot OpenMp time: " << fixed << whole_time_taken + load_time_taken << setprecision(9) << " sec" << endl;

	cap.release();
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
		imwrite(("E:\\UniversitÓMagistrale\\secondoSemestre\\PDSProject\\SPR_Project_Unipi\\sample\\"+ filename), frame);

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
		frames.push_back( imread("E:\\UniversitÓMagistrale\\secondoSemestre\\PDSProject\\SPR_Project_Unipi\\sample\\" + filename ));
	}
	
	return frames;
}


vector<vector<float>> generateKernel(int kernelSize, float sigma, bool verbose) {
	vector<vector<float>> kMatrix;

	if (verbose)
		cout << "starting kernel cal phase" << endl;

	if (kernelSize % 2 == 0)
		kernelSize++;

	int offset = kernelSize / 2;
	for (int r = 0; r < kernelSize; r++) {

		vector<float> v1;
		for (int c = 0; c < kernelSize; c++) {
			float value = (1 / (2 * PI * powf(sigma, 2))) * (expf(-((powf(r - offset, 2) + powf(c - offset, 2)) / (2 * powf(sigma, 2)))));
			v1.push_back(value);
		}
		kMatrix.push_back(v1);

	}

	if (verbose) {
		for (int i = 0; i < kernelSize; i++) {
			for (int j = 0; j < kernelSize; j++)
				cout << kMatrix[i][j] << " ";
			cout << endl;
		}
	}

	return kMatrix;
}

Mat gaussianFilter(Mat pic, vector<vector<float>> kernelMatrix) {
	
		//convolution
		for (int r = 0; r < pic.rows; r++) {
			for (int c = 0; c < pic.cols; c++) {
				if (c < pic.cols - kernelMatrix.size() && r < pic.rows - kernelMatrix.size())
				{
					float newRGB = 0;
					for (int rK = 0; rK < kernelMatrix.size(); rK++) {
						for (int cK = 0; cK < kernelMatrix.size(); cK++) {
							if((r + rK - 1)>0)
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
 	
	return pic;
}


Mat grayScale(Mat frame) {

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

	return frame;
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

void compareFrame_Range(Mat frameA, Mat frameB, bool verbose, int startR, int startC, int endR, int endC,float &res) {
	
	if (endR > frameA.rows)
		endR = frameA.rows;

	if (endC > frameA.cols)
		endC = frameA.cols;

	float differencePercentage = 0;
	destroyAllWindows();
	Mat cpya = frameB.clone();
	for (int r = startR; r < endR; ++r) {
		for (int c = startC; c < endC; ++c) {
			Vec3b pixelA = frameA.at<Vec3b>(r, c);
			Vec3b pixelB = frameB.at<Vec3b>(r, c);
			if (pixelA[0] > pixelB[0] + 7 || pixelA[0] < pixelB[0] - 7)
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

		imshow("aaa", cpya);
		//cpya.release();	
		waitKey(0);
	}

	int nPixel = frameA.rows * frameA.cols;

	mutex mtx;
	mtx.lock();
	res = (differencePercentage / nPixel) * 100;
	mtx.unlock();
}


void sequential(vector<Mat> frames) {

	auto start = chrono::high_resolution_clock::now();

	for (int fID = 0; fID < frames.size(); fID++)
		frames.at(fID) = grayScale(frames.at(fID));

	auto end = chrono::high_resolution_clock::now();
	double time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "Grayscale time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	start = chrono::high_resolution_clock::now();

	vector<vector<float>> kernelMatrix = generateKernel(5, 2, false);
	for (int fID = 0; fID < frames.size(); fID++)
		frames.at(fID) = gaussianFilter(frames.at(fID), kernelMatrix);

	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "GaussianFilter time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	start = chrono::high_resolution_clock::now();

	//cout << "0" << endl;
	Mat base = frames.at(0).clone();
	int totDifference = 0;

	for (int f = 0; f < frames.size(); f++) {
		float difference = compareFrame(base, frames.at(f), false);
		//cout << difference << endl;
		if (difference > 20) {
			base = frames.at(f).clone();
			totDifference++;
		}

	}
	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "Comparison time : " << fixed << time_taken << setprecision(9) << " sec" << endl;
	cout << "Motion detected in: " << totDifference << " frames out of " << frames.size() << endl;

}


void threadParalle(vector<Mat> frames, int nOfThreads) {
	auto start = chrono::high_resolution_clock::now();
	map_gray(frames, nOfThreads, &grayScale);
	auto end = chrono::high_resolution_clock::now();
	double time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "Grayscale time threads: " << fixed << time_taken << setprecision(9) << " sec" << endl;

	start = chrono::high_resolution_clock::now();
	map_gaussianFilter(frames, nOfThreads, &gaussianFilter);
	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "Gaussian threads : " << fixed << time_taken << setprecision(9) << " sec" << endl;

	start = chrono::high_resolution_clock::now();

	//cout << "0" << endl;
	Mat base = frames.at(0).clone();
	int totDifference = 0;

	for (int f = 0; f < frames.size(); f++) {
		float difference = parallelCompare(base, frames.at(f), nOfThreads, &compareFrame_Range);
		if (difference > 20) {
			base = frames.at(f).clone();
			totDifference++;
		}		
	}
	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "Comparison time : " << fixed << time_taken << setprecision(9) << " sec" << endl;
	cout << "Motion detected in: " << totDifference << " frames out of " << frames.size() << endl;
}

void ffParallel(vector<Mat> frames, int nOfThreads) {

	auto start = chrono::high_resolution_clock::now();

	//ParallelFor pf;
	//pf.parallel_for(0, frames.size(), 1, 0, [&](const long fID) {
	//	frames.at(fID) = grayScale(frames.at(fID));
	//	},nOfThreads);

	auto end = chrono::high_resolution_clock::now();
	double time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "Grayscale time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	start = chrono::high_resolution_clock::now();

	vector<vector<float>> kernelMatrix = generateKernel(5, 2, false);
	//pf.parallel_for(0, frames.size(), 1, 0, [&](const long fID) {
	//	frames.at(fID) = gaussianFilter(frames.at(fID), kernelMatrix);
	//	}, nOfThreads);		

	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "GaussianFilter time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	start = chrono::high_resolution_clock::now();

	//cout << "0" << endl;
	Mat base = frames.at(0).clone();
	int totDifference = 0;

	for (int f = 0; f < frames.size(); f++) {
		float difference = compareFrame(base, frames.at(f), false);
		//cout << difference << endl;
		if (difference > 20) {
			base = frames.at(f).clone();
			totDifference++;
		}

	}
	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "Comparison time : " << fixed << time_taken << setprecision(9) << " sec" << endl;
	cout << "Motion detected in: " << totDifference << " frames out of " << frames.size() << endl;

}


vector<Mat> map_gaussianFilter(vector<Mat> input, int nOfWorkers, Mat(*f)(Mat, vector<vector<float>>)) {

	vector<Mat> result(input.size());
	vector<thread*> threads;
	int nextSlice = input.size() / nOfWorkers;
	int start = 0;
	int end = 0;

	vector<vector<float>> kernelMatrix = generateKernel(5, 2, false);

	auto compute_chunk = [&](pair<int, int> range) {   // function to compute a chunk
		for (int i = range.first; i < range.second; i++) {
			result.at(i) = f(input.at(i), kernelMatrix);
			//imwrite(to_string(i)+"a.jpg", result.at(i));
		}
		return;
	};

	vector<pair<int, int>> ranges(nextSlice);                     // vector to compute the ranges 
	int delta{ (int)input.size() / nextSlice };

	for (int i = 0; i < nextSlice; i++) {                     // split the string into pieces
		ranges[i] = make_pair(i * delta, (i != (nextSlice - 1) ? (i + 1) * delta : input.size()));
		threads.push_back(new thread(compute_chunk, ranges[i]));
	}

	for (int i = 0; i < threads.size(); ++i)
	{
		threads[i]->join();
	}

	return result;
}

vector<Mat> map_gray(vector<Mat> input, int nOfWorkers, function<Mat(Mat)>f) {

	vector<Mat> result(input.size());
	vector<thread*> threads;
	int nextSlice = input.size() / nOfWorkers;
	int start = 0;
	int end = 0;

	auto compute_chunk = [&](pair<int, int> range) {   // function to compute a chunk
		for (int i = range.first; i < range.second; i++) {
			result.at(i) = f(input.at(i));
			//imwrite(to_string(i)+"a.jpg", result.at(i));
		}
		return;
	};

	vector<pair<int, int>> ranges(nextSlice);                     // vector to compute the ranges 
	int delta{ (int)input.size() / nextSlice };

	for (int i = 0; i < nextSlice; i++) {                     // split the string into pieces
		ranges[i] = make_pair(i * delta, (i != (nextSlice - 1) ? (i + 1) * delta : input.size()));
	}

	for (int i = 0; i < nextSlice; i++) {                     // assign chuncks to threads
		threads.push_back(new thread(compute_chunk, ranges[i]));
	}

	for (int i = 0; i < threads.size(); ++i)
	{
		//cout << "joined thread " << threads[i]->get_id() << endl;
		threads[i]->join();
	}

	return result;
}

float parallelCompare(Mat base, Mat frameB, int nOfWorkers, function<void(Mat, Mat, bool, int, int, int, int, float&)>f){

	vector<thread*> threads;
	int rowsS = base.rows / (nOfWorkers/2);

	float precision = 0;

	for (int t = 0; t < nOfWorkers; t++) {

		//threads.push_back(move(new thread(([=](){f(base, frameB, false, rowsS * t, 0, rowsS * 2, base.cols, precision);}))));
		threads.push_back(new thread(f,base, frameB, false, rowsS * t, 0, rowsS * 2 -1, base.cols-1, ref(precision)));

	}
	for (int i = 0; i < threads.size(); ++i)
	{
		// cout<<"joined thread "<<threads[i]->get_id()<<endl;
		threads[i]->join();
	}

	return precision;
}


void openMpParallel(vector<Mat> frames, int nOfThreads) {

	auto start = chrono::high_resolution_clock::now();
	#pragma omp parallel num_threads(nOfThreads) shared(frames)
	{
		#pragma omp for
		for (int fID = 0; fID < frames.size(); fID++)
			frames.at(fID) = grayScale(frames.at(fID));
	}
	auto end = chrono::high_resolution_clock::now();
	double time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "Grayscale time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	start = chrono::high_resolution_clock::now();

	vector<vector<float>> kernelMatrix = generateKernel(5, 2, false);

	#pragma omp parallel num_threads(nOfThreads) shared(frames)
	{
		#pragma omp for
		for (int fID = 0; fID < frames.size(); fID++)
			frames.at(fID) = gaussianFilter(frames.at(fID), kernelMatrix);
	}
	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "GaussianFilter time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	start = chrono::high_resolution_clock::now();

	//cout << "0" << endl;
	Mat base = frames.at(0).clone();
	int totDifference = 0;

	for (int f = 0; f < frames.size(); f++) {
		float difference = compareFrame(base, frames.at(f), false);
		//cout << difference << endl;
		if (difference > 20) {
			base = frames.at(f).clone();
			totDifference++;
		}

	}
	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "Comparison time : " << fixed << time_taken << setprecision(9) << " sec" << endl;
	cout << "Motion detected in: " << totDifference << " frames out of " << frames.size() << endl;

}
