#pragma once
#ifndef CLASS_DATE_H
#define CLASS_DATE_H

#include <iostream>
#include <string.h>

/*
Класс реализует хранение даты в формате: день.месяц.год с
возможностью последующей её обработки. все вычислительные
действия происходят с учетом правил вычисления високосных годов.
*/

class Date {
private:
    int _day;
    int _month;
    int _year;
public:
    Date();
    Date(int day, int month, int year);
    Date(std::string str);
    Date& operator+=(int day);
    Date& operator-=(int day);
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);
    Date operator+(int day) const;
    Date operator-(int day) const;
    int operator[](int index) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
};

    std::ostream& operator<<(std::ostream& os, const Date& other);
    std::istream& operator>>(std::istream& is, Date& other);
    Date operator+(int day, const Date& other);
    Date operator-(int day, const Date& other);
    int DateToDays(const Date& other);
    Date DaysToDate(int days);

#endif