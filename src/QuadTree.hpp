#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "Input.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

class QuadTree
{
private:
    int startHeight, startWidth, currentHeight, currentWidth, error;
    bool isSmallest;
    QuadTree* topLeftChild;
    QuadTree* topRightChild;
    QuadTree* bottomLeftChild;
    QuadTree* bottomRightChild;

public:
    static int height, width, numNodes;
    static RGB* block;
    static int errorChoice, minimumBlockSize;
    static double threshold; 
    static std::vector<std::vector<QuadTree*>> nodesAtDepth;

    QuadTree();
    QuadTree(int currentH, int currentW, int startH, int startW);
    ~QuadTree();

    /*
        Setting value of the static variable block at height h, width w
    */
    static void setValue(int h, int w, RGB value);

    /*
        Setting value of Block at height h, width w
    */
    void setValue(int h, int w, RGB value, RGB* Block, unsigned char* ImageData, bool gif);

    /*
        Getting value of the static variable block at height h, width w
    */
    static RGB getValue(int h, int w);

    /*
        Getting value of Block at height h, width w
    */
    RGB getValue(int h, int w, RGB* Block);

    RGB getMean();
    RGB getMean(RGB* Block);
    RGB getMin();
    RGB getMin(RGB* Block);
    RGB getMax();
    RGB getMax(RGB* Block);

    double variance();
    double meanAbsoluteDeviation();
    double maxPixelDifference();
    double entropy();
    double structuralSimilarityIndex(); // BONUS
    double getError();

    void divConq();
    double divConq(double currentThreshold, RGB* referenceBlock);
    int compressImage(string exportPath, RGB* image, double targetCompression, int originalFileSize);

    void colorNormalization();
    void colorNormalization(RGB* referenceBlock, RGB* Block, unsigned char* ImageData, bool gif = false);

    int getDepth();

    void buildNodesAtDepth(int depth = 0);

    void generateGIF(RGB* image, std::string outputPath);

    static RGB* copyBlock();

    static void copyBlock(RGB* &Block);

    // Belum bikin function untuk ngeset value array block biar otomatis. Untuk sementara harus manual pake set value.
};

#endif