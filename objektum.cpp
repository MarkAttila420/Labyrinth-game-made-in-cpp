#include "objektum.h"
#include "map.h"
#include "memtrace.h"

////////////////////////////////////////////////////////////////////////////////////
int valaszt(int db){
    char c;
    std::cin>>c;
    int szam=c-'0';
    for(int i=0;i<db;i++){
        if(szam==i){
            return szam;
        }
    }
    return -1;
}

int koord(int x,int y,int with){
    return y*with+x;
}
////////////////////////////////////////////////////////////////////////////////////
player::player(terkep t) : objektum(0,0){
    health=100;
    mana=100;
    level=1;
    for(int i=0;t.abra[i]!='\0';i++){
        if(i%t.getw()==0&&i!=0){
            this->y++;
        }
        this->x=i%23;
        if(t.abra[i]=='@'){
            break;
        }
    }
}

player::player(std::ifstream &f,int with){
    int pos=beolvas(f);
    x=pos%with;
    y=(pos-x)/with;
    level=beolvas(f);
    health=beolvas(f);
    mana=beolvas(f);
}

char player::checkUp(String abra,int with){
    return abra[koord(player::x,player::y-1,with)];
}
char player::checkDown(String abra,int with){
    return abra[koord(player::x,player::y+1,with)];
}
char player::checkLeft(String abra,int with){
    return abra[koord(player::x-1,player::y,with)];
}
char player::checkRight(String abra,int with){
    return abra[koord(player::x+1,player::y,with)];
}

void player::move(char dir,String &abra, int with){         //dir: irany(w,s,a,d),type: koordinata tipusa(M,a,w,m,h,F)
    if(!wall::stopPlayer(dir,abra,*this,with)){
        switch(dir){
            case'w':{
                abra[koord(player::x,player::y,with)]='_';
                y--;
                abra[koord(player::x,player::y,with)]='@';
                break;
            }
            case's':{
                abra[koord(player::x,player::y,with)]='_';
                y++;
                abra[koord(player::x,player::y,with)]='@';
                break;
            }
            case'a':{
                abra[koord(player::x,player::y,with)]='_';
                x--;
                abra[koord(player::x,player::y,with)]='@';
                break;
            }
            case'd':{
                abra[koord(player::x,player::y,with)]='_';
                x++;
                abra[koord(player::x,player::y,with)]='@';
                break;
            }
        }
    }
}

int player::meetEnemy(lista<enemy> &en){
    for(int i=0;i<=en.getn();i++){
        if(this->x==en[i].getx()&&this->y==en[i].gety()&&en[i].geth()>0){
            return i;
        }
    }
    return -1;
}


void player::fight(enemy &en, lista<varazslat> &v,std::ifstream &f){
    vonal();
    std::cout<<"Fight, enemy: "<<en.getn()<<std::endl;
    int valasztas;
    while(en.geth()>0&&!this->end()){
        vonal();
        std::cout<<en;
        vonal();
        std::cout<<*this;
        vonal();
        std::cout<<"Spells: "<<std::endl;
        for(int i=0;i<this->level;i++){
            std::cout<<"["<<i<<"] "<<v[i]<<std::endl;
        }
        vonal();
        std::cout<<"Your choice: ";
        do{
            valasztas=valaszt(this->level);
        }while(valasztas==-1||v[valasztas].getmanacost()>this->mana);
        std::cout<<std::endl;
        vonal();
        v[valasztas].hit(en);
        this->mana-=v[valasztas].getmanacost();
        this->takeDamage(en.getd());
    }
    if(en.geth()<=0){
        varazslat temp(f);
        this->level++;
        v+=temp;
    }
}

void player::pickUpItem(lista<item> &items){
    for(int i=0;i<=items.getn();i++){
        if(this->x==items[i].getx()&&this->y==items[i].gety()&&items[i].getcollected()==0){
            items[i].getPickedUp();
        }
    }
}

void player::openInv(lista<item> &inv){
    int valasztas=-1;
    char c;
    int szam;
    while(valasztas!=-2){
        vonal();
        std::cout<<*this;
        vonal();
        std::cout<<"Inventory: "<<std::endl;
        for(int i=0;i<inv.getn();i++){
            if(inv[i].getcollected()==1){
                std::cout<<"["<<i<<"] ";
                std::cout<<inv[i];
            }
        }
        std::cout<<"[x] Exit inventory"<<std::endl;
        vonal();
        std::cout<<"Your choice: ";
        do{
            std::cin>>c;
            std::cout<<std::endl;
            vonal();
            if(c=='x'||c=='X'){valasztas=-2;}
            if(valasztas!=-2&&c>='0'&&c<='9'){
                szam=c-'0';
                if(szam>=inv.getn()){valasztas=-1;}
                else valasztas=szam;
            }
        }while(valasztas==-1);
        if(valasztas!=-2&&inv[valasztas].getcollected()==1){
            if(inv[valasztas].gettype()=='h'){
                this->health+=10;
                inv[valasztas].drink();
            }
            if(inv[valasztas].gettype()=='m'){
                this->mana+=10;
                inv[valasztas].drink();
            }
        }
    }
    std::cout<<std::endl;
}

player &player::operator=(player& p){
        if(this!=&p){
            x=p.x;
            y=p.y;
            health=p.health;
            mana=p.mana;
            level=p.level;
        }
        return *this;
    }
////////////////////////////////////////////////////////////////////////////////////

bool wall::stopPlayer(char dir,String abra, player p,int with){
    switch(dir){
        case'w':return player::check(abra,with,p,&player::checkUp,'#'); break;
        case'a':return player::check(abra,with,p,&player::checkLeft,'#'); break;
        case's':return player::check(abra,with,p,&player::checkDown,'#'); break;
        case'd':return player::check(abra,with,p,&player::checkRight,'#'); break;
        default:break;
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////

finish::finish(terkep t) : objektum(0,0){
    for(int i=0;t.abra[i]!='\0';i++){
        if(i%t.getw()==0&&i!=0){
            this->y++;
        }
        this->x=i%23;
        if(t.abra[i]=='F'){
            break;
        }
    }
}

bool finish::end(player p){
    if(this->x==p.getx()&&this->y==p.gety()){
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////

enemy::enemy(int a,int b,std::ifstream &f):objektum(a,b){
    String hp("");
    String dmg("");
    String temp("");
    name=temp;
    int i=0;
    char c=0;
    while(f>>c&&c!='#'){
        if(c==';'){
            i++;
        }
        else{
            switch(i){
            case 0: name+=c; break;
            case 1: hp+=c; break;
            case 2: dmg+=c; break;
            }
        }
    }
    health=atoi(hp.c_str());
    damage=atoi(dmg.c_str());
}

enemy::enemy(std::ifstream &f){     //f:a save file
    x=(beolvas(f));
    y=(beolvas(f));
    String temp("");
    name=temp;
    char c=0;
    while(f>>c&&c!=';')
        name+=c;
    damage=beolvas(f);
    health=beolvas(f);

}
////////////////////////////////////////////////////////////////////////////////////

item::item(int a,int b, char t):objektum(a,b), type(t){
    collected=0;
    String temp("");
    if(t=='h') temp+="Health potion";
    if(t=='m') temp+="Mana potion";
    name=temp;

}

item::item(std::ifstream &f){
    x=(beolvas(f));
    y=(beolvas(f));
    f>>type;
    char c=0;
    f>>c;
    collected=beolvas(f);
    String temp("");
    name=temp;
    if(type=='m')
        name+="Mana potion";
    else if(type=='h')
        name+="Health potion";
}
////////////////////////////////////////////////////////////////////////////////////

varazslat::varazslat(std::ifstream &f){
    String mc("");
    String dmg("");
    String temp("");
    name=temp;
    int i=0;
    char c=0;
    while(f>>c&&c!='#'){
        if(c==';'){
            i++;
        }
        else{
            switch(i){
            case 0: name+=c; break;
            case 1: mc+=c; break;
            case 2: dmg+=c; break;
            }
        }
    }
    manacost=atoi(mc.c_str());
    damage=atoi(dmg.c_str());
}





