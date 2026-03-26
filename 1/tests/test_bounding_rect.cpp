#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main() {
    std::cout << "Тестирование boundingRect:\n";

    // Тест 1: Обычные прямоугольники (не пересекаются)
    Rect r1(1, 4, 5, 2);   
    Rect r2(6, 9, 8, 5);   
    Rect b1 = boundingRect(r1, r2);
    assert(b1.getLeft() == 1);    // min(left) = 1
    assert(b1.getRight() == 9);   // max(right) = 9
    assert(b1.getTop() == 8);     // max(top) = 8
    assert(b1.getBottom() == 2);  // min(bottom) = 2
    std::cout << "Непересекающиеся прямоугольники прошли\n";

    // Тест 2: Пересекающиеся прямоугольники
    Rect r3(1, 5, 5, 1);
    Rect r4(3, 7, 7, 3);
    Rect b2 = boundingRect(r3, r4);
    assert(b2.getLeft() == 1);
    assert(b2.getRight() == 7);
    assert(b2.getTop() == 7);
    assert(b2.getBottom() == 1);
    std::cout << "Пересекающиеся прямоугольники прошли\n";

    // Тест 3: Один внутри другого
    Rect r5(0, 10, 10, 0);
    Rect r6(2, 8, 8, 2);
    Rect b3 = boundingRect(r5, r6);
    assert(b3.getLeft() == 0);
    assert(b3.getRight() == 10);
    assert(b3.getTop() == 10);
    assert(b3.getBottom() == 0);
    std::cout << "Один внутри другого прошли\n";

    // Тест 4: Отрицательные координаты
    Rect r7(-5, -1, 2, -3);   
    Rect r8(-3, 2, 4, -1);   
    Rect b4 = boundingRect(r7, r8);
    assert(b4.getLeft() == -5);  
    assert(b4.getRight() == 2); 
    assert(b4.getTop() == 4);     
    assert(b4.getBottom() == -3); 
    std::cout << "Отрицательные координаты прошли\n";

    // Тест 5: Перепутанные координаты
    Rect r9(10, 5, 0, 5);   
    Rect r10(2, 6, 7, 3);  
    Rect b5 = boundingRect(r9, r10);
    assert(b5.getLeft() == 2);    // min(5,2)=2
    assert(b5.getRight() == 10);  // max(10,6)=10
    assert(b5.getTop() == 7);     // max(5,7)=7
    assert(b5.getBottom() == 0);  // min(0,3)=0
    std::cout << "Перепутанные координаты прошли\n";

    std::cout << "Все тесты boundingRect прошли успешно\n";
    return 0;
}