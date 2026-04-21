#include "workerDb.hpp"
#include <iostream>
#include "../../2/src/myString.hpp"


int WorkerDb::findIndex(const myString& surname) const {
        for (int i = 0; i < count; i++) {
            if (surnames[i] == surname) {
                return i;
            }
        }
        return -1;  
    }

WorkerData& WorkerDb::operator[](const myString surname)
{
    int index = findIndex(surname);
        if (index != -1) {
            return workers[index];
        }
        // Если работника нет, создаем нового
        if (count < BASECAPACITY) {
            surnames[count] = surname;
            index = count;
            count++;
            return workers[index];
        } else {
            throw std::runtime_error("База данных переполнена!");
        }
}

 bool WorkerDb::exists(const myString& surname) const {
        return findIndex(surname) != -1;
}

bool WorkerDb::remove(const myString& surname) {
        int index = findIndex(surname);
        if (index == -1) {
            return false;
        }
        for (int i = index; i < count - 1; i++) {
            surnames[i] = surnames[i + 1];
            workers[i] = workers[i + 1];
        }
        
        count--;
        return true;
}
void printDb(WorkerDb& db) {
    std::cout << "=== База данных работников ===" << std::endl;

    for (auto it = db.begin(); it != db.end(); ++it) {
        std::cout << "Фамилия: " << it.key() 
                  << ", Имя: " << it->name
                  << ", Возраст: " << it->age
                  << ", Должность: " << it->position
                  << ", Зарплата: " << it->salary << std::endl;
    }
    
    std::cout << "================================" << std::endl;
}
    

int WorkerDb::getCount() const {
    return count;
}
double getAvgAge(WorkerDb& db) {
    int totalAge = 0;
    int count = 0;
    for (auto it = db.begin(); it != db.end(); ++it) {
        totalAge += it->age;
        count++;
    }
    if (count == 0) {
        return 0;  
    }
    return static_cast<double>(totalAge) / count;
}
