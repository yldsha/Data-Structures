#include "myString.hpp"

//Задание 2.3. Объект - обладатель ресурса.

#include <iostream>

int main() {
    myString str1;
    std::cout << "Пустая строка: ";
    str1.print();
    std::cout << std::endl;  
    
    // 2. Конструктор с параметром
    myString str2("Hello, world!");
    std::cout << "str2: ";
    str2.print();
    std::cout << std::endl;
    
    // 3. get()
    std::cout << "Первый символ: " << str2.get(0) << std::endl;
    
    // 4. set()
    std::cout << "Было: ";
    str2.print();
    std::cout << std::endl;
    
    str2.set(0, 'n');
    std::cout << "Стало: ";
    str2.print();
    std::cout << std::endl;
    
    // 5. setNewString()
    str2.setNewString("Новая строка");
    std::cout << "Новая строка: ";
    str2.print();
    std::cout << std::endl;
    
    // 6. readLine()
    myString str4;
    std::cout << "Введите строку: ";
    str4.readLine();
    std::cout << "Вы ввели: ";
    str4.print();
    std::cout << std::endl;
    

     /**
     * Проверьте, что ваша строка корректно работает в следующих ситуациях.
     */

    {
        myString s1;
        myString s2 = s1;
        s2.print();
        myString s3("This is my string");
        s3.print();
        std::cout<<"\n";
        myString s4 = s3;
        s4.print();
    } 

    
    return 0;
}
