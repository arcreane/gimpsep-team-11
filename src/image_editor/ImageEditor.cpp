#include "ImageEditor.h"

ImageEditor::ImageEditor(const std::string& imagePath) {
    loadImage(imagePath);
}


void ImageEditor::loadImage(const std::string& imagePath) {
}

void ImageEditor::dilateImage(int size) {
}

void ImageEditor::erodeImage(int size) {
}

void ImageEditor::resizeImage(double scale) {
}

void ImageEditor::resizeImage(int width, int height) {
}

void ImageEditor::lightenDarken(double factor) {
}

void ImageEditor::stitchImages(const std::vector<std::string>& filenames) {
}

void ImageEditor::cannyEdgeDetection(double lowerThreshold, double upperThreshold, int kernelSize) {
}

bool ImageEditor::saveImage(const std::string& outputPath) {
    return true;
}

cv::Mat ImageEditor::getImage() const {
    return image;
}
