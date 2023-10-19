#define _CRT_SECURE_NO_WARNINGS
#include "class_string_dynamic.h"
#include <string.h>

String::Heap::Heap(const char *str) {
    l = 1;
    n = strlen(str);
    s = new char[n + 1];
    strcpy(s, str);
}

void String::Heap::assign(const String::Heap &strh) {
    if (n != strh.n) {
        delete[] s;
        n = strh.n;
        s = new char[n + 1];
    }
    strcpy(s, strh.s);
}

void String::Heap::multiply(unsigned count) {
    char *t = new char[n * count + 1];
    t[0] = '\0';
    for(unsigned i = 0; i < count; i++)
        strcat(t, s);
    delete[] s;
    s = t;
    n *= count;
}

void String::Heap::adding(const String::Heap &strh) {
    char *t = new char[n + strh.n + 1];
    strcpy(t, s);
    strcat(t, strh.s);
    delete[] s;
    s = t;
    n += strh.n;
}

void String::Heap::removed(unsigned idx, unsigned len) {
    if (idx >= n) { std::cerr << "Index out of range" << std::endl; return; }
    if (idx + len > n) {std::cerr << "Length out of range" << std::endl; len = n - len; }
    char *t = new char[n - len + 1];
    strncpy(t, s, idx);
    t[idx] = '\0';
    strcat(t, &s[idx + len]);
    delete[] s;
    s = t;
    n -= len;
}

void String::Heap::inserted(unsigned idx, const String::Heap &strh) {
    if (idx > n) { std::cerr << "Index out of range" << std::endl; return; }
    char *t = new char[n + strh.n + 1];
    strncpy(t, s, idx);
    t[idx] = '\0';
    strcat(t, strh.s);
    strcat(t, &s[idx]);
    delete[] s;
    s = t;
    n += strh.n;
}

void String::Heap::substred(unsigned idx, unsigned len) {
    if (idx >= n) { std::cerr << "Index out of range" << std::endl; return; }
    if (idx + len > n) {std::cerr << "Length out of range" << std::endl; len = n - len; }
    char *t = new char[len + 1];
    strncpy(t, &s[idx], len);
    t[len] = '\0';
    delete[] s;
    s = t;
    n = len;
}

String::Char String::operator[](unsigned idx) {
    if (idx < sh->n) return Char(*this, idx);
    std::cerr << "Index out of range" << std::endl;
    static String dummy;
    return Char(dummy = '\0', 0);
}

const char String::operator[](unsigned idx) const {
    if (idx < sh->n) return sh->s[idx];
    std::cerr << "Index out of range" << std::endl;
    return '\0';
}

String& String::operator=(const String &str) {
    if (this == &str) return *this;
    delete sh->deleter();
    sh = str.sh->linking();
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
