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
    std::cout << " Тест2: RleFile " << std::endl;
    
    const size_t DATA_SIZE = 45000; 
    const size_t BUFFER_SIZE = 256;
    
    srand(static_cast<unsigned>(time(nullptr)));
    char* originalData = new char[DATA_SIZE];
    generateRandomData(originalData, DATA_SIZE);
  
    std::cout << "Оригинальные данные (первые 10 байт): ";
    for (int i = 0; i < 10; i++) {
        std::cout << (int)(unsigned char)originalData[i] << " ";
    }
    std::cout << std::endl;
    
    {
        RleFile rf("test_rlefile.bin", "w");
        size_t written = 0;
        while (written < DATA_SIZE) {
            size_t toWrite = (DATA_SIZE - written < BUFFER_SIZE) ? (DATA_SIZE - written) : BUFFER_SIZE;
            rf.write(originalData + written, toWrite);
            written += toWrite;
        }
        rf.flush();  
        rf.close();
        std::cout << "Записано байт: " << written << std::endl;
    }
    
    {
        RleFile rf("test_rlefile.bin", "r");
        char* readData = new char[DATA_SIZE];
        size_t totalRead = 0;
        while (totalRead < DATA_SIZE) {
            size_t toRead = (DATA_SIZE - totalRead < BUFFER_SIZE) ? (DATA_SIZE - totalRead) : BUFFER_SIZE;
            size_t r = rf.read(readData + totalRead, toRead);
            if (r == 0) break;
            totalRead += r;
        }
        
        std::cout << "Прочитано байт: " << totalRead << std::endl;
        
        std::cout << "Прочитанные данные (первые 10 байт): ";
        for (int i = 0; i < 10; i++) {
            std::cout << (int)(unsigned char)readData[i] << " ";
        }
        std::cout << std::endl;
        
        if (compareData(originalData, readData, DATA_SIZE)) {
            std::cout << "ТЕСТ ПРОЙДЕН" << std::endl;
        } else {
            std::cout << "ТЕСТ НЕ ПРОЙДЕН" << std::endl;
            
            for (size_t i = 0; i < DATA_SIZE; i++) {
                if (originalData[i] != readData[i]) {
                    std::cout << "Первое несовпадение на байте " << i << ": ";
                    std::cout << "ожидалось " << (int)(unsigned char)originalData[i];
                    std::cout << ", получено " << (int)(unsigned char)readData[i] << std::endl;
                    break;
                }
            }
            
            delete[] readData;
            delete[] originalData;
            return 1;
        }
        delete[] readData;
    }
    
    delete[] originalData;
    return 0;
}