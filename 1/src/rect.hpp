#pragma once

class Rect
{
private:
    int left;
    int right;
    int top;
    int bottom;
public:
    Rect(int l, int r, int t, int b);
    Rect();
    Rect(const Rect& other);

   ~Rect();

   int getLeft() const;
   int getRight() const;
   int getTop() const;
   int getBottom() const;
   int getHeight() const;
   int getWidth() const;
   int getSquare() const;

   void setAll(int nleft, int nright, int ntop, int nbottom);
   void setWidth(int width);
   void setHeight(int height);
   
   void inflate(int amount);
   void inflate(int dh, int dw);
   void inflate(int dLeft, int dRight, int dTop, int dBottom);
   void move(int dx, int dy = 0) ;
};

Rect boundingRect(const Rect& r1, const Rect& r2);
   
void printRect(const Rect &r);