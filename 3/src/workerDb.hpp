#pragma once
#include "../../2/src/myString.hpp"
const unsigned int BASECAPACITY = 100;
struct WorkerData
{
    myString name;
    myString position;
    double salary;
    int age;

    WorkerData() : age(0), salary(0) {}
    WorkerData(const myString& n, int a, const myString& pos, double sal) 
        : name(n), age(a), position(pos), salary(sal) {}

    void setName(const myString& n) { name = n; }
    void setAge(int a) { age = a; }
    void setPosition(const myString& pos) { position = pos; }
    void setSalary(double sal) { salary = sal; }
};

class WorkerDb
{
private:
    myString surnames[BASECAPACITY];
    WorkerData workers[BASECAPACITY];
    int count;

    int findIndex(const myString& surname) const;
public:
    WorkerDb() : count(0) {}
    WorkerData& operator[](const myString surname);
    bool exists(const myString& surname) const;
    bool remove(const myString& surname);
    int getCount() const;

    class Iterator {
    private:
        WorkerDb* db;
        int position;
        
    public:
        Iterator(WorkerDb* database, int pos) : db(database), position(pos) {}
        
        // Оператор разыменования *
        WorkerData& operator*() {
            return db->workers[position];
        }
        
        // Оператор доступа ->
        WorkerData* operator->() {
            return &(db->workers[position]);
        }
        
        // Метод key() - возвращает фамилию
        myString key() const {
            return db->surnames[position];
        }
        
       
        Iterator& operator++() {
            position++;
            return *this;
        }
        
      
        Iterator operator++(int) {
            Iterator temp = *this;
            position++;
            return temp;
        }
        
        bool operator!=(const Iterator& other) const {
            return position != other.position;
        }
        
        bool operator==(const Iterator& other) const {
            return position == other.position;
        }
    };
    
       
        Iterator begin() {
            return Iterator(this, 0);
        }
        
        Iterator end() {
            return Iterator(this, count);
    }

    
   
};

double getAvgAge(WorkerDb& db);
void printDb(WorkerDb& db);

