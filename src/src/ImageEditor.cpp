#include "../include/ImageEditor.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>
#include <iostream>
#include <fstream>

ImageEditor::ImageEditor(const std::string& imagePath) {
    if (!imagePath.empty()) {
        loadImage(imagePath);
    }
}

void ImageEditor::loadImage(const std::string& imagePath) {
    std::ifstream file(imagePath);
    if (!file) {
        std::cerr << "Error: File does not exist - " << imagePath << std::endl;
        return;
    }

    Image image(imagePath);
    if (image.getImage().empty()) {
        std::cerr << "Error: Unable to load image from " << imagePath << std::endl;
    } else {
        imageManager.addImage(image);
        std::cout << "Image loaded successfully from " << imagePath << std::endl;
        updateDisplay();
    }
}

void ImageEditor::loadMultipleImages(const std::vector<std::string>& imagePaths) {
    imageManager.addMultipleImages(imagePaths);
    std::cout << "Images loaded successfully." << std::endl;
}

bool ImageEditor::saveImage(const std::string& outputPath) {
    if (!checkImageLoaded()) return false;

    std::string savePath = outputPath;

  /*  if (!hasValidExtension(outputPath)) {
        std::cerr << "Invalid file extension. Try again" << std::endl;
        return false;
    }
    */

    if (cv::imwrite(savePath, imageManager.getCurrentImage().getImage())) {
        std::cout << "Image saved to " << savePath << std::endl;
        return true;
    } else {
        std::cerr << "Error: Unable to save image to " << savePath << std::endl;
        return false;
    }
}

/*bool ImageEditor::hasValidExtension(const std::string& filename) {
    std::vector<std::string> validExtensions = {".jpg", ".jpeg", ".png", ".bmp", ".tiff"};
    for (const auto& ext : validExtensions) {
        if (filename.size() >= ext.size() &&
            filename.compare(filename.size() - ext.size(), ext.size(), ext) == 0) {
            return true;
        }
    }
    return false;
}
 */

bool ImageEditor::checkImageLoaded() const {
    return !imageManager.getCurrentImage().getImage().empty();
}

void ImageEditor::dilateImage(int size) {
    if (!checkImageLoaded()) return;

    cv::Mat currentImage = imageManager.getCurrentImage().getImage();
    cv::Mat result;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(size, size));
    cv::dilate(currentImage, result, element);
    imageManager.addToHistory(Image(result, ""));

    updateDisplay();
}

void ImageEditor::erodeImage(int size) {
    if (!checkImageLoaded()) return;

    cv::Mat currentImage = imageManager.getCurrentImage().getImage();
    cv::Mat result;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(size, size));
    cv::erode(currentImage, result, element);
    imageManager.addToHistory(Image(result, ""));

    updateDisplay();
}

void ImageEditor::resizeImage(double scale) {
}

void ImageEditor::resizeImage(int width, int height) {
}

void ImageEditor::lightenDarkenImage(int value) {
    if (!checkImageLoaded()) return;

    cv::Mat currentImage = imageManager.getCurrentImage().getImage();
    cv::Mat result;

    double alpha = 1.0;
    double beta = value;
    cv::addWeighted(currentImage, alpha, currentImage, 0, beta, result);

    imageManager.addToHistory(Image(result, ""));
    updateDisplay();
}



void ImageEditor::stitchImages(const std::vector<int>& indices) {
}

void ImageEditor::cannyEdgeDetection(double lowerThreshold, double upperThreshold, int kernelSize) {
}

void ImageEditor::displayImage() const {
    if (!checkImageLoaded()) return;

    cv::destroyAllWindows();
    cv::imshow("Image", imageManager.getCurrentImage().getImage());
    std::cout << "Press any key to close the image window..." << std::endl;
    cv::waitKey(1);
    cv::destroyWindow("Image");
}


void ImageEditor::undo() {
    if (imageManager.undo()) {
        std::cout << "Undo successful." << std::endl;
        updateDisplay();  // Display the image after undoing
    } else {
        std::cout << "No more steps to undo." << std::endl;
    }
}

void ImageEditor::selectImage(int index) {
    imageManager.selectImage(index);
}

std::vector<Image> ImageEditor::getAllImages() const {
    return imageManager.getAllImages();
}

void ImageEditor::updateDisplay() const {
    if (!checkImageLoaded()) {
        std::cout << "No image loaded to display." << std::endl;
        return;
    }

    cv::destroyAllWindows();  // Close any open windows
    cv::imshow("Image", imageManager.getCurrentImage().getImage());
    std::cout << "Press any key to close the image window..." << std::endl;
    cv::waitKey(0);
    cv::destroyWindow("Image");
}