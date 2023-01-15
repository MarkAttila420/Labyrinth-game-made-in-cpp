#include "map.h"
#include "memtrace.h"
using namespace std;
void vonal(){
    cout<<"+";
    for(int i=1;i<=98;i++){
        cout<<"-";
    }
    cout<<"+"<<endl;
}
int beolvas(ifstream &f, char c){
    char kar=0;
    String szam("");
    while(f>>kar&&kar!=c){
        szam+=kar;
    }
    return atoi(szam.c_str());

}


terkep::terkep(){
    char c=0;
    if(letezik()){
        ifstream f;
        f.open("map.txt",ios::in);
        with=beolvas(f,'x');
        height=beolvas(f);
        String temp("");
        abra=temp;
        while(f>>c){
            abra+=c;
        }
        abra+='\0';
        f.close();
    }
}

terkep::terkep(ifstream &f){
    char c=0;
    with=beolvas(f,'x');
    height=beolvas(f);
    String temp("");
    abra=temp;
    while(f>>c&&c!=';'){
        abra+=c;
    }
    abra+='\0';
}

bool terkep::letezik(){
    ifstream f;
    f.open("map.txt",ios::in);
    if(!f.is_open())
        return false;
    char c;
    while(f>>c&&c!=';')
    f>>c;
    while(f>>c){
        if(c=='#'||c=='@'||c=='F'||c=='h'||c=='m'||c=='M'||c=='_')
            return false;
    }
    return true;
}

ostream& operator<<(ostream& os, const terkep& t){
    vonal();
    for(int i=0;t.abra[i]!='\0';i++){
        if(i%t.with==0&&i!=0)
            os<<endl;
        switch(t.abra[i]){
            case '_':os<<' ';
                break;
            case 'h':
            case 'm':os<<'$';
                break;
            default:os<<t.abra[i];
                break;
        }
    }
    os<<endl;
    vonal();
    return os;
}

terkep& terkep::operator=(const terkep &t){
    if (this != &t) {
        abra=t.abra;
        with=t.with;
        height=t.with;
    }
    return *this;
}
