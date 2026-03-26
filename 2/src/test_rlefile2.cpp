#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "BaseFile.hpp"

void generateRandomData(char* data, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        data[i] = static_cast<char>(rand() % 256);
    }
}

bool compareData(const char* data1, const char* data2, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        if (data1[i] != data2[i]) {
            return false;
        }
    }
    return true;
}

int main()
{
    std::cout << " Тест3 : RleFile2 " << std::endl;
    
    const size_t DATA_SIZE = 45000; 
    const size_t BUFFER_SIZE = 256;
    
    srand(static_cast<unsigned>(time(nullptr)));
    char* originalData = new char[DATA_SIZE];
    generateRandomData(originalData, DATA_SIZE);
    
    
    {
        RleFile2 rf2(new BaseFile("test_rlefile2.bin", "w"));
        size_t written = 0;
        while (written < DATA_SIZE) {
            size_t toWrite = (DATA_SIZE - written < BUFFER_SIZE) ? (DATA_SIZE - written) : BUFFER_SIZE;
            rf2.write(originalData + written, toWrite);
            written += toWrite;
        }
    }
    
    {
        RleFile2 rf2(new BaseFile("test_rlefile2.bin", "r"));
        char* readData = new char[DATA_SIZE];
        size_t totalRead = 0;
        while (totalRead < DATA_SIZE) {
            size_t toRead = (DATA_SIZE - totalRead < BUFFER_SIZE) ? (DATA_SIZE - totalRead) : BUFFER_SIZE;
            size_t r = rf2.read(readData + totalRead, toRead);
            if (r == 0) break;
            totalRead += r;
        }
        
        if (compareData(originalData, readData, DATA_SIZE)) {
            std::cout << "ТЕСТ ПРОЙДЕН" << std::endl;
        } else {
            std::cout << "ТЕСТ НЕ ПРОЙДЕН" << DATA_SIZE << ")" << std::endl;
            delete[] readData;
            delete[] originalData;
            return 1;
        }
        delete[] readData;
    }
    
    delete[] originalData;
    return 0;
}

