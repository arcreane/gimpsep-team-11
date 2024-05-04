#include "Menu.h"

Menu::Menu() {
}

void Menu::run() {
    int choice = 0;
    while (true) {
        if (editor.getImage().empty()) {
            std::cout << "No image loaded. Please load an image first." << std::endl;
            loadImage();
        } else {
            displayMenu();
            std::cin >> choice;
            if (choice == 9) {
                break
            }
            processInput(choice);
        }
    }
}

void Menu::displayMenu() {
    std::cout << "\nImage Editor Menu:\n";
    std::cout << "1. Load a new image\n";
    std::cout << "2. Save current image\n";
    std::cout << "3. Apply dilation\n";
    std::cout << "4. Apply erosion\n";
    std::cout << "5. Resize image\n";
    std::cout << "6. Lighten/Darken image\n";
    std::cout << "7. Stitch images into panorama\n";
    std::cout << "8. Apply Canny edge detection\n";
    std::cout << "9. Exit\n";
    std::cout << "Select an option: ";
}

void Menu::processInput(int choice) {
    switch (choice) {
        case 1:
            loadImage();
            break;
        case 2:
            saveImage();
            break;
        case 3:
            applyDilation();
            break;
        case 4:
            applyErosion();
            break;
        case 5:
            resizeImage();
            break;
        case 6:
            lightenDarkenImage();
            break;
        case 7:
            stitchImages();
            break;
        case 8:
            cannyEdgeDetection();
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

void Menu::loadImage() {
    std::cout << "Enter image path: ";
    std::cin >> imagePath;
   // editor.loadImage(imagePath);
}

void Menu::saveImage() {
    std::string outputPath;
    std::cout << "Enter output file path: ";
    std::cin >> outputPath;
    // save image
}

void Menu::applyDilation() {
    // Implementation for dilation
    int size;
    std::cout << "Enter dilation size: ";
    std::cin >> size;
   // editor.dilateImage(size);
    std::cout << "Dilation applied.\n";
}

void Menu::applyErosion() {
    int size;
    std::cout << "Enter erosion size: ";
    std::cin >> size;
    //editor.erodeImage(size);
    std::cout << "Erosion applied.\n";
}

void Menu::resizeImage(){
    int size;
    std::cout << "Enter new size: ";
    std::cin >> size;
    //
    std::cout << "image resized .\n";

}

void Menu::lightenDarkenImage(){}
void Menu::stitchImages(){}
void Menu::cannyEdgeDetection(){}