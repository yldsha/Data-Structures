#include "myString.hpp"
#include <iostream>

myString::myString() 
:  length(0) {
    data = new char[1];
    data[0] = '\0';
}
myString::myString(const char* str){
    if (str == nullptr) {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    } else {
        length = getLength(str);
        data = new char[length + 1];  
        copyString(data, str);
    }
}
myString::~myString() {
     
        delete[] data;
        
    
}

char myString::get(int i) const {
    if (i < 0 || i >= length) {
        std::cout << "Индекс вне диапазона" << std::endl;
        return '\0';
    }
    return data[i];
}

void myString::set(int i, char c){
    if (i < 0 || i >= length) {
        std::cout << "Индекс вне диапазона" << std::endl;
        return;
    }
    data[i] = c;
}

void myString::setNewString(const char *str){
    delete[] data;
    if (str == nullptr) {
        data = new char[1];
        data[0] = '\0';
        length = 0;
        return;
    }
    length = getLength(str);
    data = new char[length + 1];
    copyString(data, str);
}
void myString::print(){
    if (data != nullptr) {
        std::cout << data;
    }
}
void myString::readLine() {
    delete[] data;
    int capacity = 64;
    data = new char[capacity];
    int position = 0;
    
    char ch;
    while (std::cin.get(ch) && ch != '\n') {
        if (position >= capacity - 1) {
            int newCapacity = capacity * 2;
            char* newData = new char[newCapacity];
            copyString(newData, data);
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        
        data[position++] = ch;
    }
    
    data[position] = '\0';
    length = position;
}

myString::myString(const myString& other) : data(nullptr), length(other.length) {
    data = new char[length + 1];
    for (int i = 0; i <= length; ++i) {  
        data[i] = other.data[i];
    }
}

int myString::getLength(const char* str) {
    if (str == nullptr) return 0;
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void myString::copyString(char* dest, const char* src) {
    if (src == nullptr) {
        dest[0] = '\0';
        return;
    }
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

