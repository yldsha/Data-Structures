#include <iostream>
#include "shortArray.hpp"

int main() {
    /*// Тест 1: статический режим (11 элементов)
    short data1[] = {1, 2, 3, 4, 5};
    ShortArray small(data1, 5);
    small.printAr();  // 1 2 3 4 5
    small.push(6);
    small.printAr();  // 1 2 3 4 5 6
    std::cout << "size: " << small.size() << std::endl;  // 6
    
    // Тест 2: переключение на динамический
    for (int i = 0; i < 10; i++) {
        small.push(i + 10);
    }
    small.printAr();  // все 16 элементов
    */
    // Тест 3: динамический режим
    short data2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    ShortArray big(data2, 15);
    big.setMem(0xFFFF);
    std::cout << big.isDynamic();
    //big.printAr();
    
    //std::cout << "sizeof(ShortArray): " << sizeof(ShortArray) << " байт" << std::endl;
    
    return 0;
}