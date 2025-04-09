#ifndef INPUT_HPP
#define INPUT_HPP

#include "RGB.hpp"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

extern unsigned char *imageData;
extern int imageChannels;

/*
    .png = PNG
    .jpg = JPG
    .jpeg = JPEG
    .gif = GIF
*/
extern string fileType; 

int inputImage(RGB* &block, int &width, int &height);

void imageToBlock(RGB* &block, int width, int height);

void blockToImage(RGB* &block, int width, int height);

void inputErrorMethod(int &errorChoice);

double inputCompressionTarget();

void inputTreshold(double &threshold);

void inputMinBlockSize(int &minimumBlockSize);

string inputExportPath();

string inputGifPath();

int exportImage(string outputPath, RGB* block, int width, int height);

int getFileSize(string filename);

string getFileType(string filename);

void freeData();

#endif