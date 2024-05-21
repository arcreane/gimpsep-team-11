#include "../include/Image.h"
#include <opencv2/imgcodecs.hpp>

// Default constructor
Image::Image() : path("") {}

Image::Image(const std::string& path) : path(path) {
    image = cv::imread(path);
}

Image::Image(const cv::Mat& image, const std::string& path) : image(image), path(path) {}

cv::Mat Image::getImage() const {
    return image;
}

std::string Image::getPath() const {
    return path;
}

void Image::setImage(const cv::Mat& newImage) {
    image = newImage;
}
