#ifndef MENU_H
#define MENU_H

#include "../image_editor/ImageEditor.h"
#include <string>
#include <iostream>

class Menu {
private:
    ImageEditor editor;
    std::string imagePath;

    void displayMenu();
    void processInput(int choice);
    void loadImage();
    void saveImage();
    void applyDilation();
    void applyErosion();
    void resizeImage();
    void lightenDarkenImage();
    void stitchImages();
    void cannyEdgeDetection();
public:
    Menu();
    void run();
};
#endif //MENU_H