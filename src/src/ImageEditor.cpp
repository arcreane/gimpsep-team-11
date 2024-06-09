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
    if(imageManager.getCurrentImage().getImage().empty()){
        std::cout << "No image loaded." << std::endl;
        return 0;
    }
    return 1;
    // return(!imageManager.getCurrentImage().getImage().empty());
}

void ImageEditor::listLoadedImage() const{
    imageManager.listLoadedImage();
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
    if (!checkImageLoaded()) return;

    cv::Mat currentImage = imageManager.getCurrentImage().getImage();
    cv::Mat result;
    cv::resize(currentImage, result,
               cv::Size(round(scale*currentImage.cols), round(scale*currentImage.rows)), scale, scale,
               cv::INTER_LINEAR);
    imageManager.addToHistory(Image(result, ""));

    updateDisplay();
}

void ImageEditor::resizeImage(int width, int height) {
    if (!checkImageLoaded()) return;

    cv::Mat currentImage = imageManager.getCurrentImage().getImage();
    cv::Mat result;
    cv::resize(currentImage, result, cv::Size(width, height), cv::INTER_LINEAR);
    imageManager.addToHistory(Image(result, ""));

    updateDisplay();
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
    std::vector <cv::Mat>images;
    cv::Mat result;
    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;

    images=imageManager.getIndexImage(indices);

    std::cout << "Images accepted." << std::endl;
    cv::Ptr<cv::Stitcher> stitcher=cv::Stitcher::create(mode);
    cv::Stitcher::Status status = stitcher->stitch(images, result);


    if (status != cv::Stitcher::OK){
        std::cout << "Can't stitch images, error code = " << int(status) << std::endl;
    }
    else{
        imageManager.addToHistory(Image(result, ""));
        updateDisplay();
    }
}

void ImageEditor::cannyEdgeDetection(double lowerThreshold, double upperThreshold, int kernelSize) {
    if (!checkImageLoaded()) return;

    cv::Mat currentImage = imageManager.getCurrentImage().getImage();
    cv::Mat result;
    cv::Canny(currentImage, result, lowerThreshold, upperThreshold, kernelSize);

    imageManager.addToHistory(Image(result, ""));
    updateDisplay();
}

void ImageEditor::rotateImage(double angle){
    if (!checkImageLoaded()) return;
    cv::Mat currentImage = imageManager.getCurrentImage().getImage();
    cv::Mat result;

    cv::Point2f center((image.cols - 1) / 2.0, (image.rows - 1) / 2.0);
    cv::Mat rotation_matrix = getRotationMatrix2D(center, angle, 1.0);
    warpAffine(currentImage, result, rotation_matrix, currentImage.size());

    imageManager.addToHistory(Image(result, ""));
    updateDisplay();
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