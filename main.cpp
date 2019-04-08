#include <iostream>
#include <filesystem>
#include <string>

#include "binaryio.h" //This is the binary input / output library, for writing and reading binary files with ease
#include "encode.h" //This is the library to encode ppm files
#include "decode.h" //This is the library to decode ppm files

int main()
{
    //Sets the path for input file
    fs::path inputPath = fs::current_path();
    inputPath /= "samples";
    inputPath /= "beach.ppm";

    //Sets the path for the output file
    fs::path outputPath = fs::current_path();
    outputPath /= "output_images";
    outputPath /= "beach_output.ppm";
    
    //This will encode the image with the message
    encodeImage(inputPath, outputPath, "This is a hidden message inside the file! ");
    
    //This will decode the image and show on the screen
    decodeImage(outputPath);

    return 0;
}
