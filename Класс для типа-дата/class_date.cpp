#define _CRT_SECURE_NO_WARNINGS
#include "class_date.h"
#include <math.h>

static const int days[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
static const int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static int sum_month(int month, bool leap) {
    return leap && month > 2 ? days[month - 1] + 1 : days[month - 1];
}

static int giv_month(int day, bool leap) {
    leap && day >= 60 ? day-- : day;
    for (int i = 0; i < 12; i++)
        if (days[i] >= day) return i;

    return 12;
}

static bool is_leap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

static int day_month(int month, bool leap) {
    return leap && month == 2 ? 29 : day[month - 1];
}

Date::Date()
: _day(1), _month(1), _year(1900)
{}

Date::Date(int day, int month, int year)
{
    if (month < 1 || month > 12)
        throw std::invalid_argument("Date settings are incorrect: Nuber months exceeded");
    if (year < 1 || year >= INT_MAX)
        throw std::invalid_argument("Date settings are incorrect: Nuber years exceeded");
    if (day_month(month, is_leap(year)) < day)
        throw std::invalid_argument("Date settings are incorrect: Nuber days exceeded");

    _day = day;
    _month = month;
    _year = year;
}

Date::Date(std::string str) {
    int day, month, year;

    if (!sscanf(str.c_str(), "%d.%d.%d", &day, &month, &year))
        throw std::invalid_argument("Date settings are incorrect");

    *this = Date(day, month, year);
}

int Date::operator[](int index) const {
    switch (index) {
        case 1: return _day;
        case 2: return _month;
        case 3: return _year;
        default: throw std::invalid_argument("Date settings are incorrect: operator[]");
    }
}

Date& Date::operator+=(int day) {
    return *this = *this + day;
}

Date& Date::operator-=(int day) {
    return *this = *this - day;
}

Date& Date::operator++() {
    return *this += 1;
}

Date Date::operator++(int) {
    return ++*this - 1;
}

Date& Date::operator--() {
    return *this -= 1;
}

Date Date::operator--(int) {
    return --*this + 1;
}

Date Date::operator+(int day) const {
    return DaysToDate(DateToDays(*this) + day);
}

Date Date::operator-(int day) const {
    return *this + -day;
}

Date operator+(int day, const Date& other) {
    return other + day;
}

Date operator-(int day, const Date& other) {
    return other - day;
}

std::ostream& operator<<(std::ostream& os, const Date& other) {
    os << other[1] << '.' << other[2] << '.' << other[3];
    return os;
}

std::istream& operator>>(std::istream& is, Date& other) {
    int d, m, y;
    is >> d >> m >> y;
    other = Date(d, m, y);
    return is;
}

bool Date::operator==(const Date& other) const {
    return _day == other._day && _month == other._month && _year == other._year;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

int DateToDays(const Date& other) {
    return  (other[3] - 1) * 365 + (other[3] - 1) / 4 - (other[3] - 1) / 100 + (other[3] - 1) / 400 +
            sum_month(other[2], is_leap(other[3])) +
            other[1];
}

Date DaysToDate(int days){
    int c_year = 1;
    int c_day = days;
    for (; is_leap(c_year) ? c_day > 366 : c_day > 365
         ; is_leap(c_year++) ? c_day -= 366 : c_day -= 365);
    bool leap = is_leap(c_year);
    int c_month = giv_month(c_day, leap);
    c_day -= sum_month(c_month, leap);

    return Date(c_day, c_month, c_year);
}