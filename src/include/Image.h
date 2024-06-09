#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/core.hpp>
#include <string>

class Image {
public:

    Image();
    Image(const std::string& path);
    Image(const cv::Mat& image, const std::string& path = "");

    cv::Mat getImage() const;
    std::string getPath() const;
    void setImage(const cv::Mat& newImage);

private:
    cv::Mat image;
    std::string path;
};

#endif // IMAGE_H
