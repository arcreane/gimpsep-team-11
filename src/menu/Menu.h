#ifndef MENU_H
#define MENU_H

#include "../image_editor/ImageEditor.h"
#include <string>

class Menu {
public:
    Menu();
    void run();

private:
    void displayMenu();
    void processInput(int choice);
    void loadImage();
    void loadMultipleImages();
    void saveImage();
    void applyDilation();
    void applyErosion();
    void resizeImage();
    void lightenDarkenImage();
    void stitchImages();
    void cannyEdgeDetection();
    void displayImage();
    void undo();

    ImageEditor editor;
    std::string imagePath;
};

#endif // MENU_H
