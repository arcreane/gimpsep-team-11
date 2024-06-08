#include "../include/ImageManager.h"
#include <iostream>

void ImageManager::addImage(const Image& image) {
    images.push_back(image);
    if (currentIndex == -1) {
        addToHistory(image);
    } else {
        history.resize(currentIndex + 1);
        addToHistory(image);
    }
}
bool ImageManager::undo() {
    if (currentIndex > 0) {
        currentIndex--;
        return true;
    }
    return false;
}

Image ImageManager::getCurrentImage() const {
    if (currentIndex >= 0 && currentIndex < history.size()) {
        return history[currentIndex];
    }
    return Image();
}
std::vector<cv::Mat> ImageManager::getIndexImage(const std::vector<int>& indeces) const{
    std::vector <cv::Mat> images;
    for (const auto& idx : indeces) {
        if (idx >= 0 && idx < history.size()){
            images.push_back(history[idx].getImage());
        }
    }
    return images;
}

void ImageManager::listLoadedImage() const{
    int idx=0;
    for (const auto& img : history) {
        std::cout << "[" << idx++ << "] " << img.getPath() << std::endl;
    }
}

void ImageManager::selectImage(int index) {
    if (index >= 0 && index < images.size()) {
        addToHistory(images[index]);
    }
}

void ImageManager::addToHistory(const Image& image) {
    if (currentIndex < history.size() - 1) {
        history.resize(currentIndex + 1);
    }
    history.push_back(image);
    currentIndex++;
}

void ImageManager::addMultipleImages(const std::vector<std::string>& paths) {
    for (const auto& path : paths) {
        addImage(Image(path));
    }
}

std::vector<Image> ImageManager::getAllImages() const {
    return images;
}


int ImageManager::getIndex() {
    return currentIndex;
}