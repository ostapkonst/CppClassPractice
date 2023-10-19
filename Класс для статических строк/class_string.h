#pragma once
#ifndef CLASS_STRING_H
#define CLASS_STRING_H

#include <iostream>

class String {
private:
    char *s;
    unsigned n;
public:
    String(const char *str = "");
    String(const String &str);
    ~String();
    char& operator[](unsigned index);
    const char& operator[](unsigned index) const;
    String& operator=(const String &str);
    String& operator+=(const String &str);
    String& operator*=(unsigned count);
    unsigned length() const { return n; };
    const char* c_str() const { return s; };
};

    std::ostream& operator<<(std::ostream& os, const String& other);
    std::istream& operator>>(std::istream& is, String& other);
    String operator+(const String &lh, const String &rh);
    String operator*(const String &other, unsigned count);

    inline bool operator==(const String &lh, const String &rh) {
        return strcmp(lh.c_str(), rh.c_str()) == 0;
    }

    inline bool operator>(const String &lh, const String &rh) {
        return std::strcmp(lh.c_str(), rh.c_str()) > 0;
    }

    inline bool operator!=(const String &lh, const String &rh) {
        return !(lh == rh);
    }

    inline bool operator<=(const String &lh, const String &rh) {
        return !(lh > rh);
    }

    inline bool operator<(const String &lh, const String &rh) {
        return rh > lh;
    }

    inline bool operator>=(const String &lh, const String &rh) {
        return !(lh < rh);
    }

#endif