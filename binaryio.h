#ifndef BINARY_IO_H_
#define BINARY_IO_H

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
