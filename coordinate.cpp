#include "coordinate.h"

Coordinate::Coordinate(){
    Coordinate::x = -4;
    Coordinate::y = -4;
}//end null constructor

Coordinate::Coordinate(int x, int y){
    Coordinate::x = x;
    Coordinate::y = y;
}//end setter constructor

int Coordinate::getX(){
    return Coordinate::x;
}//end getX

int Coordinate::getY(){
    return Coordinate::y;
}//end getY

void Coordinate::setX(int x){
    Coordinate::x = x;
}//end setX

void Coordinate::setY(int y){
    Coordinate::y = y;
}//end setY