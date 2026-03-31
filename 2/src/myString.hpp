#pragma once
#include <iostream>
#include <stdexcept>

class myString
{
private:
    char* data;
    int length;
public:
    myString();
    myString(const char* str);
    myString(const myString& other);

    ~myString();

    char get(int i) const;
    void set(int i, char c);
    void setNewString(const char *str);
    void print() const;
    void readLine();

    const char* getData() const { return data; }
    int getLength(const char* str);

    void copyString(char* dest, const char* src);

    myString& operator=(const myString& a);
    myString& operator+=(const myString& a);
    myString operator+(const myString& a) const;

    bool operator==(const myString& other) const;
    bool operator!=(const myString& other) const;
    bool operator<(const myString& other) const;
    bool operator<=(const myString& other) const;
    bool operator>(const myString& other) const;
    bool operator>=(const myString& other) const;
    
    bool operator==(const char* str) const;
    bool operator!=(const char* str) const;
    bool operator<(const char* str) const;
    bool operator<=(const char* str) const;
    bool operator>(const char* str) const;
    bool operator>=(const char* str) const;

    char& operator[](int index);
};
myString operator+(const char* str, const myString& s);

bool operator==(const char* str, const myString& s);
bool operator!=(const char* str, const myString& s);
bool operator<(const char* str, const myString& s);
bool operator<=(const char* str, const myString& s);
bool operator>(const char* str, const myString& s);
bool operator>=(const char* str, const myString& s);

std::ostream& operator<<(std::ostream& os, const myString& s);
std::istream& operator>>(std::istream& is, myString& s);

myString addTxtExtension(const myString &path);