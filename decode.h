#ifndef DECODE_H_
#define DECODE_H_

#include "binaryio.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>

void decodeImage(fs::path & inputPath)
{
    //Reads file to buffer
    std::vector<std::bitset<sizeof(unsigned char)*8>> bytesOfData;
    bytesOfData = readBinaryToBitSet(inputPath);

    //Creates buffer to store message
    std::vector<std::bitset<sizeof(unsigned char)*8>> messageBuffer;

    //The size of the buffer is going to be the size of the file divided by 4, because we need to read 4 bytes to create 1 byte.
    //So for example a file containing 512 bytes can store 128 bytes of encoded message.  512/4 = 128;
    messageBuffer.reserve(bytesOfData.size()/4);

    //Creates a buffer to store 1 byte (1 char)
    std::bitset<sizeof(unsigned char)*8> charBuffer;
    
    //We need to iterate over 4 bytes of input file to build 1 byte (one char) of the encoded message
    unsigned iteracaoString = 0;
    unsigned shiftOfByte = 0;
    for(auto & b : bytesOfData)
    {
        //Set the char buffer (first bit + shiftOfByte) bit to the first bit of the iterate byte of the input file
        if(b.test(0))
            charBuffer.set(shiftOfByte);
        else
            charBuffer.reset(shiftOfByte);
        
        //Set the char buffer (second bit + shiftOfByte) bit to the second bit of the iterate byte of the input file
        if(b.test(1))
            charBuffer.set(shiftOfByte+1);
        else
            charBuffer.reset(shiftOfByte+1);

        shiftOfByte+=2;
        if(shiftOfByte == 8)
        {
            shiftOfByte = 0;
            messageBuffer.emplace_back(charBuffer);
        }
    }
   
    //Converts the vector of bitsets to a vector of unsigned chars, and then output the message to screen
    std::vector<unsigned char> message = vectorConvert_bitSetToUnsignedChar(messageBuffer);
    std::cout << "Mensagem: ";
    for(auto & c : message)
        std::cout << c;
    std::cout << std::endl;

    return;
}

#endif 
