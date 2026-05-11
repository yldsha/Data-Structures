#include <iostream>
#include "pointCircle.hpp"

int main() 
{
    List myList;
    std::cout << "1. Создан пустой список" << std::endl;
    std::cout << "   Размер: " << myList.getSize() << std::endl << std::endl;
    
    std::cout<<"-----"<<std::endl;
    //myList.pushBack(Circle(Point(3,4), 5));
    std::cout<<"-----"<<std::endl;
    //myList.pushBack(Circle(1, 1, 3));
    //myList.pushBack(Circle(2, 2, 7));
    //printList(myList);

    myList.pushFront(Circle(10, 10, 2));
    printList(myList);

    Circle toRemove(1, 1, 3);
    bool removed = myList.removeByCircle(toRemove);
    if (removed) {
        std::cout << "   Круг успешно удален!" << std::endl;
    } else {
        std::cout << "   Круг не найден!" << std::endl;
    }
    printList(myList);

    Circle notExist(99, 99, 99);
    removed = myList.removeByCircle(notExist);
    if (removed) {
        std::cout << "   Круг успешно удален!" << std::endl;
    } else {
        std::cout << "   Круг не найден (это ожидаемо)!" << std::endl;
    }
    printList(myList);


    List list1;
    list1.pushBack(Circle(2, 5, 28));
    list1.pushBack(Circle(2, 5, 44));
    list1.pushBack(Circle(2, 5, 2));
    list1.pushBack(Circle(2, 5, 7));
    list1.pushBack(Circle(2, 5, 4));

    list1.listSort();
    printList(list1);

    return 0;

}