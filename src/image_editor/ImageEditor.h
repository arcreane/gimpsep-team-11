#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

class ImageEditor {
private:
    cv::Mat image;

public:
    ImageEditor() {}
    ImageEditor(const std::string& imagePath);

    void loadImage(const std::string& imagePath);

    void dilateImage(int size);
    void erodeImage(int size);
    void resizeImage(double scale);
    void resizeImage(int width, int height);
    void lightenDarken(double factor);
    void stitchImages(const std::vector<std::string>& filenames);
    void cannyEdgeDetection(double lowerThreshold, double upperThreshold, int kernelSize);

    bool saveImage(const std::string& outputPath);

    cv::Mat getImage() const;
    virtual ~ImageEditor(){}
};

#endif IMAGEEDITOR_H
