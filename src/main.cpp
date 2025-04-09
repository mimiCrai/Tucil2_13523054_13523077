#include <chrono>
#include "QuadTree.hpp"

using namespace std;

int main()
{
    cout << endl << "📂  Input" << endl << endl;
    int originalFileSize = inputImage(QuadTree::block, QuadTree::width, QuadTree::height);
    // cout << QuadTree::width << " x " << QuadTree::height << endl;
    cout << "⚙️  Compression Settings" << endl << endl;
    inputErrorMethod(QuadTree::errorChoice);
    double targetCompression = inputCompressionTarget();
    if (targetCompression == 0){
        inputTreshold(QuadTree::threshold);
    }
    inputMinBlockSize(QuadTree::minimumBlockSize);

    cout << "💾  Export" << endl << endl;
    string exportPath = inputExportPath();
    string gifPath = inputGifPath();

    RGB* imageBlock = QuadTree::copyBlock();

    // Divide and conquer algorithm
    cout << endl << "🛠️  Compresing Image..." << endl << endl;
    auto start = chrono::high_resolution_clock::now();

    QuadTree qt;
    
    int compressedFileSize = qt.compressImage(exportPath, imageBlock, targetCompression, originalFileSize);
    double originalFileSizeInKB = (double) originalFileSize / 1000;
    double compressedFileSizeInKB = (double) compressedFileSize / 1000;
    double compressionPercentage = (double) (originalFileSize - compressedFileSize) / originalFileSize * 100;
    int depth = qt.getDepth();
    QuadTree::nodesAtDepth = vector<vector<QuadTree*>>(depth + 1);
    qt.buildNodesAtDepth();
    qt.generateGIF(imageBlock, gifPath);

    cout << "✅ Compression completed!" << endl;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << endl << "📊 Compression Summary" << endl;
    cout << "-----------------------------------------" << endl;

    cout << "⏱️   Elapsed time            : "<< elapsed.count() << " seconds" << endl;
    cout << "📷  Original image size     : " << originalFileSizeInKB << " KB" << endl;
    cout << "📉  Compressed image size   : " << compressedFileSizeInKB << " KB" << endl;
    cout << "📦  Compression percentage  : " << compressionPercentage << "%" << endl;
    cout << "🌳  Depth of quadtree       : " << depth << endl;
    cout << "🔢  Number of nodes         : " << QuadTree::numNodes << endl;
    if (targetCompression != 0){
        cout << "⚠️   Error threshold         : " << QuadTree::threshold << endl;
    }

    delete[] imageBlock;
    delete[] QuadTree::block;
    freeData();
    return 0;
}