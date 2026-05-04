#include "pointCircle.hpp"
#include <iostream>

List::List(){
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}
List::~List(){
    while (head != nullptr) {
        Node* temp = head;
        head = head->getNext();
        delete temp;
    }
}
void List::pushFront(const Circle& data){
    Node* newNode = new Node(data);
        if (head == nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            newNode->setNext(head);
            head->setPrev(newNode);
            head = newNode;
        }
        m_size++;
}
void List::pushBack(const Circle& data){
    Node* newNode = new Node(data);
    if (head == nullptr){
        head = newNode;
        tail = newNode;
    }
    else {
        tail -> setNext(newNode);
        newNode -> setPrev(tail);
        tail = newNode;
    }
    m_size++;
}
bool List::removeByCircle(const Circle& circle){
    Node* current = head;
    while (current != nullptr){
        const Circle& currentCircle = current->getData();
        if (currentCircle.getCenter().getX() == circle.getCenter().getX() &&
            currentCircle.getCenter().getY() == circle.getCenter().getY() &&
            currentCircle.getRadius() == circle.getRadius())
            {
                if (current -> getPrev() != nullptr){
                    current -> getPrev() -> setNext(current -> getNext());
                }
                else {
                    head = current -> getNext();
                }
                if (current -> getNext() != nullptr){
                    current -> getNext() -> setPrev(current -> getPrev());
                }
                else {
                    tail = current -> getPrev();
                }
                delete current;
                m_size--;
                return true;
            }
            current = current -> getNext();
    }
    return false;
}

void printList(List& list){
    Node* current = list.getHead();
    int index = 0;
    while (current != nullptr) {
        const Circle& c = current->getData();
        std::cout << index++ << ": center (" << c.getCenter().getX() 
        << ";" << c.getCenter().getY() << ") radius: " << c.getRadius() 
        << std::endl;
        current = current->getNext();
    }
    std::cout<<std::endl;
}

void List::listSort(){
    Node* start = head;
    while (start != nullptr){
        Node* min = start;
        Node* current = start -> getNext();
        while (current != nullptr){
            if (current->getData().getRadius() < min->getData().getRadius()){
                min = current;
            }
            current = current->getNext();
        }
        if (min != start){
            Circle tmp = start->getData();
            start->getData() = min->getData();
            min->getData() = tmp;
        }
        start = start->getNext();
        
    }
}