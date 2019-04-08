#ifndef BINARY_IO_H_
#define BINARY_IO_H_

#include <filesystem>
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>

//If you are compiling with gnu g++, the namespace to access filesystem library is just fs::filesystem, otherwise, if you are on windows
//where gnu g++ minGW don't fully support filesystem, you need to use Visual Studio Visual C++ Compiler,
//and for accessing the filesystem library within VC++, you need to use fs::experimental::filesystem
#ifdef _WIN32
namespace fs = std::experimental::filesystem;
#else
namespace fs = std::filesystem;
#endif

//This define the size of the .ppm header file, so it skips the head and don't screw things up
#define HEADER_SIZE_IN_BYTES 15

//This writes a vector of unsigned char to a file
void writeBinary(fs::path & outputPath, std::vector<unsigned char> & dataBuffer)
{
    std::ofstream outputFile(fs::absolute(outputPath).string().c_str(), std::ios::binary | std::ios::app);

    //writes dataBuffer to file
    for(auto & data : dataBuffer)
    {
        outputFile.write((const char*)&data, sizeof(data));
    }

    outputFile.close();
}

//This writes a vector of bitsets to a file
void writeBinary(fs::path & outputPath, std::vector<std::bitset<sizeof(unsigned char)*8>> & dataBuffer)
{
    std::ofstream outputFile(fs::absolute(outputPath).string().c_str(), std::ios::binary | std::ios::app);

    //Escrever o dataBuffer no arquivo
    for(auto & data : dataBuffer)
    {
        char i = static_cast<char>(data.to_ulong());
        outputFile.write((const char*)&i, sizeof(i));
    }

    outputFile.close();
}

//This reads a binary file and return the data on a vector of bitsets
std::vector<std::bitset<sizeof(unsigned char)*8>> readBinaryToBitSet(fs::path & inputPath)
{
    std::vector<std::bitset<sizeof(unsigned char)*8>> dataBuffer;

    if(!fs::exists(inputPath))
    {
        std::cerr << "[ERROR]: File does not exists\n";
        return dataBuffer;
    }
        
    std::ifstream inputFile(fs::absolute(inputPath).string().c_str(), std::ios::binary);
    std::size_t fileSizeInBytes = fs::file_size(inputPath);

    dataBuffer.clear();
    dataBuffer.reserve(fileSizeInBytes);

    while(fileSizeInBytes--)
    {
        char charRead;
        inputFile.read(reinterpret_cast<char*>(&charRead), sizeof(charRead));
        dataBuffer.push_back(std::bitset<sizeof(unsigned char)*8>(charRead));
    }

    inputFile.close();
    return dataBuffer;
}

//This reads a binary file and set the dataBuffer argument to the actual data
void readBinary(fs::path & inputPath, std::vector<std::bitset<sizeof(unsigned char)*8>> & dataBuffer)
{
    if(!fs::exists(inputPath))
        return;

    std::ifstream inputFile(fs::absolute(inputPath).string().c_str(), std::ios::binary);
    std::size_t fileSizeInBytes = fs::file_size(inputPath);

    dataBuffer.clear();
    dataBuffer.reserve(fileSizeInBytes);

    while(fileSizeInBytes--)
    {
        char charRead;
        inputFile.read(reinterpret_cast<char*>(&charRead), sizeof(charRead));
        dataBuffer.push_back(std::bitset<sizeof(unsigned char)*8>(charRead));
    }

    inputFile.close();
}

//This reads a binary file and returns the data on a vector of unsigned char
std::vector<unsigned char> readBinaryToUnsignedChar(fs::path & inputPath)
{
    std::vector<unsigned char> dataBuffer;

    if(!fs::exists(inputPath))
        return dataBuffer;

    std::ifstream inputFile(fs::absolute(inputPath).string().c_str(), std::ios::binary);
    std::size_t fileSizeInBytes = fs::file_size(inputPath);

    dataBuffer.clear();
    dataBuffer.reserve(fileSizeInBytes);

    while(fileSizeInBytes--)
    {
        char charRead;
        inputFile.read(reinterpret_cast<char*>(&charRead), sizeof(charRead));
        dataBuffer.push_back(charRead);
    }

    inputFile.close();
    return dataBuffer;
}

//This reads a binary file and set the dataBuffer argument to the actual data
void readBinary(fs::path & inputPath, std::vector<unsigned char> & dataBuffer)
{
    if(!fs::exists(inputPath))
        return;

    std::ifstream inputFile(fs::absolute(inputPath).string().c_str(), std::ios::binary);
    std::size_t fileSizeInBytes = fs::file_size(inputPath);

    dataBuffer.clear();
    dataBuffer.reserve(fileSizeInBytes);

    while(fileSizeInBytes--)
    {
        char charRead;
        inputFile.read(reinterpret_cast<char*>(&charRead), sizeof(charRead));
        dataBuffer.push_back(charRead);

    }

    inputFile.close();
}

//This converts a vector of bitset to a vector of unsigned char
void vectorConvert_bitSetToUnsignedChar(std::vector<std::bitset<sizeof(unsigned char)*8>> & bytesOfData, std::vector<unsigned char> & vectorData)
{
    vectorData.clear();
    vectorData.reserve((unsigned)bytesOfData.size());
    for(auto & b : bytesOfData)
    {
        vectorData.emplace_back((char)b.to_ulong());
    }
}

//This converts a single bitset to a single unsigned char
void convert_bitSetToUnsignedChar(std::bitset<sizeof(unsigned char)*8> & byteOfData, unsigned char & unsignedCharData)
{
    unsignedCharData = (char)byteOfData.to_ulong();
}

//This converts a single unsigned char to a single bitset
void convert_unsignedCharToBitSet(unsigned char & unsignedCharData, std::bitset<sizeof(unsigned char)*8> & byteOfData)
{
    byteOfData = std::bitset<sizeof(unsigned char)*8>(unsignedCharData);
}

//This receives a single bitset and returns a single unsigned char (convert)
unsigned char convert_bitSetToUnsignedChar(std::bitset<sizeof(unsigned char)*8> & byteOfData)
{
    return (char)byteOfData.to_ulong();
}

//This receives a single unsigned char and returns a single bitset (convert)
std::bitset<sizeof(unsigned char)*8> convert_unsignedCharToBitSet(unsigned char & unsignedCharData)
{
    return std::bitset<sizeof(unsigned char)*8>(unsignedCharData);
}

//This converts a vector of bitset to a vector of unsigned char and return the vector of unsigned char
std::vector<unsigned char> vectorConvert_bitSetToUnsignedChar(std::vector<std::bitset<sizeof(unsigned char)*8>> & bytesOfData)
{
    std::vector<unsigned char> vectorData;
    vectorData.clear();
    vectorData.reserve((unsigned)bytesOfData.size());
    for(auto & b : bytesOfData)
    {
        vectorData.emplace_back((char)b.to_ulong());
    }
    return vectorData;
}

//This converts a vector of unsigned char to a vector of bitsets
void vectorConvert_unsignedCharToBitSet(std::vector<unsigned char> & vectorData, std::vector<std::bitset<sizeof(unsigned char)*8>> & bytesOfData)
{
    bytesOfData.clear();
    bytesOfData.reserve((unsigned)vectorData.size());
    for(auto & c : vectorData)
    {
        bytesOfData.emplace_back(std::bitset<sizeof(unsigned char)*8>(c));
    }
}

//This converts a vector of unsigned char to a vector of bitsets and return the vector of bitsets
std::vector<std::bitset<sizeof(unsigned char)*8>> vectorConvert_unsignedCharToBitSet(std::vector<unsigned char> & vectorData)
{
    std::vector<std::bitset<sizeof(unsigned char)*8>> bytesOfData;
    bytesOfData.clear();
    bytesOfData.reserve((unsigned)vectorData.size());
    for(auto & c : vectorData)
    {
        bytesOfData.emplace_back(std::bitset<sizeof(unsigned char)*8>(c));
    }
    return bytesOfData;
}





//This returns the size of the file in bytes.
std::size_t getFileSizeInBytes(fs::path & inputPath)
{
    if(fs::exists(inputPath))
        return fs::file_size(inputPath);
    return 0;
}

//This returns the size of the file in bits.
std::size_t getFileSizeInBits(fs::path & inputPath)
{
    if(fs::exists(inputPath))
        return fs::file_size(inputPath)*8;
    return 0;
}

#endif
