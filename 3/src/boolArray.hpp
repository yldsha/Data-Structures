#pragma once
#include <stdexcept>


class BoolArray {
private:
    unsigned char* data; // массив байтов для хранения битов
    size_t size; // кол-во элементов
    
    size_t getByteIndex(size_t index) const {
        return index / 8;
    }
    size_t getBitIndex(size_t index) const {
        return index % 8;
    }
public:
    BoolArray(size_t n);
    BoolArray(size_t n, bool value);
    BoolArray(const BoolArray& other);
    ~BoolArray();
    BoolArray& operator=(const BoolArray& other);
    size_t getSize() const;

    void set(size_t index, bool value);
    bool get(size_t index) const;
    void resize(size_t new_size, bool value = false);

    class Bit {
    private:
        unsigned char* byte;    // указатель на байт
        size_t bit;             // номер бита в байте
    public:
        Bit(unsigned char* b, size_t bt) : byte(b), bit(bt) {}
        
        // для записи: ar1[4] = true
        Bit& operator=(bool value);
        
        // для чтения: bool x = ar1[4]
        operator bool() const { return (*byte >> bit) & 1; }

        Bit& operator=(const Bit& other);
    };

    Bit operator[](size_t index);
   
};

void print(BoolArray ar);

