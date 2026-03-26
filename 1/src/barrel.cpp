#include "barrel.hpp"

Barrel::Barrel(double alc, double wat)
: alcohol(alc), water(wat){}

double Barrel::getVolume() const {return alcohol + water;}
double Barrel::getAlcohol() const {return alcohol;}
double Barrel::getWater() const {return water;}
double Barrel::getConcentration() {
  double total = alcohol + water;
  if (total==0){return 0;}
  return (alcohol / total) * 100;
}

void Barrel::setAlcohol(double alc){alcohol = alc;}
void Barrel::setWater(double wat){water = wat;}

void Barrel::pour(Barrel& to, double amount){
  double totalFrom = getAlcohol() + getWater();
  if (totalFrom <= 0){
    std::cout<<"Бочка пуста"<<std::endl;
    return;
  }
  double actualAmount = amount;
  if (totalFrom < actualAmount) {
    actualAmount = totalFrom;
    std::cout<<actualAmount<<std::endl;
  }
  double part = actualAmount/totalFrom;

  double alcoholFrom = getAlcohol() * part;
  double waterFrom = getWater() * part;

  setAlcohol(getAlcohol() - alcoholFrom);
  setWater(getWater() - waterFrom);

  to.setAlcohol(to.getAlcohol() + alcoholFrom);
  to.setWater(to.getWater() + waterFrom);

} 
