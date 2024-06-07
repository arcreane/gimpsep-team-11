#include "../include/Menu.h"
#include <iostream>
#include <opencv2/highgui.hpp>

Menu::Menu() : editor("") {}

void Menu::run() {
    int choice = 0;
    while (true) {
        displayMenu();
        std::cin >> choice;
        if (choice == 11) {
            break;
        }
        processInput(choice);
    }
}

void Menu::displayMenu() {
    std::cout << "\n---- Image Editor Menu ----\n";
    std::cout << "  1. Load a new image\n";
    std::cout << "  2. Load multiple images\n";
    std::cout << "  3. Save current image\n";
    std::cout << "  4. Apply dilation\n";
    std::cout << "  5. Apply erosion\n";
    std::cout << "  6. Resize image\n";
    std::cout << "  7. Lighten/Darken image\n";
    std::cout << "  8. Stitch images into panorama\n";
    std::cout << "  9. Apply Canny edge detection\n";
    std::cout << "  10. Undo last operation\n";
    std::cout << "  11. Exit\n";
    std::cout << "Select an option: ";
}

void Menu::processInput(int choice) {
    switch (choice) {
        case 1:
            loadImage();
            break;
        case 2:
            loadMultipleImages();
            break;
        case 3:
            saveImage();
            break;
        case 4:
            applyDilation();
            break;
        case 5:
            applyErosion();
            break;
        case 6:
            resizeImage();
            break;
        case 7:
            lightenDarkenImage();
            break;
        case 8:
            stitchImages();
            break;
        case 9:
            cannyEdgeDetection();
            break;
        case 10:
            undo();
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

void Menu::loadImage() {
    std::cout << "Enter the path of the image to load: ";
    std::cin >> imagePath;
    editor.loadImage(imagePath);
}

void Menu::loadMultipleImages() {
    std::vector<std::string> paths;
    std::string path;
    std::cout << "Enter paths of the images to load (enter 'done' when finished):" << std::endl;
    while (true) {
        std::cin >> path;
        if (path == "done") break;
        paths.push_back(path);
    }
    for (const auto& path : paths) {
        std::cout << path << std::endl;
    }
    editor.loadMultipleImages(paths);
}

void Menu::saveImage() {
    std::string outputPath;
    std::cout << "Enter the path to save the image (with extension, e.g., output.jpg): ";
    std::cin >> outputPath;
    editor.saveImage(outputPath);
}

void Menu::applyDilation() {
    int size;
    std::cout << "Enter the dilation size: ";
    std::cin >> size;
    editor.dilateImage(size);
}

void Menu::applyErosion() {
    int size;
    std::cout << "Enter the erosion size: ";
    std::cin >> size;
    editor.erodeImage(size);
}

void Menu::resizeImage() {
    int type;
    double scale;
    int width, height;
    std::cout << "Type 1 for resize by scale. Type 2 for resize by width and height: ";
    std::cin >> type;

    if(type==1 || type==2){
        if(type==1){
            std::cout<<"Enter the scale: " ;
            std::cin >> scale; 
            editor.resizeImage(scale);
        }
        else{
            std::cout << "Enter the scale or width and height: ";
            std::cin >> width >> height;
            editor.resizeImage(width, height);
        }
    }
    else
        std::cout << "Type error enter again." << std::endl;
}

void Menu::lightenDarkenImage() {
    int value;
    std::cout << "Enter a positive value to lighten or negative to darken the image: ";
    std::cin >> value;
    editor.lightenDarkenImage(value);
}

void Menu::stitchImages() {
    std::string load;
    std::cout << "Have you loaded the images? (yes/no): ";
    std::cin >> load;

    if(load=="yes"){
        editor.listLoadedImage();
        std::cout << "Enter the image numbers to stitch(Enter -1 when done): ";
        std::vector<int> indices;
        int number;
        while(true){
            std::cin >> number;
            if(number==-1)  break;
            indices.push_back(number);
        }
        editor.stitchImages(indices);
    }
    else{
        std::cout << "Load the images first." << std::endl;
    }
}

void Menu::cannyEdgeDetection() {
    double lowerThreshold, upperThreshold;
    int kernelSize;
    std::cout << "  --- Help" << std::endl;
    std::cout << "  --- kernelSize between (3,7)" << std::endl;
    std::cout << "Enter lowerThreshold, upperThreshold and kernelSize: ";
    std::cin >> lowerThreshold >> upperThreshold >> kernelSize;
    editor.cannyEdgeDetection(lowerThreshold, upperThreshold, kernelSize);
}


void Menu::undo() {
    editor.undo();
}
