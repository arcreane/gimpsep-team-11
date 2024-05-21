#include "ImageManager.h"

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
