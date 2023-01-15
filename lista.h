#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <iostream>
#include "memtrace.h"

template<typename T>
class lista{
    int n;      //hossz
    T *elemek;
public:
    lista(const lista& l){
        n=l.n;
        elemek=new T[n];
        for(int i=0;i<n;i++){
            l.elemek[i]=elemek[i];
        }
    }
    int getn(){return n;}
    void changen(int a){n=a;}
    lista(int hossz){n=hossz;elemek=new T[n];}
    lista() : n(0), elemek(0){}
    lista &operator=(const lista& l){
        delete[] elemek;
        n=l.n;
        elemek=new T[n];
        for(int i=0;i<n;i++){
            elemek[i]=l.elemek[i];
        }
        return *this;
    }
    T& operator[](int i){return elemek[i];}
    const T& operator[](int i)const{return elemek[i];}
    ~lista(){delete[] elemek;}
    lista &operator+=(T uj){
        if(n>=1){
            lista temp(n);
            for(int i=0;i<n;i++)
                temp.elemek[i]=elemek[i];
            delete[] elemek;
            elemek=new T[n+1];
            for(int i=0;i<n;i++)
                elemek[i]=temp.elemek[i];
            elemek[n]=uj;
            n++;
        }
        else{
            elemek=new T[1];
            elemek[0]=uj;
            n=1;
        }
        return *this;
    }
};



#endif // LISTA_H_INCLUDED
