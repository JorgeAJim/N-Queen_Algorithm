//coordinate.h

#ifndef COORDINATE_H_EXISTS
#define COORDINATE_H_EXISTS

class Coordinate {
    private:
        int x;
        int y;
    public:
        Coordinate();
        Coordinate(int x, int y);
        int getX();
        int getY();
        void setX(int x);
        void setY(int y);


};//end class definition

#endif