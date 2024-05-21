#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "Image.h"
#include "ImageManager.h"
#include <string>
#include <vector>

class ImageEditor {
public:
    ImageEditor(const std::string& imagePath = "");

    void loadImage(const std::string& imagePath);
    void loadMultipleImages(const std::vector<std::string>& imagePaths);
    bool saveImage(const std::string& outputPath);
    void displayImage() const;
    void dilateImage(int size);
    void erodeImage(int size);
    void resizeImage(double scale);
    void resizeImage(int width, int height);
    void lightenDarken(double factor);
    void stitchImages(const std::vector<int>& indices);
    void cannyEdgeDetection(double lowerThreshold, double upperThreshold, int kernelSize);
    void undo();
    void selectImage(int index);
    std::vector<Image> getAllImages() const;

private:
    bool checkImageLoaded() const;
    ImageManager imageManager;
};

#endif // IMAGEEDITOR_H
