#pragma once
#include <cstddef>
#include <iostream>
class Point 
{
private:
    int x;
    int y;
public:
    Point(){x = 0; y = 0;}
    Point(int newX, int newY){x = newX; y = newY;}
    ~Point(){std::cout<<"~Point"<<std::endl;}
    int getX() const {return x;}
    int getY() const {return y;}
    void setX(int newX){x = newX;}
    void setY(int newY){y = newY;}
};

class Circle
{
private: 
    Point center;
    int radius;
public:
    Circle(): center(0,0), radius(0){}
    Circle(const Point& p, int r){center = p; radius = r; std::cout<<"Circle"<<std::endl;}
    Circle(int x, int y, int r){center = Point(x,y); radius = r;}

    Point getCenter() const { return center; }
    int getRadius() const { return radius; }
    void setRadius(int newRadius){radius = newRadius;}
    ~Circle(){}
};

class Node
{
private:
    Node* pPrev;   
    Node* pNext;   
    Circle m_data; 

public:
    Node() : pPrev(nullptr), pNext(nullptr), m_data(0, 0, 0) {}

    Node(const Circle& data) : pPrev(nullptr), pNext(nullptr), m_data(data) {}

    ~Node() {
        if (pPrev != nullptr) {
            pPrev->pNext = pNext;
        }
        if (pNext != nullptr) {
            pNext->pPrev = pPrev;
        }
    }

    void setNext(Node* next) { pNext = next; }
    void setPrev(Node* prev) { pPrev = prev; }
    Node* getNext() const { return pNext; }
    Node* getPrev() const { return pPrev; }
    
    const Circle& getData() const { return m_data; }
    Circle& getData() { return m_data; }
};

class List
{
    Node* head;
    Node* tail;
    size_t m_size;
public:
    List();
    ~List();
    List& operator=(const List& other);
    
    void pushFront(const Circle& data);
    void pushBack(const Circle& data);
    bool removeByCircle(const Circle& circle);

    Node* getHead() const {return head;}
    Node* getTail() const {return tail;}
    size_t getSize() const {return m_size;}
    void listSort();
};

void printList(List& list);
