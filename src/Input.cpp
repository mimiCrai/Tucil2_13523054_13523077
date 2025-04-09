
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Input.hpp"
#include "include/stb_image.h"
#include "include/stb_image_write.h"

using namespace std;

// initialize global variables
unsigned char *imageData = nullptr;
int imageChannels;
std::string fileType;

int inputImage(RGB* &block, int &width, int &height){
    string inputPath;
    cout << "Masukkan alamat gambar yang akan dikompresi: ";
    getline(cin, inputPath);
    fileType = getFileType(inputPath);
    if (fileType == "PNG"){
        imageData = stbi_load(inputPath.c_str(), &width, &height, &imageChannels, 4);
    }
    else if (fileType == "JPG"){
        imageData = stbi_load(inputPath.c_str(), &width, &height, &imageChannels, 3);
    }
    else if (fileType == "JPEG"){
        imageData = stbi_load(inputPath.c_str(), &width, &height, &imageChannels, 3);
    }
    if (imageData == nullptr){
        cout << "Gambar tidak ditemukan!" << endl;
        exit(0);
    }
    else if (fileType == "UNKNOWN"){
        cout << "Format gambar tidak didukung!" << endl;
        exit(0);
    }

    cout << "✅ Gambar berhasil dimuat!" << endl << endl;
    imageToBlock(block, width, height);

    return getFileSize(inputPath);
}

int exportImage(string outputPath, RGB* block, int width, int height){
    blockToImage(block, width, height);
    if (fileType == "PNG"){
        stbi_write_png(outputPath.c_str(), width, height, 4, imageData, width * 4);
    }
    else if (fileType == "JPG"){
        stbi_write_jpg(outputPath.c_str(), width, height, 3, imageData, 70);
    }
    else if (fileType == "JPEG"){
        stbi_write_jpg(outputPath.c_str(), width, height, 3, imageData, 70);
    }
    return getFileSize(outputPath);
}

void imageToBlock(RGB* &block, int width, int height){
    block = new RGB[width * height];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (fileType == "PNG"){
                int index = (i * width + j) * 4;
                unsigned char r = imageData[index + 0]; 
                unsigned char g = imageData[index + 1];  
                unsigned char b = imageData[index + 2];  
                unsigned char a = imageData[index + 3]; 
                block[i * width + j] = RGB(r, g, b, a);
            }
            else{
                int index = (i * width + j) * 3;
                unsigned char r = imageData[index + 0];
                unsigned char g = imageData[index + 1];
                unsigned char b = imageData[index + 2];
                block[i * width + j] = RGB(r, g, b);
            }
        }
    }
    cout << block << endl;
}


void blockToImage(RGB* &block, int width, int height){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            RGB color = block[i * width + j];
            int index;
            if (fileType == "PNG"){
                index = (i * width + j) * 4;
            }
            else{
                index = (i * width + j) * 3;
            }
            imageData[index + 0] = color.red;
            imageData[index + 1] = color.green;
            imageData[index + 2] = color.blue;
            // use the default alpha value
        }
    }
}


void inputErrorMethod(int &errorChoice){
    cout << "Pilih metode error: " << endl;
    cout << "  1. Variance" << endl;
    cout << "  2. Mean Absolute Deviation (MAD)" << endl;
    cout << "  3. Max Pixel Difference" << endl;
    cout << "  4. Entropy" << endl;
    cout << "  5. Structural Similarity Index (SSIM)" << endl;
    cout << "Masukkan pilihan [1-5]: ";
    string input;
    getline(cin, input);
    stringstream ss(input);
    int choice;
    ss >> choice;
    if (ss.fail() || !ss.eof()){
        cout << "Pilihan tidak valid!" << endl;
        exit(0);
    }
    if (choice >= 1 && choice <= 5){
        errorChoice = choice;
    }
    else{
        cout << "Pilihan tidak valid!" << endl ;
        exit(0);
    }
    cout << endl;
}

double inputCompressionTarget(){
    cout << "Masukkan target kompresi [0.0-1.0]: ";
    string input;
    getline(cin, input);
    stringstream ss(input);
    double target;
    ss >> target;
    if (ss.fail() || !ss.eof()){
        cout << "Target kompresi tidak valid!" << endl;
        exit(0);
    }
    if (target < 0 || target > 1){
        cout << "Target kompresi tidak valid!" << endl;
        exit(0);
    }
    return target;
}

void inputTreshold(double &threshold){
    cout << "Masukkan ambang batas error: ";
    string input;
    getline(cin, input);
    stringstream ss(input);
    ss >> threshold;
    if (ss.fail() || !ss.eof()){
        cout << "Ambang batas tidak valid!" << endl;
        exit(0);
    }
    if (threshold < 0){
        cout << "Ambang batas tidak valid!" << endl;
        exit(0);
    }
}

void inputMinBlockSize(int &minimumBlockSize){
    cout << "Masukkan ukuran blok minimum: ";
    string input;
    getline(cin, input);
    stringstream ss(input);
    ss >> minimumBlockSize;
    if (ss.fail() || !ss.eof()){
        cout << "Ukuran blok minimum tidak valid!" << endl;
        exit(0);
    }
    if (minimumBlockSize < 1){
        cout << "Ukuran blok minimum tidak valid!" << endl;
        exit(0);
    }
    cout << endl;
}

string inputExportPath(){
    string outputPath;
    cout << "Masukkan alamat gambar yang akan diekspor: ";
    getline(cin, outputPath);
    if (getFileType(outputPath) != fileType){
        cout << "Format gambar tidak sesuai dengan input!" << endl;
        exit(0);
    }
    return outputPath;
}

string inputGifPath(){
    string gifPath;
    cout << "Masukkan alamat GIF yang akan diekspor: ";
    getline(cin, gifPath);
    if (getFileType(gifPath) != "GIF"){
        cout << "Format tidak sesuai!" << endl;
        exit(0);
    }
    return gifPath;
}

int getFileSize(string filename){
    FILE *file = fopen(filename.c_str(), "rb");
    if (file == nullptr){
        cout << "File tidak ditemukan!" << endl;
        return -1;
    }
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);
    return size;
}

string getFileType(string filename){
    string type;
    if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".png"){
        type = "PNG";
    }
    else if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".jpg"){
        type = "JPG";
    }
    else if (filename.size() >= 5 && filename.substr(filename.size() - 5) == ".jpeg"){
        type = "JPEG";
    }
    else if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".gif"){
        type = "GIF";
    }
    else{
        type = "UNKNOWN";
    }
    return type;
}

void freeData(){
    stbi_image_free(imageData);
}

#endif
#endif