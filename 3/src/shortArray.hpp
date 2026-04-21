#pragma once
#include <iostream>
#include <cstdint> 

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
        struct {
            unsigned char size : 7;   // 7 битов для размера (0-12)
            unsigned char flag : 1;   // 1 бит для флага (0=динамический, 1=статический)
        } bits;
    };
    bool isDynamic() const {return bits.flag == 0;}
    void setDynamicMode() {bits.flag = 0;}
    void setStaticMode(size_t staticSize) {
        bits.flag = 1;
        bits.size = staticSize;
    }
    size_t getStaticSize() const {return bits.size;}
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