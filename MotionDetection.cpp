#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>    
#include <omp.h>
#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>

//export PATH=/usr/local/gcc-11.1/bin/:$PATH
//export LD_LIBRARY_PATH=/usr/local/gcc-11.1/lib64/:$LD_LIBRARY_PATH
//g++-10 ./SPR_Project_Unipi/MotionDetection.cpp -o SPR_Project_Unipi/motionDetection `pkg-config --cflags opencv4` `pkg-config --libs opencv4` -pthread -std=c++17 -O3 -I /usr/local/fastflow/ -fopenmp

using namespace cv;
using namespace std;
using namespace ff;

vector<Mat> loadVideo(string videoPath);

Mat grayScale(Mat frames);
vector<vector<float>> generateKernel(int kernelSize, float sigma, bool verbose);
Mat gaussianFilter(Mat pic, vector<vector<float>> kernelMatrix);
float compareFrame(Mat frameA, Mat frameB, bool verbose);


void sequential(vector<Mat> frames);

void threadParalle(vector<Mat> frames, int nOfThreads);
vector<Mat> map_gray(vector<Mat> input, int nOfWorkers, function<Mat(Mat)>f);
vector<Mat> map_gaussianFilter(vector<Mat> input, int nOfWorkers, Mat(*f)(Mat, vector<vector<float>>));
float parallelCompare(Mat base, Mat frameB, int nOfWorkers, function<void(Mat, Mat, bool, int, int, int, int, float&)>f);
void compareFrame_Range(Mat frameA, Mat frameB, bool verbose, int startR, int startC, int endR, int endC, float &res);

void ffParallel(vector<Mat> frames, int nOfWorkers);

void openMpParallel(vector<Mat> frames, int nOfThreads);

tuple<vector<double>, vector<double>, vector<double>, vector<double>> statistics(double Tseq, vector<double> Tpar, vector<int> n, bool verbose);

const float PI = 3.14159265359;

int main(int argc, char** argv)
{	
	string videoPath = argv[1];
	cout<<"starting"<<endl;

	auto loadTime = chrono::high_resolution_clock::now();
	vector<Mat> seqFrames = loadVideo(videoPath);
	auto loadEnd = chrono::high_resolution_clock::now();
	double load_time_taken = (chrono::duration_cast<chrono::nanoseconds>(loadEnd - loadTime).count())* 1e-9;
	
	cout<<"## Sequential"<<endl;
	cout << "- Loading video Time: " << fixed << load_time_taken << setprecision(9) << " sec" << endl;
	auto seqTime = chrono::high_resolution_clock::now();
	sequential(seqFrames);
	auto seqTimeEnd = chrono::high_resolution_clock::now();
	double whole_time_taken = (chrono::duration_cast<chrono::nanoseconds>(seqTimeEnd - seqTime).count())*1e-9;
	cout << "Tot seq time: " << fixed << whole_time_taken+ load_time_taken << setprecision(9) << " sec" << endl;
	cout << endl;
	seqFrames.clear();

	vector<double> Tpar_threads, Tpar_FF, Tpar_OMP;
	vector<int> nParWor;

	double Tseq = whole_time_taken + load_time_taken;

	for(int th = 1; th<=32; th*=2)
	{

		nParWor.push_back(th);

		cout<<"# Number of threads "<<th<<endl;
		cout<<"-------------------------------------------------------"<<endl;
			
		cout<<"## Threads"<<endl;	

		loadTime = chrono::high_resolution_clock::now();
		vector<Mat> thFrames = loadVideo(videoPath);
		loadEnd = chrono::high_resolution_clock::now();
		load_time_taken = (chrono::duration_cast<chrono::nanoseconds>(loadEnd - loadTime).count()) * 1e-9;
		cout << "- Loading video Time: " << fixed << load_time_taken << setprecision(9) << " sec" << endl;
		
		auto threadTime = chrono::high_resolution_clock::now();
		threadParalle(thFrames, th);
		auto threadTimeEnd = chrono::high_resolution_clock::now();
		whole_time_taken = (chrono::duration_cast<chrono::nanoseconds>(threadTimeEnd - threadTime).count()) * 1e-9;
		cout << "- Tot thread time: " << fixed << whole_time_taken + load_time_taken << setprecision(9) << " sec" << endl;
		cout << endl;
		thFrames.clear();
		Tpar_threads.push_back(whole_time_taken + load_time_taken);
		
		cout<<"## Fast Flow"<<endl;
		loadTime = chrono::high_resolution_clock::now();
		vector<Mat> ffFrames = loadVideo(videoPath);
		loadEnd = chrono::high_resolution_clock::now();
		load_time_taken = (chrono::duration_cast<chrono::nanoseconds>(loadEnd - loadTime).count()) * 1e-9;
		cout << "- Loading video Time: " << fixed << load_time_taken << setprecision(9) << " sec" << endl;

		auto ffTime = chrono::high_resolution_clock::now();
		ffParallel(ffFrames,th);
		auto ffTimeEnd = chrono::high_resolution_clock::now();
		whole_time_taken = (chrono::duration_cast<chrono::nanoseconds>(ffTimeEnd - ffTime).count()) * 1e-9;
		cout << "- Tot FastFlow time: " << fixed << whole_time_taken + load_time_taken << setprecision(9) << " sec" << endl;
		cout << endl;
		ffFrames.clear();
		Tpar_FF.push_back(whole_time_taken + load_time_taken);

		cout<<"## OpenMP"<<endl;
		loadTime = chrono::high_resolution_clock::now();
		vector<Mat> ompFrames = loadVideo(videoPath);
		loadEnd = chrono::high_resolution_clock::now();
		load_time_taken = (chrono::duration_cast<chrono::nanoseconds>(loadEnd - loadTime).count()) * 1e-9;
		cout << "- Loading video Time: " << fixed << load_time_taken << setprecision(9) << " sec" << endl;

		auto ompTime = chrono::high_resolution_clock::now();
		openMpParallel(ompFrames, th);
		auto ompTimeEnd = chrono::high_resolution_clock::now();
		whole_time_taken = (chrono::duration_cast<chrono::nanoseconds>(ompTimeEnd - ompTime).count()) * 1e-9;
		cout << "- Tot OpenMp time: " << fixed << whole_time_taken + load_time_taken << setprecision(9) << " sec" << endl;
		ompFrames.clear();
		Tpar_OMP.push_back(whole_time_taken + load_time_taken);
		cout<<"----------------------------------------------------------------"<<endl<<endl;

		if (th == 1)
			th++;
	}

	cout << "Statistics for threads" << endl;
	auto t_statististcs = statistics(Tseq, Tpar_threads, nParWor,true);
	cout << "Statistics for FF" << endl;
	auto FF_statististcs = statistics(Tseq, Tpar_FF, nParWor,true);
	cout << "Statistics for OMP" << endl;
	auto OMP_statististcs = statistics(Tseq, Tpar_OMP, nParWor,true);

	return 0;
}

vector<Mat> loadVideo(string videoPath) {

	vector<Mat> videoFrames;
	VideoCapture cap(videoPath);
	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return videoFrames;
	}

	int o = 0;
	bool control = true;
	while (control) {
		Mat frame;
		cap >> frame;

		if (frame.empty())
			break;

		videoFrames.push_back(frame);

		char c = (char)waitKey(25);

		if (c == 27)
			control = false;
		cout << "pic: " << o << " out of: " << cap.get(CAP_PROP_FRAME_COUNT) << " \b" << '\r' << flush;
		o++;
	}

	return videoFrames;
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

		Mat picClone = pic.clone();
		//convolution
		for (int r = 0; r < pic.rows; r++) {
			for (int c = 0; c < pic.cols; c++) {
				if (c < pic.cols - kernelMatrix.size() && r < pic.rows - kernelMatrix.size())
				{
					float newRGB = 0;
					for (int rK = 0; rK < kernelMatrix.size(); rK++) {
						for (int cK = 0; cK < kernelMatrix.size(); cK++) {
							if((r + rK - 1)>0)
							newRGB += picClone.at<Vec3b>(r + rK - 1, c + cK - 1)[0] * kernelMatrix[rK][cK];
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
	cout << "- Grayscale time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	start = chrono::high_resolution_clock::now();

	vector<vector<float>> kernelMatrix = generateKernel(5, 2, false);
	for (int fID = 0; fID < frames.size(); fID++)
		frames.at(fID) = gaussianFilter(frames.at(fID), kernelMatrix);

	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "- GaussianFilter time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	start = chrono::high_resolution_clock::now();

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
	cout << "- Comparison time : " << fixed << time_taken << setprecision(9) << " sec" << endl;
	cout << "- Motion detected in: " << totDifference << " frames out of " << frames.size() << endl;

}


void threadParalle(vector<Mat> frames, int nOfThreads) {
	
	auto start = chrono::high_resolution_clock::now();
	map_gray(frames, nOfThreads, &grayScale);
	auto end = chrono::high_resolution_clock::now();
	double time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "- Grayscale time threads: " << fixed << time_taken << setprecision(9) << " sec" << endl;

	start = chrono::high_resolution_clock::now();
	map_gaussianFilter(frames, nOfThreads, &gaussianFilter);
	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "- Gaussian threads : " << fixed << time_taken << setprecision(9) << " sec" << endl;

	start = chrono::high_resolution_clock::now();

	Mat base = frames.at(0).clone();
	int totDifference = 0;
	
	for (int f = 0; f < frames.size(); f++) {
		float difference = compareFrame(base, frames.at(f), false);// parallelCompare(base, frames.at(f), nOfThreads, &compareFrame_Range);
		if (difference > 20) {
			base = frames.at(f).clone();
			totDifference++;
		}		
	}
	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "- Comparison time : " << fixed << time_taken << setprecision(9) << " sec" << endl;
	cout << "- Motion detected in: " << totDifference << " frames out of " << frames.size() << endl;
}

void ffParallel(vector<Mat> frames, int nOfThreads) {

	auto start = chrono::high_resolution_clock::now();

	ParallelFor pf;
	pf.parallel_for(0, frames.size(), 1, 0, [&](const long fID) {
		frames.at(fID) = grayScale(frames.at(fID));
	},nOfThreads);

	auto end = chrono::high_resolution_clock::now();
	double time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "- Grayscale time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	start = chrono::high_resolution_clock::now();

	vector<vector<float>> kernelMatrix = generateKernel(5, 2, false);
	pf.parallel_for(0, frames.size(), 1, 0, [&](const long fID) {
		frames.at(fID) = gaussianFilter(frames.at(fID), kernelMatrix);
	}, nOfThreads);		

	end = chrono::high_resolution_clock::now();
	time_taken = (chrono::duration_cast<chrono::nanoseconds>(end - start).count()) * 1e-9;
	cout << "- GaussianFilter time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	start = chrono::high_resolution_clock::now();

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
	cout << "- Comparison time : " << fixed << time_taken << setprecision(9) << " sec" << endl;
	cout << "- Motion detected in: " << totDifference << " frames out of " << frames.size() << endl;

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
			//imwrite("../sample/" + to_string(nOfWorkers)+"_"+to_string(i) + "a.jpg", result.at(i));
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
			//imwrite("../smaple/"+to_string(nOfWorkers) + "_" + to_string(i) + "a.jpg", result.at(i));
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

	for (int t = 0; t < nOfWorkers; t++) 
		threads.push_back(new thread(f,base, frameB, false, rowsS * t, 0, rowsS * 2 -1, base.cols-1, ref(precision)));
	
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
	cout << "- Grayscale time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


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
	cout << "- GaussianFilter time : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	start = chrono::high_resolution_clock::now();

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
	cout << "- Comparison time : " << fixed << time_taken << setprecision(9) << " sec" << endl;
	cout << "- Motion detected in: " << totDifference << " frames out of " << frames.size() << endl;

}


tuple<vector<double>, vector<double>, vector<double>, vector<double>> statistics(double Tseq, vector<double> Tpar, vector<int> n, bool verbose) {

	vector<double> speedup;
	vector<double> scalab;
	vector<double> efficency;
	vector<double> idealTime;

	//we assume that in the index 0 of Tpar we find the paralellization done with 1 thread

	for (int i = 1; i < n.size(); i++) {
		
		speedup.at(i) = Tseq / Tpar.at(i);
		scalab.at(i) = Tpar.at(0) / Tpar.at(i);
		efficency.at(i) = speedup.at(i) / n.at(i);
		idealTime.at(i) = Tseq / n.at(i);

		if (verbose) {
			cout << "## With " << n.at(i) << " threads:" << endl;
			cout << "- Speedup is " << speedup.at(i) << endl;
			cout << "- Scalb is " << scalab.at(i) << endl;
			cout << "- Efficency is " << efficency.at(i) << endl;
			cout << "- Ideal time is " << efficency.at(i) << endl;
			cout << endl;
		}

	}



	return make_tuple(speedup,scalab,efficency,idealTime);
}

