#include "shortArray.hpp"
#include <iostream>

ShortArray::ShortArray() : isDynamic(false), smallLength(0) {}
ShortArray::ShortArray(const short* array, size_t len)
{
    if (len <= 12) {
        isDynamic = false;
        smallLength = len;
        for (size_t i = 0; i < len; i++) {
            small[i] = array[i];
        }
    } else {
        isDynamic = true;
        dynamic.length = len;
        dynamic.memory = len;
        dynamic.ar = new short[dynamic.memory];
        for (size_t i = 0; i < len; i++) {
            dynamic.ar[i] = array[i];
        }
    }
}

ShortArray::~ShortArray(){
    if (isDynamic)
    {
        delete[] dynamic.ar;
    }
}
short& ShortArray::operator[](int i)
{
    if (i >= size()) {
        throw std::out_of_range("Index out of range");
    }
    
    if (isDynamic) {
        return dynamic.ar[i];
    } else {
        return small[i];
    }
}

void ShortArray::push(short new_val)
{
    if (isDynamic)
    {
        short* newAr = new short[dynamic.length + 1];
        for (int i = 0; i < dynamic.length; i++){
            newAr[i] = dynamic.ar[i];
        }
        dynamic.length += 1;
        newAr[dynamic.length - 1] = new_val;
        delete[] dynamic.ar;
        dynamic.ar = newAr;
        dynamic.memory = dynamic.length;
    }
    else
    {
        if (smallLength < 12) {
            small[smallLength] = new_val;
            smallLength += 1;
        }
    }
    
}
short ShortArray::pop(){
    if (isDynamic){
        if (dynamic.length == 0) {
            throw std::out_of_range("Cannot pop from empty array");
        }
        short* newAr = new short[dynamic.length - 1];
        short val = dynamic.ar[dynamic.length - 1];
        for (int i = 0; i < dynamic.length - 1; i++){
            newAr[i] = dynamic.ar[i];
        }
        dynamic.length -= 1;
        delete[] dynamic.ar;
        dynamic.ar = newAr;
        dynamic.memory = dynamic.length;
        return val;
    }
    else
    {
        if (smallLength == 0) {
            throw std::out_of_range("Cannot pop from empty array");
        }
        short val = small[smallLength - 1];
        smallLength -= 1;
        return val;
    }
    
}
size_t ShortArray::size() const
{
    if (isDynamic) {
        return dynamic.length;
    } else {
        return smallLength;
    }
}

void ShortArray::resize(size_t newSize, short fillValue)
{
    if (isDynamic)
    {
        short *newAr = new short[newSize];
        for (int i = 0; i < dynamic.length; i++){
            newAr[i] = dynamic.ar[i];
        }
        for (int i = dynamic.length; i < newSize; i++){
            newAr[i] = fillValue;
        }
        delete[] dynamic.ar;
        dynamic.ar = newAr;
        dynamic.length = newSize;
        dynamic.memory = newSize;
    }
    else
    {
        // Встроенный режим
        if (newSize <= 12) {
            if (newSize > smallLength) {
                for (size_t i = smallLength; i < newSize; i++) {
                    small[i] = fillValue;
                }
            }
            smallLength = newSize;
            
        } else {
            // Нужно переключиться на динамический режим
            size_t oldLength = smallLength;
            short* newAr = new short[newSize];
            for (size_t i = 0; i < oldLength; i++) {
                newAr[i] = small[i];
            
            for (size_t i = oldLength; i < newSize; i++) {
                newAr[i] = fillValue;
            }
            // Переключаемся на динамический режим
            dynamic.ar = newAr;
            dynamic.length = newSize;
            dynamic.memory = newSize;
            isDynamic = true;
        }
    }
    
    }
}

void ShortArray::printAr()
{
    if (isDynamic){
        for (int i = 0; i < dynamic.length; i++)
        {
            std::cout << dynamic.ar[i];
        }
    }
    else
    {
        for (int i = 0; i < smallLength; i++)
        {
            std::cout << small[i];
        }
    }
    
    std::cout << "\n";
}

void ShortArray::convertToDynamic()
{
    if (isDynamic) return;  
    
    size_t len = smallLength;
    size_t newMemory = (len < 4) ? 4 : len * 2;  
    short* newAr = new short[newMemory];
    
    for (size_t i = 0; i < len; i++) {
        newAr[i] = small[i];
    }
    
    dynamic.ar = newAr;
    dynamic.length = len;
    dynamic.memory = newMemory;
    
    isDynamic = true;
    
}