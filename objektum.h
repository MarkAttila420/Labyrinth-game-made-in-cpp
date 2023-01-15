#ifndef OBJEKTUM_H_INCLUDED
#define OBJEKTUM_H_INCLUDED

#include <iostream>
#include <fstream>
#include "lista.h"
#include "map.h"
#include "labstring.h"
#include "memtrace.h"

class objektum{
protected:
    int x;
    int y;
public:
    objektum(){x=0;y=0;}
    objektum(int a, int b):x(a),y(b){}
    int getx(){return x;}
    int gety(){return y;}
    virtual ~objektum(){}
};

////////////////////////////////////////////////////////
class enemy : public objektum{
    String name;
    int health;
    int damage;
public:
    int geth(){return health;}
    int getd(){return damage;}
    String getn(){return name;}
    enemy(std::ifstream &f);
    enemy():objektum(){}
    enemy(int a,int b, std::ifstream &f);
    void takeDamage(int minusz){health-=minusz;}

    friend std::ostream& operator<<(std::ostream& os,const enemy &e){
        os<<e.name<<"'s Helath: "<<e.health<<std::endl<<e.name<<"'s Damage: "<<e.damage<<std::endl;
        return os;
    }
};

////////////////////////////////////////////////////////
class item : public objektum{
    String name;
    char type;          //m: mana potion, h:health potion
    int collected;      //0:nincs felszedve, 1:fel van szedve, de nincs megiiva, 2:meg van iva
public:
    item():objektum(){}
    item(int a,int b, char t);
    item(std::ifstream &f);
    int getcollected(){return collected;}
    String getname(){return name;}
    char gettype(){return type;}
    void getPickedUp(){collected=1;}
    void drink(){collected=2;}

    friend std::ostream& operator<<(std::ostream& os,const item &i){
        os<<i.name<<": increases ";
        if(i.type=='h')
            os<<"health ";
        if(i.type=='m')
            os<<"mana ";
        os<<"by 10"<<std::endl;
        return os;
    }
};

////////////////////////////////////////////////////////
class varazslat{
    String name;
    int manacost;
    int damage;
public:
    varazslat(){}
    varazslat(std::ifstream &f);
    int getmanacost(){return manacost;}
    void hit(enemy &en){en.takeDamage(damage);}
    friend std::ostream& operator<<(std::ostream& os,const varazslat &v){
        os<<v.name<<", manacost: "<<v.manacost<<", damage: "<<v.damage;
        return os;
    }
};

class player : public objektum{
    int health;
    int mana;
    int level;
public:
    int geth(){return health;}
    int getm(){return mana;}
    int getl(){return level;}
    player(std::ifstream &f, int with);
    player():objektum(){health=100;mana=100;level=1;}
    player(terkep t);
    player(int a,int b):objektum(a,b){health=100;mana=100;level=1;}
    void takeDamage(int amount){health-=amount;}
    void pickUpItem(lista<item> &potions);
    int meetEnemy(lista<enemy> &en);
    void fight(enemy &en,lista<varazslat> &v,std::ifstream &f);
    void openInv(lista<item> &inv);
    bool end(){if(health<=0) return true; else return false;}
    template<typename T>
    static bool check(String abra, int with,T &instance, char(T:: *fn)(String abra, int with),char c){
        if((instance.*fn)(abra,with)==c)
            return true;
        return false;
    }
    void move(char dir, String &abra,int with);         //dir: irany(u,d,l,r),type: koordinata tipusa(M,a,w,m,h,F)
    char checkUp(String abra,int with);
    char checkDown(String abra,int with);
    char checkLeft(String abra,int with);
    char checkRight(String abra,int with);
    player &operator=(player& p);

    friend std::ostream& operator<<(std::ostream& os,const player &p){
        os<<"Level: "<<p.level<<std::endl<<"Health: "<<p.health<<std::endl<<"Mana: "<<p.mana<<std::endl;
        return os;
    }
};
////////////////////////////////////////////////////////
class finish : public objektum{
public:
    finish():objektum(){}
    finish(terkep t);
    finish(int a,int b):objektum(a,b){}
    bool end(player p);
};

////////////////////////////////////////////////////////
class wall : public objektum{
public:
    wall():objektum(){}
    wall(int a,int b):objektum(a,b){}
    static bool stopPlayer(char dir,String abra, player p,int with);
};
#endif // OBJEKTUM_H_INCLUDED
