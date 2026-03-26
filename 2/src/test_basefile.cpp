#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "BaseFile.hpp"
#include "myString.hpp"

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
    std::cout << " Тест 1: BaseFile " << std::endl;
    
    const size_t DATA_SIZE = 45000; 
    const size_t BUFFER_SIZE = 1000;
    
    srand(static_cast<unsigned>(time(nullptr)));
    char* originalData = new char[DATA_SIZE];
    generateRandomData(originalData, DATA_SIZE);
    
    {
        BaseFile bf("test_basefile.bin", "w");
        size_t written = 0;
        while (written < DATA_SIZE) {
            size_t toWrite = (DATA_SIZE - written < BUFFER_SIZE) ? (DATA_SIZE - written) : BUFFER_SIZE;
            bf.write(originalData + written, toWrite);
            written += toWrite;
        }
    }
    FILE* f = fopen("test_basefile.bin", "rb");
if (f) {
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fclose(f);
    std::cout << "Сжатый файл имеет размер: " << file_size << " байт" << std::endl;
}
    {
        BaseFile bf("test_basefile.bin", "r");
        char* readData = new char[DATA_SIZE];
        size_t totalRead = 0;
        while (totalRead < DATA_SIZE) {
            size_t toRead = (DATA_SIZE - totalRead < BUFFER_SIZE) ? (DATA_SIZE - totalRead) : BUFFER_SIZE;
            size_t r = bf.read(readData + totalRead, toRead);
            if (r == 0) break;
            totalRead += r;
        }
        
        if (compareData(originalData, readData, DATA_SIZE)) {
            std::cout << "ТЕСТ ПРОЙДЕН" << std::endl;
        } else {
            std::cout << "ТЕСТ НЕ ПРОЙДЕН" << std::endl;
            delete[] readData;
            delete[] originalData;
            return 1;
        }
        delete[] readData;
    }
    
    delete[] originalData;
    return 0;
}

