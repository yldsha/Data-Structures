#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main() {
    std::cout << "Тестирование операций Rect:\n";

    // Тест 1: move (dx, dy)
    Rect r1(1, 4, 5, 2);  
    r1.move(2, 3);
    assert(r1.getLeft() == 3);    // 1+2=3
    assert(r1.getRight() == 6);   // 4+2=6
    assert(r1.getTop() == 8);     // 5+3=8
    assert(r1.getBottom() == 5);  // 2+3=5
    assert(r1.getWidth() == 3);   // не изменилось
    assert(r1.getHeight() == 3);  // не изменилось
    std::cout << "move с положительными значениями прошёл\n";

    // Тест 2: move с отрицательными значениями
    Rect r2(3, 7, 9, 5);
    r2.move(-2, -1);
    assert(r2.getLeft() == 1);
    assert(r2.getRight() == 5);
    assert(r2.getTop() == 8);
    assert(r2.getBottom() == 4);
    std::cout << "move с отрицательными значениями прошёл\n";

    // Тест 3: move на ноль
    Rect r3(2, 6, 8, 4);
    r3.move(0, 0);
    assert(r3.getLeft() == 2);
    assert(r3.getRight() == 6);
    assert(r3.getTop() == 8);
    assert(r3.getBottom() == 4);
    std::cout << "move с нулевыми значениями прошёл\n";

    // Тест 4: inflate с положительными значениями
    Rect r4(2, 5, 6, 3);  
    r4.inflate(1, 2);     // dh=1 (вертикаль), dw=2 (горизонталь)
    assert(r4.getLeft() == 0);    // left - dw = 2 - 2 = 0
    assert(r4.getRight() == 7);   // right + dw = 5 + 2 = 7
    assert(r4.getTop() == 7);     // top + dh = 6 + 1 = 7
    assert(r4.getBottom() == 2);  // bottom - dh = 3 - 1 = 2
    std::cout << "inflate с положительными значениями прошёл\n";

    // Тест 5: inflate с отрицательными значениями 
    Rect r5(2, 8, 7, 1);  
    r5.inflate(-1, -2);   // dh=-1, dw=-2
    assert(r5.getLeft() == 4);    // left - (-2) = left + 2 = 2 + 2 = 4
    assert(r5.getRight() == 6);   // right + (-2) = right - 2 = 8 - 2 = 6
    assert(r5.getTop() == 6);     // top + (-1) = top - 1 = 7 - 1 = 6
    assert(r5.getBottom() == 2);  // bottom - (-1) = bottom + 1 = 1 + 1 = 2
    std::cout << "inflate с отрицательными значениями прошёл\n";
    // Тест 6: inflate на ноль
    Rect r6(3, 7, 9, 4);
    r6.inflate(0, 0);
    assert(r6.getLeft() == 3);
    assert(r6.getRight() == 7);
    assert(r6.getTop() == 9);
    assert(r6.getBottom() == 4);
    std::cout << "inflate с нулевыми значениями прошёл\n";

    std::cout << "Все тесты операций Rect прошли успешно\n";
    return 0;
}