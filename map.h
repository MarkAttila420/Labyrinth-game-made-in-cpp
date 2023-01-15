#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <iostream>
#include <fstream>
#include "labstring.h"
#include "memtrace.h"

void vonal();
int beolvas(std::ifstream &f, char c=';');

class terkep{
    static int with;           //egy sor hossza
    static int height;         //hány sor van
public:
    int getw(){return with;}
    int geth(){return height;}
    String abra;
    terkep();
    terkep(std::ifstream &f);
    bool letezik();
    terkep &operator=(const terkep &t);
    friend std::ostream& operator<<(std::ostream& os, const terkep& t);
};


#endif // MAP_H_INCLUDED

