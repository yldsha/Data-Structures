#include "myString.hpp"
#include <iostream>
#include <stdexcept> 

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
void myString::print() const{
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
    for (int i = 0; i < length; ++i) {  
        data[i] = other.data[i];
    }
    data[length] = '\0';  
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

myString& myString::operator=(const myString& a)
{
    if (this == &a){
        return *this;
    }
    length = a.length;
    delete[] data;
    data = new char[getLength(a.data) + 1];
    copyString(data, a.data);
    return *this;
}
myString& myString::operator+=(const myString& a)
{
    if (this == &a) {
        char* newData = new char[length * 2 + 1];
        for (int i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        for (int i = 0; i < length; i++) {
            newData[length + i] = data[i];
        }
        newData[length * 2] = '\0';
        delete[] data;
        data = newData;
        length *= 2;
        return *this;
    }
    if (a.data == nullptr){
        return *this;
    }
    char* newData = new char[a.length + length + 1];
    for (int i = 0; i < length; i++){
        newData[i] = data[i];
    }
    for (int i = 0; i < a.length; i++) {
        newData[length + i] = a.data[i];
    } 
    length = length + a.length;
    newData[length] = '\0'; 
    delete[] data;
    data = newData;
    return *this;
}
myString myString::operator+(const myString& a) const
{
    myString result(*this);
    return result += a;
}
myString operator+(const char* str, const myString& s)
{
    return myString(str) + s;
}

bool myString::operator==(const myString& other) const
{
    return strcmp(data, other.data) == 0;
}

bool myString::operator!=(const myString& other) const
{
    return strcmp(data, other.data) != 0;
}

bool myString::operator<(const myString& other) const
{
    return strcmp(data, other.data) < 0;
}

bool myString::operator<=(const myString& other) const
{
    return strcmp(data, other.data) <= 0;
}

bool myString::operator>(const myString& other) const
{
    return strcmp(data, other.data) > 0;
}

bool myString::operator>=(const myString& other) const
{
    return strcmp(data, other.data) >= 0;
}


bool myString::operator==(const char* str) const
{
    if (str == nullptr) return false;
    return strcmp(data, str) == 0;
}

bool myString::operator!=(const char* str) const
{
    if (str == nullptr) return true;
    return strcmp(data, str) != 0;
}

bool myString::operator<(const char* str) const
{
    if (str == nullptr) return false;
    return strcmp(data, str) < 0;
}

bool myString::operator<=(const char* str) const
{
    if (str == nullptr) return false;
    return strcmp(data, str) <= 0;
}

bool myString::operator>(const char* str) const
{
    if (str == nullptr) return true;
    return strcmp(data, str) > 0;
}

bool myString::operator>=(const char* str) const
{
    if (str == nullptr) return true;
    return strcmp(data, str) >= 0;
}

bool operator==(const char* str, const myString& s)
{
    if (str == nullptr) return false;
    return strcmp(str, s.getData()) == 0;
}

bool operator!=(const char* str, const myString& s)
{
    if (str == nullptr) return true;
    return strcmp(str, s.getData()) != 0;
}

bool operator<(const char* str, const myString& s)
{
    if (str == nullptr) return true;
    return strcmp(str, s.getData()) < 0;
}

bool operator<=(const char* str, const myString& s)
{
    if (str == nullptr) return true;
    return strcmp(str, s.getData()) <= 0;
}

bool operator>(const char* str, const myString& s)
{
    if (str == nullptr) return false;
    return strcmp(str, s.getData()) > 0;
}

bool operator>=(const char* str, const myString& s)
{
    if (str == nullptr) return false;
    return strcmp(str, s.getData()) >= 0;
}

char& myString::operator[](int index)
{
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

std::ostream& operator<<(std::ostream& os, const myString& s)
{
    if (s.getData() != nullptr) {
        os << s.getData();
    }
    return os;
}

std::istream& operator>>(std::istream& is, myString& s)
{
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    
    is.getline(buffer, BUFFER_SIZE);
    

    s.setNewString(buffer);
    
    return is;
}

myString addTxtExtension(const myString &path) { return path + ".txt"; }