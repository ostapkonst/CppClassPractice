#pragma once
#ifndef CLASS_STRING_H
#define CLASS_STRING_H

#include <iostream>

class String {
private:
    class Heap {
    private:
        unsigned l;
    public:
        char *s;
        unsigned n;
        Heap(const char *str);
        ~Heap() { delete[] s; };
        Heap* copying() { if (l == 1) return this; l--; return new Heap(s); };
        Heap* linking() { if (l == UINT_MAX) return new Heap(s); l++; return this; };
        void* deleter() { return l == 0 || --l == 0 ? this : NULL; }; // Условие l == 0 - необязательно
        void assign(const Heap &strh);
        void adding(const Heap &strh);
        void multiply(unsigned count);
        void removed(unsigned idx, unsigned len);
        void inserted(unsigned idx, const Heap &strh);
        void substred(unsigned idx, unsigned len);
    } *sh;
    class Char {
    private:
        String &s;
        unsigned i;
        Char& operator&();
    public:
        Char(String &str, unsigned idx): s(str), i(idx) {};
        operator char() const { return s.sh->s[i]; };
        void operator=(char c) { s.sh = s.sh->copying(); s.sh->s[i] = c; };
    };
    class SubString {
    private:
        String &s;
        unsigned i, l;
        String& operator&();
    public:
        SubString(String &str, unsigned idx, unsigned len): s(str), i(idx), l(len) {};
        operator String() const { Heap h = Heap(s.sh->s); h.substred(i, l); return h.s; };
        void operator=(const String &str) { s.sh = s.sh->copying(); s.sh->removed(i, l); s.sh->inserted(i, *str.sh); };
    };
public:
    String(const char *str = "") { sh = new Heap(str); };
    String(const String &str) { sh = str.sh->linking(); };
    String(char c) { char str[2] = {c,}; sh = new Heap(str); }
    ~String() { delete sh->deleter(); };
    Char operator[](unsigned idx);
    const char operator[](unsigned idx) const; // const char& operator[](unsigned idx) const, был заменен т.к. указывал бы на кучу
    String& operator=(const String &str);
    String& operator=(const char *str_c) { sh = sh->copying(); sh->assign(str_c); return *this; };
    String& operator+=(const String &str) { sh = sh->copying(); sh->adding(*str.sh); return *this; };
    String& operator*=(unsigned count) { sh = sh->copying(); sh->multiply(count); return *this; };
    String& remove(unsigned idx, unsigned len) { sh = sh->copying(); sh->removed(idx, len); return *this; };
    String& insert(unsigned idx, const String &str) { sh = sh->copying(); sh->inserted(idx, *str.sh); return *this; };
    SubString substr(unsigned idx, unsigned len) { return SubString(*this, idx, len); };
    String substr(unsigned idx, unsigned len) const { Heap h = Heap(sh->s); h.substred(idx, len); return h.s; };
    unsigned length() const { return sh->n; };
    const char* c_str() const { return sh->s; };
};

    std::ostream& operator<<(std::ostream& os, const String& other);
    std::istream& operator>>(std::istream& is, String& other);
    inline String operator+(const String &lh, const String &rh) { String t = lh.c_str(); return t += rh; }
    inline String operator*(const String &other, unsigned count) { String t = other.c_str(); return t *= count; }

    inline bool operator==(const String &lh, const String &rh) {
        return strcmp(lh.c_str(), rh.c_str()) == 0;
    }

    inline bool operator>(const String &lh, const String &rh) {
        return std::strcmp(lh.c_str(), rh.c_str()) > 0;
    }

    inline bool operator!=(const String &lh, const String &rh) { return !(lh == rh); }

    inline bool operator<=(const String &lh, const String &rh) { return !(lh > rh); }

    inline bool operator<(const String &lh, const String &rh) { return rh > lh; }

    inline bool operator>=(const String &lh, const String &rh) { return !(lh < rh); }

#endif