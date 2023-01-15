#include <iostream>
#include "map.h"
#include "objektum.h"
#include "lista.h"
#include "memtrace.h"

using namespace std;
//#define Teszt


void helyek(lista<item> &tomb,terkep t){
    int j=0;
    for(int i=0;t.abra[i]!='\0';i++){
        if(i%t.getw()==0&&i!=0)
            j++;
        if(t.abra[i]=='m'){
            item temp(i%t.getw(),j,'m');
            tomb+=temp;
        }
        if(t.abra[i]=='h'){
            item temp(i%t.getw(),j,'h');
            tomb+=temp;
        }
    }
}

void helyek(lista<enemy> &tomb,terkep t){
    ifstream f;
    f.open("enemys.txt",ios::in);
    int x=0;
    for(int i=0;t.abra[i]!='\0';i++){
        if(i%t.getw()==0&&i!=0)
            x++;
        if(t.abra[i]=='M'){
            enemy temp(i%t.getw(),x,f);
            tomb+=temp;
        }
    }
    f.close();
}

void mentes(terkep t, player p, lista<enemy> &en, lista <item> &items){
    fstream file;
    file.open("save.txt",ios::out);
    file<<t.geth()<<"x"<<t.getw()<<";"<<t.abra<<";"<<p.gety()*t.getw()+p.getx()<<";"<<p.getl()<<";"<<p.geth()<<";"<<p.getm()<<";"<<items.getn();
    for(int i=0;i<items.getn();i++){
        file<<";"<<items[i].getx()<<";"<<items[i].gety()<<";"<<items[i].gettype()<<";"<<items[i].getcollected();
    }
    file<<";"<<en.getn();
    for(int i=0;i<en.getn();i++){
        file<<";"<<en[i].getx()<<";"<<en[i].gety()<<";"<<en[i].getn()<<";"<<en[i].getd();
        if(en[i].geth()<=0)
            file<<";0";
        else
            file<<";"<<en[i].geth();
    }
    file.close();
}

void mentesteszt(terkep t, player p, lista<enemy> &en, lista <item> &items){
    mentes(t,p,en,items);
}

int main(){
    ifstream g;
    g.open("save.txt",ios::in);
    terkep t;
    if(g.is_open()&&g.peek()!=ifstream::traits_type::eof()){
        terkep temp(g);
        t=temp;
    }
    if(t.letezik()){

        player plyr(t);
        finish f(t);

        lista<enemy> en;
        helyek(en,t);

        lista<item> i;
        helyek(i,t);

        lista<varazslat> v;

        ifstream file;
        file.open("spells.txt",ios::in);

        if(g.is_open()&&g.peek()!=ifstream::traits_type::eof()){
            player tempp(g,t.getw());
            plyr=tempp;
            for(int i=1;i<plyr.getl();i++){
                varazslat tempv(file);
                v+=tempv;
            }
            lista<item> tempi;
            int itemdb=beolvas(g);
            for(int j=0;j<itemdb;j++){
                item uj(g);
                tempi+=uj;
            }
            i=tempi;

            lista<enemy> tempe;
            int enemydb=beolvas(g);
            for(int j=0;j<enemydb;j++){
                enemy uj(g);
                tempe+=uj;
            }
            en=tempe;

        }
        varazslat alap(file);
        v+=alap;
        char mov;
        cout<<t;
        cout<<plyr;
        while(cin>>mov&&!f.end(plyr)&&!plyr.end()){

        plyr.move(mov,t.abra,t.getw());
        vonal();
        if(mov=='i'||mov=='I'){
            plyr.openInv(i);
        }
        cout<<t;
        cout<<plyr;
        if(plyr.meetEnemy(en)!=-1){
            plyr.fight(en[plyr.meetEnemy(en)],v,file);
            cout<<t;
            cout<<plyr;
        }
        plyr.pickUpItem(i);

        }

        if(f.end(plyr)){
            cout<<t;
            cout<<plyr;
            vonal();
            cout<<"Congratulations, you won!";
            ofstream s;
            s.open("save.txt",ios::out);
            s.close();
        }
        else if(plyr.end()){
            cout<<t;
            cout<<plyr;
            vonal();
            cout<<"You are dead!";
            ofstream s;
            s.open("save.txt",ios::out);
            s.close();
        }
        else
            mentes(t,plyr,en,i);
        file.close();
        g.close();

        #ifdef Teszt
        mentesteszt(t,plyr,en,i);
        #endif

        return 0;
    }
}
