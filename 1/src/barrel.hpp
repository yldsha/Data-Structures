#pragma once
#include <iostream>

class Barrel
{
private:
    double alcohol;
    double water;
public:
    Barrel(double alc, double wat);
    
    double getVolume() const;
    double getAlcohol() const;
    double getWater() const;
    double getConcentration();
    
    void setAlcohol(double alc);
    void setWater(double wat);

    void pour(Barrel& to, double amount);
    
};

 