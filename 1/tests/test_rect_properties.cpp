#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main() {
    std::cout << "Тестирование свойств Rect:\n";

    // Тест 1: getWidth и getHeight
    Rect r1(1, 5, 4, 0);  
    assert(r1.getWidth() == 4);   
    assert(r1.getHeight() == 4);  
    assert(r1.getSquare() == 16); 
    std::cout << "getWidth/getHeight/getSquare прошли\n";

    // Тест 2: setWidth (изменение правой границы)
    Rect r2(2, 5, 3, 1);
    r2.setWidth(5);  
    assert(r2.getWidth() == 5);
    assert(r2.getRight() == 7);  // left 2 + width 5 = 7
    assert(r2.getHeight() == 2);  
    std::cout << "setWidth прошёл\n";

    // Тест 3: setHeight (изменение верхней границы)
    Rect r3(2, 5, 3, 1);
    r3.setHeight(4);  
    assert(r3.getHeight() == 4);
    assert(r3.getTop() == 5);  // bottom 1 + height 4 = 5
    assert(r3.getWidth() == 3);  
    std::cout << "setHeight прошёл\n";


    // Тест 5: Проверка на нулевую ширину/высоту
    Rect r5(2, 2, 5, 5);
    assert(r5.getWidth() == 0);
    assert(r5.getHeight() == 0);
    assert(r5.getSquare() == 0);
    r5.setWidth(1);
    assert(r5.getWidth() == 1);
    assert(r5.getLeft() == 3);
    std::cout << "Нулевые размеры прошли\n";

    std::cout << "Все тесты свойств Rect прошли успешно\n";
    return 0;
}