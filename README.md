# PARALLEL AND DISTRIBUTED SYSTEMS: PARADIGMS AND MODELS 2021/2022

## Introduction
This repository contains the solution to the motion detection project proposed in the SPM exam for the master's degree in artificial intelligence from the University of Pisa.
To have a more in depth view of this problem and the solution, read the report which contains results and explanation for each implementation choice.
<a href = "./SPM_Project_Report_FasanoPaolo.pdf">SPM_Project_REport.pdf</a> 

<br>

## Build instructions
To recompile and re-run the code there are two ways:
### First method
- install FastFlow adding it to your c++ compiler include folder (following
the instructions present on the FastFlow github: https://github.com/fastflow/fastflow);
- install opencv either using the guide given from opencv at https://github.com/opencv/opencv
or using vcpkg (https://github.com/microsoft/vcpkg);
- run the CMakeLists inside the project folder, using cMake (https://cmake.org/),
which automatically finds opencv and builds the project;
- after building the project an IDE, like Visual Studio or QtCreator, can be
used to run it;
### The second option
- download and build FastFlow and OpenCv;
- run the MotionDetection.cpp in the C++ compiler including the location
of fast flow and configuring the opencv lib. The compiler line should be
something like:
g++-10 ./SPR_Project_Unipi/MotionDetection.cpp -o SPR_Project_Unipi/motionDetection
‘pkg-config --cflags opencv4‘ ‘pkg-config --libs opencv4‘ -pthread -std=c++17
-O3 -I /usr/local/fastflow/ -fopenmp
- run the result of the compilation. The command should be:
./MotionSetection <Path to a video file>


---

## Contact information

If you have any problems to install this repository or need any clarification on the code please contact us at: 

|Author             |University Mail                    | Personal Mail             | Github                                                   |
|-------------------|-----------------------------------|---------------------------|----------------------------------------------------------|
| Paolo Fasano      | p.fasano1@studenti.unipi.it       | p.fasano99@hotmail.com    | <a href="https://github.com/PFasano99/">Paolo Fasano</a> |
