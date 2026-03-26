#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "BaseFile.hpp"

unsigned char* generateData(size_t size) {
    unsigned char* data = new unsigned char[size];
    for (size_t i = 0; i < size; i++) {
        data[i] = rand() % 256;  
    }
    return data;
}


bool testOneClass(const char* className, Ifile* fileForWrite, Ifile* fileForRead, size_t dataSize) {
    std::cout << "\nТест " << className << ":\n";
    
    unsigned char* original = generateData(dataSize);
    size_t written = 0;
    while (written < dataSize) {
        size_t blockSize = 256;
        if (written + blockSize > dataSize) {
            blockSize = dataSize - written;
        }
        fileForWrite->write(original + written, blockSize);
        written += blockSize;
    }
    delete fileForWrite; 
    
    unsigned char* readData = new unsigned char[dataSize];
    size_t read = 0;
    while (read < dataSize) {
        size_t blockSize = 256;
        if (read + blockSize > dataSize) {
            blockSize = dataSize - read;
        }
        read += fileForRead->read(readData + read, blockSize);
    }
    
    bool success = true;
    for (size_t i = 0; i < dataSize; i++) {
        if (original[i] != readData[i]) {
            success = false;
            break;
        }
    }
    
    if (success) {
        std::cout << " Тест пройден\n";
    } else {
        std::cout << " Тест не пройден\n";
    }
    
    delete[] original;
    delete[] readData;
    delete fileForRead;
    return success;
}

int main() {
    srand(time(nullptr));
    const size_t DATA_SIZE = 40 * 1024;  
    
    std::cout << "ЗАПУСК ТЕСТОВ\n";
    
    int passed = 0;
    
    // Тест BaseFile
    if (testOneClass("BaseFile", 
        new BaseFile("base_test.bin", "w"),
        new BaseFile("base_test.bin", "r"),
        DATA_SIZE)) { 
        passed++;
    }
    
    // Тест RleFile  
    remove("rle_test.bin");
    if (testOneClass("RleFile",
        new RleFile("rle_test.bin", "w"),
        new RleFile("rle_test.bin", "r"),
        DATA_SIZE)) { 
        passed++;
    }
    remove("rle2_test.bin");
    // Тест RleFile2
    if (testOneClass("RleFile2",
        new RleFile2(new BaseFile("rle2_test.bin", "w")),
        new RleFile2(new BaseFile("rle2_test.bin", "r")),
        DATA_SIZE)) {  
        passed++;
    }
    
    std::cout << "\n==============\n";
    std::cout << "ИТОГ: " << passed << "/3 тестов пройдено\n";
    
    return 0;
}