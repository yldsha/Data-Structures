#pragma once
#include <iostream>

class ShortArray
{
private:
    union {
        struct {            
            short* ar;
            size_t length;
            size_t memory;
        } dynamic;
        short small[12];
    };
    bool isDynamic;         // true = динамический, false = встроенный
    size_t smallLength;     // длина для встроенного режима (0-12)
public:
    ShortArray();
    ShortArray(const short* ar, size_t len); 
    ~ShortArray();

    short& operator[](int i);
    void push(short new_val);
    short pop();
    size_t size() const;
    void resize(size_t newSize, short fillValue = 0);
    void printAr();
    void convertToDynamic();
};