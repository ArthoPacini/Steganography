#include <iostream>
#include <filesystem>
#include <string>

int main()
{
    //Sets the path for input file
    fs::path inputPath = fs::current_path();
    inputPath /= "input.ppm";

    //Sets the path for the output file
    fs::path outputPath = fs::current_path();
    outputPath /= "output.ppm";
    
    //This will encode the image with the message
    encodeImage(inputPath, outputPath, "This is a hidden message inside the file! ");
    
    //This will decode the image and show on the screen
    decodeImage(outputPath);

    return 0;
}
