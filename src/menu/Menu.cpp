#include "Menu.h"
#include <iostream>

Menu::Menu() : editor("") {}

void Menu::run() {
    int choice = 0;
    while (true) {
        displayMenu();
        std::cin >> choice;
        if (choice == 12) {
            break;
        }
        processInput(choice);
    }
}

void Menu::displayMenu() {
    std::cout << "\nImage Editor Menu:\n";
    std::cout << "1. Load a new image\n";
    std::cout << "2. Load multiple images\n";
    std::cout << "3. Save current image\n";
    std::cout << "4. Apply dilation\n";
    std::cout << "5. Apply erosion\n";
    std::cout << "6. Resize image\n";
    std::cout << "7. Lighten/Darken image\n";
    std::cout << "8. Stitch images into panorama\n";
    std::cout << "9. Apply Canny edge detection\n";
    std::cout << "10. Display current image\n";
    std::cout << "11. Undo last operation\n";
    std::cout << "12. Exit\n";
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
            displayImage();
            break;
        case 11:
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
}

void Menu::lightenDarkenImage() {
}

void Menu::stitchImages() {
}

void Menu::cannyEdgeDetection() {
}

void Menu::displayImage() {
    editor.displayImage();
}

void Menu::undo() {
    editor.undo();
}
