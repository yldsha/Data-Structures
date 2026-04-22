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
         struct {
            short small[11];
            unsigned char size : 7;   
            unsigned char flag : 1;  
        } bits;
    };
    
    
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
    void setMem(size_t newmemory){dynamic.memory = newmemory;}
    void setDynamicMode() {bits.flag = 0;}
    bool isDynamic() const {return bits.flag == 0;}
    
    
};