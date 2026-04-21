#include <iostream>
#include "boolArray.hpp"

BoolArray::BoolArray(size_t n): size(n)
{
    if (n == 0) {
            data = nullptr;
        } else {
            size_t bytesCount = (n + 7) / 8;
            data = new unsigned char[bytesCount]();
        }
}

BoolArray::~BoolArray()
{
    delete[] data;
}

BoolArray::BoolArray(size_t n, bool value) : size(n) {
        if (n == 0) {
            data = nullptr;
        } else {
            size_t bytesCount = (n + 7) / 8;
            data = new unsigned char[bytesCount]();
            
            if (value) {
                // Заполняем все единицами
                for (size_t i = 0; i < bytesCount; ++i) {
                    data[i] = 0xFF;
                }
                // Корректируем последний байт (лишние биты должны быть 0)
                size_t lastByteBits = n % 8; // cколько битов используется в последнем байте
                if (lastByteBits != 0) { // заполнен ли полсностью полследний байт
                    data[bytesCount - 1] &= (1 << lastByteBits) - 1;
                }
            }
        }
    }

BoolArray::BoolArray(const BoolArray& other) : size(other.size) {
    if (size == 0) {
        data = nullptr;
    } else {
        size_t bytesCount = (size + 7) / 8;
        data = new unsigned char[bytesCount];
        for (size_t i = 0; i < bytesCount; ++i) {
            data[i] = other.data[i];
        }
    }
}

BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        
        if (size == 0) {
            data = nullptr;
        } else {
            size_t bytesCount = (size + 7) / 8;
            data = new unsigned char[bytesCount];
            for (size_t i = 0; i < bytesCount; ++i) {
                data[i] = other.data[i];
            }
        }
    }
    return *this;
}

void BoolArray::set(size_t index, bool value){
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    size_t byteIdx = getByteIndex(index); // в каком байте лежит наш бит
    size_t bitIdx = getBitIndex(index); //какой по счету наш бит в этом байте
    
    if (value) {
        data[byteIdx] |= (1 << bitIdx);   // установить бит в 1
    } else {
        data[byteIdx] &= ~(1 << bitIdx);  // установить бит в 0
    }
}
size_t BoolArray::getSize() const {
    return size;
}
bool BoolArray::get(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    size_t byteIdx = getByteIndex(index);
    size_t bitIdx = getBitIndex(index);
    
    return (data[byteIdx] >> bitIdx) & 1; //сдвигает выбранный байт, чтобы наш бит оказался в крайней правой позиции
}
BoolArray::Bit& BoolArray::Bit::operator=(bool value) {
            if (value) *byte |= (1 << bit);
            else *byte &= ~(1 << bit);
            return *this;
}

BoolArray::Bit& BoolArray::Bit::operator=(const Bit& other) {
        bool value = (bool)other;
        if (value) *byte |= (1 << bit);
        else *byte &= ~(1 << bit);
        return *this;
}

BoolArray::Bit BoolArray::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return Bit(&data[getByteIndex(index)], getBitIndex(index));
}

void BoolArray::resize(size_t new_size, bool value)
{
    size_t newBytes = (new_size + 7) / 8;
    size_t oldBytes = (size + 7) / 8;
    unsigned char* newAr = new unsigned char[newBytes]();
    size_t copyBytes = (oldBytes < newBytes) ? oldBytes : newBytes;
    for (size_t i = 0; i < copyBytes; i++){
    newAr[i] = data[i];
    }

    delete[] data;

    if (new_size > size) {
    for (size_t i = size; i < new_size; i++) {
        size_t byteIdx = i / 8;
        size_t bitIdx = i % 8;
        if (value) {
            newAr[byteIdx] |= (1 << bitIdx);
        } else {
            newAr[byteIdx] &= ~(1 << bitIdx);
        }
    }
    }
    size_t lastByteBits = new_size % 8;
    if (lastByteBits != 0) {
        newAr[newBytes - 1] &= (1 << lastByteBits) - 1;
    }
    size = new_size;
    data = newAr;
}

void print(BoolArray ar){
    std::cout << "[";
        for (int i = 0; i < ar.getSize(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << ar[i];
        }
        std::cout << "]\n";
}