#define _CRT_SECURE_NO_WARNINGS
#include "class_string.h"
#include <string.h>

String::String(const char *str) {
    n = strlen(str);
    s = new char[n + 1];
    strcpy(s, str);
}

String::String(const String &str) {
    n = str.n;
    s = new char[n + 1];
    strcpy(s, str.s);
}

String::~String() {
    delete[] s;
}

char& String::operator[](unsigned index) {
    if (index < n) return s[index];
    std::cerr << "Index out of range" << std::endl;
    static char dummy;
    return dummy = '\0';
}

const char& String::operator[](unsigned index) const {
    if (index < n) return s[index];
    std::cerr << "Index out of range" << std::endl;
    return s[n];
}

String& String::operator=(const String &str) {
    if (this == &str) return *this;
    delete[] s;
    n = str.n;
    s = new char[n + 1];
    strcpy(s, str.s);
    return *this;
}

String& String::operator+=(const String &str) {
    char *t = new char[n + str.n + 1];
    strcpy(t, s);
    strcat(t, str.s);
    delete[] s;
    s = t;
    n += str.n;
    return *this;
}

String& String::operator*=(unsigned count) {
    char *t = new char[n * count + 1];
    t[0] = '\0';
    for(unsigned i = 0; i < count; i++)
        strcat(t, s);
    delete[] s;
    s = t;
    n *= count;
    return *this;
}


std::istream& operator>>(std::istream& is, String& other) {
    char buf[2048];
    is.getline(buf, sizeof buf);
    other = buf;
    return is;
}

std::ostream& operator<<(std::ostream& os, const String& other) {
    return os << other.c_str();
}

String operator+(const String &lh, const String &rh) {
    String t = lh;
    return t += rh;
}

String operator*(const String &other, unsigned count) {
    String t = other;
    return t *= count;
}