#include "ImageEditor.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>

ImageEditor::ImageEditor(const std::string& imagePath) {
    loadImage(imagePath);
}


void ImageEditor::loadImage(const std::string& imagePath) {
    std::ifstream file(imagePath);
    if (!file) {
        std::cerr << "Error: File does not exist - " << imagePath << std::endl;
        return;
    }

    image = cv::imread(imagePath);
    if (image.empty()) {
        std::cerr << "Error: Unable to load image from " << imagePath << std::endl;
    } else {
        std::cout << "Image loaded successfully from " << imagePath << std::endl;
    }
}

bool ImageEditor::saveImage(const std::string& outputPath) {
    if (image.empty()) {
        std::cerr << "Error: No image to save." << std::endl;
        return false;
    }

    std::string savePath = outputPath;

    if (!hasValidExtension(outputPath)) {
        std::cerr << "Invalid file extension. Try again" << std::endl;
        return false;
    }

    if (cv::imwrite(savePath, image)) {
        std::cout << "Image saved to " << savePath << std::endl;
        return true;
    } else {
        std::cerr << "Error: Unable to save image to " << savePath << std::endl;
        return false;
    }
}


bool ImageEditor::hasValidExtension(const std::string& filename) {
    std::vector<std::string> validExtensions = {".jpg", ".jpeg", ".png", ".bmp", ".tiff"};
    for (const auto& ext : validExtensions) {
        if (filename.size() >= ext.size() &&
            filename.compare(filename.size() - ext.size(), ext.size(), ext) == 0) {
            return true;
        }
    }
    return false;
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


cv::Mat ImageEditor::getImage() const {
    return image;
}
