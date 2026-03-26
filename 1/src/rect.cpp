#include "rect.hpp"
#include <iostream>

   Rect::Rect(int l, int r, int t, int b)
    : left(l), right(r), top(t), bottom(b) {
        /*std::cout << "Rect(param const) address:" << this << ", (" 
        << left << ", " << right << ", " << top << ", " << bottom << ")\n";*/
    }
    Rect::Rect()
    : left(0), right(0), top(0), bottom(0){
        /*std::cout << "Rect(default const) address:" << this << ", (0,0,0,0)\n";*/
    }
    Rect::Rect(const Rect& other)
    :left(other.left),
    right(other.right),
    top(other.top),
    bottom(other.bottom)
    {
        /*std::cout<<"Rect(copy const) address:" << this << ", ("
        << other.left << ", " << other.right << ", "
        << other.top << ", " << other.bottom << ")\n";*/
    }
    
   Rect::~Rect(){
    /*std::cout<<"Rect (dest) address:" << this << ", ("
            << left << ", " << right << ", "
            << top << ", " << bottom << ")\n";*/
   }

   int Rect::getLeft() const { return left; }
   int Rect::getRight() const { return right; }
   int Rect::getTop() const { return top; }
   int Rect::getBottom() const { return bottom; }

   int Rect::getHeight() const { 
        if (bottom < top){return top - bottom;}
        else{return bottom - top;}
   }
   int Rect::getWidth() const { 
        if (left < right){return right - left;}
        else{return left - right;}
   }
   int Rect::getSquare() const {
        return (getWidth() * getHeight());
   }

   void Rect::setAll(int nleft, int nright, int ntop, int nbottom){
        left = nleft;
        right = nright;
        top = ntop;
        bottom = nbottom;
   }
   void Rect::setWidth(int width){
        if (right > left){right = left + width;}
        else {left = right + width;}
   }
   void Rect::setHeight(int height){
        if (top > bottom){top = bottom + height;}
        else {bottom = top + height;}
   }
   
   void Rect::inflate(int amount){
        inflate(amount, amount);
   }
   void Rect::inflate(int dh, int dw){
        inflate(dw, dw, dh, dh);
   }
   void Rect::inflate(int dLeft, int dRight, int dTop, int dBottom){
        left -= dLeft;
        right += dRight;
        top += dTop;
        bottom -= dBottom;
   }
   void Rect::move(int dx, int dy ) {
        left += dx;
        right += dx;
        top += dy;
        bottom += dy;
   }
   

Rect boundingRect(const Rect& r1, const Rect& r2){
    int r1_left = std::min(r1.getLeft(), r1.getRight());
    int r1_right = std::max(r1.getLeft(), r1.getRight());
    int r1_top = std::max(r1.getTop(), r1.getBottom());
    int r1_bottom = std::min(r1.getTop(), r1.getBottom());

    int r2_left = std::min(r2.getLeft(), r2.getRight());
    int r2_right = std::max(r2.getLeft(), r2.getRight());
    int r2_top = std::max(r2.getTop(), r2.getBottom());
    int r2_bottom = std::min(r2.getTop(), r2.getBottom());
    
    int mLeft = (r1_left < r2_left ? r1_left : r2_left);
    
    int mRight;
    if (r1_right > r2_right){
        mRight = r1_right;
    } else {
        mRight = r2_right;
    }
    
    int mTop;
    if (r1_top > r2_top) {
        mTop = r1_top;
    } else {
        mTop = r2_top;
    }
    
    int mBottom;
    if (r1_bottom < r2_bottom) {
        mBottom = r1_bottom;
    } else {
        mBottom = r2_bottom;
    }

    return Rect(mLeft, mRight, mTop, mBottom);
}

void printRect(const Rect &r){
    std::cout<<"left: " << r.getLeft() << std::endl;
    std::cout<<"top: "<< r.getTop() << std::endl;
    std::cout<<"right: "<< r.getRight() << std::endl;
    std::cout<<"bottom: "<< r.getBottom() << std::endl;
}


