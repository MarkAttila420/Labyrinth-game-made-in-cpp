#ifndef LABSTRING_H_INCLUDED
#define LABSTRING_H_INCLUDED
#include <iostream>
#include "memtrace.h"
class String {
    char *pData;
    size_t len;
public:
	size_t size() const { return len; }
    String() :pData(0), len(0) {}
    const char* c_str() const { if (pData) return pData; else return "";}
    String(char ch);
    String(const char *p);
    String(const String& s1);
    ~String() { delete[] pData; }
    void printDbg(const char *txt = "") const {
        std::cout << txt << "[" << len << "], "
                  << (pData ? pData : "(NULL)") << std::endl;
    }
    String& operator=(const String& rhs_s);

String& operator+=(const String& rhs_s) {
    *this = *this + rhs_s;
    return *this;
}
    String operator+(const String& rhs_s) const ;
    char& operator[](unsigned int idx);
    const char& operator[](unsigned int idx) const;

    void erase() { *this = ""; }
};
std::ostream& operator<<(std::ostream& os, const String& s0);
std::istream& operator>>(std::istream& is, String& s0);
inline String operator+(char ch, const String& str) { return String(ch) + str; }

#endif // LABSTRING_H_INCLUDED
