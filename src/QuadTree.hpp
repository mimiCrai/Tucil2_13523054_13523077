#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "Input.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

class QuadTree
{
private:
    double error;
    QuadTree* topLeftChild;
    QuadTree* topRightChild;
    QuadTree* bottomLeftChild;
    QuadTree* bottomRightChild;
    int startHeight, startWidth, currentHeight, currentWidth;
    bool isSmallest;

public:
    static double threshold; 
    static RGB* block;
    static int height, width, numNodes;
    static int errorChoice, minimumBlockSize;
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

    RGB getMean(RGB* Block);
    RGB getMin(RGB* Block);
    RGB getMax(RGB* Block);

    double variance(RGB* Block);
    double meanAbsoluteDeviation(RGB* Block);
    double maxPixelDifference(RGB* Block);
    double entropy(RGB* Block);
    double structuralSimilarityIndex(RGB* Block); // BONUS
    double getError(RGB* Block);

    void divConq();
    void divConq(double currentThreshold, RGB* referenceBlock);
    int compressImage(string exportPath, RGB* image, double targetCompression, int originalFileSize);

    void colorNormalization();
    void colorNormalization(RGB* referenceBlock, RGB* Block, unsigned char* ImageData, bool gif = false);

    int getDepth();

    void buildNodesAtDepth(int depth = 0);

    void generateGIF(RGB* image, std::string outputPath);

    static RGB* copyBlock();

    static void copyBlock(RGB* &Block);
};

#endif