#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "Image.h"
#include <vector>
#include <string>

class ImageManager {
public:
    void addImage(const Image& image);
    bool undo();
    Image getCurrentImage() const;
    void selectImage(int index);
    void addToHistory(const Image& image);
    void addMultipleImages(const std::vector<std::string>& paths);
    std::vector<Image> getAllImages() const;

private:
    std::vector<Image> history;
    int currentIndex = -1;
    std::vector<Image> images;
};

#endif // IMAGEMANAGER_H
