#ifndef ENCODE_H_
#define ENCODE_H_

#include "binaryio.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>


//This performs the actual encoding
void encodeImage(fs::path & inputPath, fs::path & outputPath, std::string encodeMessage)
{
    //Create and read files to buffer
    std::vector<std::bitset<sizeof(unsigned char)*8>> bytesOfData;
    bytesOfData = readBinaryToBitSet(inputPath);
    
    //Creates and reserve 15 bytes to store the header of the file
    std::vector<std::bitset<sizeof(unsigned char)*8>> headerData;
    headerData.reserve(HEADER_SIZE_IN_BYTES);

    //Reads the first 15 bytes of the header into the 'headerData' buffer
    for(unsigned i = 0; i < HEADER_SIZE_IN_BYTES; i++)
    {
        headerData.emplace_back(bytesOfData[i]);
    }

    
    //This iterates over every byte in the 'bytesOfData' buffer. For every 4 bytes, we can encode 1 byte of the message.
    unsigned iterationString = 0;
    unsigned shiftOfByte = 0;
    for(auto & b : bytesOfData)
    {
        //Stores the byte of the encode message into a bitset
        std::bitset<sizeof(unsigned char)*8> c(encodeMessage[iterationString]);

        //Sets the first bit of the iterate bytesOfData to match the (first bit + shiftOfByte) bit of the message character
        if(c.test(shiftOfByte))
            b.set(0);
        else
            b.reset(0);

        //Sets the second bit of the iterate bytesOfData to match the (second bit + shiftOfByte) bit of the message character
        if(c.test(shiftOfByte+1))
            b.set(1);
        else
            b.reset(1);

        //This performs a loop, this number is going to be
        /*
            Times looping | shiftOfByte value
                0                   0
                1                   2
                2                   4
                3                   6
                4                   8
                5                   0
                6                   2
                7                   4
                8                   6
                9                   8
                10                  0
                and so on...
        */
        shiftOfByte+=2;
        if(shiftOfByte == 8)
        {
            shiftOfByte = 0;
            iterationString = (iterationString + 1)%encodeMessage.size();
        }
    }
    //Writes the header data...
    writeBinary(outputPath, headerData);

    //Writes the encoded message, but first it need to get rid of the first 15 bytes, because they are the header data
    //So creates a new vector, now without the 15 bytes headerData
    std::vector<std::bitset<sizeof(unsigned char)*8>> bytesOfDataWithoutHeader;
    //Reserve the size of bytesOfData - 15 bytes of header data
    bytesOfDataWithoutHeader.reserve(bytesOfData.size()-headerData.size());
    //Copy the files ***THIS NEEDS TO BE CHANGE, probrably really bad approach***
    std::copy(bytesOfData.begin()+HEADER_SIZE_IN_BYTES, bytesOfData.end(), back_inserter(bytesOfDataWithoutHeader));

    //Writes the rest of the file
    writeBinary(outputPath, bytesOfDataWithoutHeader);
    return;
}

#endif
