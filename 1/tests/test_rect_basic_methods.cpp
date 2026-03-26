#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main() {
    std::cout << "Тестирование базовых методов Rect:\n";

    // Тест 1: Конструктор по умолчанию
    Rect r1;
    assert(r1.getLeft() == 0);
    assert(r1.getRight() == 0);
    assert(r1.getTop() == 0);
    assert(r1.getBottom() == 0);
    std::cout << "Конструктор по умолчанию прошел\n";

    // Тест 2: Конструктор с параметрами (left, right, top, bottom)
    Rect r2(1, 3, 4, 2);  
    assert(r2.getLeft() == 1);
    assert(r2.getRight() == 3);
    assert(r2.getTop() == 4);
    assert(r2.getBottom() == 2);
    std::cout << "Конструктор с параметрами прошел\n";


    // Тест 4: Конструктор копирования
    Rect r3(r2);
    assert(r3.getLeft() == 1);
    assert(r3.getRight() == 3);
    assert(r3.getTop() == 4);
    assert(r3.getBottom() == 2);
    std::cout << "Конструктор копирования прошел\n";

    // Тест 5: Метод setAll
    Rect r4;
    r4.setAll(5, 7, 8, 6); 
    assert(r4.getLeft() == 5);
    assert(r4.getRight() == 7);
    assert(r4.getTop() == 8);
    assert(r4.getBottom() == 6);
    assert(r4.getWidth() == 2);
    assert(r4.getHeight() == 2);
    std::cout << "Метод setAll прошел\n";

    std::cout << "Все тесты Rect прошли успешно!\n";
    return 0;
}