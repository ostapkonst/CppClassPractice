#include "class_date.h"
#include <iostream>

using namespace std;

#define DEBUG_MODE 0

typedef bool (*TEST_FuncT)();

bool CompareDateArguments(Date D, int d, int m, int y) {
#if DEBUG_MODE
    cout << D << " = " << d << '.' << m << '.' << y << endl;
#endif
    return D[1] == d && D[2] == m && D[3] == y;
}

bool TEST_CreateDateDefault() {
    Date D;
    return  CompareDateArguments(D, 1, 1, 1900);
}

bool TEST_CreateDate() {
    Date D(29, 2, 2012);
    return  CompareDateArguments(D, 29, 2, 2012);
}

bool TEST_CreateDateString() {
    Date D("29.12.2010");
    return  CompareDateArguments(D, 29, 12, 2010);
}

bool TEST_DatePlus() {
    Date D("29.12.2010");
    Date L = D + 3;
    D = D + 3;
    return  CompareDateArguments(D + 3, 4, 1, 2011);
}

bool TEST_DateMinus() {
    Date D("29.12.2010");
    Date L = D - 3;
    D = D - 3;
    return  CompareDateArguments(D - 3, 23, 12, 2010);
}

bool TEST_PlusDate() {
    Date D("29.12.2010");
    Date L = 3 + D;
    D = 3 + D;
    return  CompareDateArguments(3 + D, 4, 1, 2011);
}

bool TEST_MinusDate() {
    Date D("29.12.2010");
    Date L = 3 - D;
    D = 3 - D;
    return  CompareDateArguments(3 - D, 23, 12, 2010);
}

bool TEST_DatePlusPlus() {
    Date D("31.12.2010");
    Date L = D++;
    D = D++; /* значение не изменится */
    D++;
    return  CompareDateArguments(D++, 2, 1, 2011);
}

bool TEST_PlusPlusDate() {
    Date D("31.12.2010");
    Date L = ++D;
    D = ++D;
    return  CompareDateArguments(++D, 3, 1, 2011);
}

bool TEST_DateMinusMinus() {
    Date D("31.12.2010");
    Date L = D--;
    D = D--; /* значение не изменится */
    D--;
    return  CompareDateArguments(D--, 29, 12, 2010);
}

bool TEST_MinusMinusDate() {
    Date D("31.12.2010");
    Date L = --D;
    D = --D;
    return  CompareDateArguments(--D, 28, 12, 2010);
}

bool TEST_DatePlusEqually() {
    Date D("31.12.2010");
    D += 1;
    D += 2;
    return  CompareDateArguments(D += 1, 4, 1, 2011);
}

bool TEST_DateMinusEqually() {
    Date D("31.12.2010");
    D -= 1;
    D -= 2;
    return  CompareDateArguments(D -= 1, 27, 12, 2010);
}

bool TEST_DateEqually() {
    Date D("31.12.2010");
    Date L("31.12.2010");
    Date H("30.12.2010");
    return D == L && D != H;
}

bool TEST_DateBrackets() {
    Date D("31.12.2010");
    return D[1] == 31 && D[2] == 12 && D[3] == 2010;
}

bool TEST_DateDays() {
    Date D1("1.1.1");
    Date D2("1.1.2");
    Date D3("1.1.3");
    Date D4("1.1.4"); //високосный год
    Date D5("1.1.5");

    return  DateToDays(D1) == (365 * 0 + 1) &&
            DateToDays(D2) == (365 * 1 + 1) &&
            DateToDays(D3) == (365 * 2 + 1) &&
            DateToDays(D4) == (365 * 3 + 1) &&
            DateToDays(D5) == (365 * 4 + 1 + 1);
}

bool TEST_DaysDate() {
    Date D1("1.1.1");
    Date D2("1.1.2");
    Date D3("1.1.3");
    Date D4("1.1.4"); //високосный год
    Date D5("1.1.5");

    return  DaysToDate(DateToDays(D1)) == D1 &&
            DaysToDate(DateToDays(D2)) == D2 &&
            DaysToDate(DateToDays(D3)) == D3 &&
            DaysToDate(DateToDays(D4)) == D4 &&
            DaysToDate(DateToDays(D5)) == D5;
}

bool TEST_DateArithmetic() {
    Date D1("1.1.1");
    Date D2("1.1.2008");
    Date D3("29.2.2008");
    Date D4("28.2.2007");

    return  CompareDateArguments(D1 + 365, 1, 1, 2) &&
            CompareDateArguments(D2 + 366, 1, 1, 2009) &&
            CompareDateArguments(D3 + 366, 1, 3, 2009) &&
            CompareDateArguments(D4 + 366, 29, 2, 2008);
}

int main(){
    TEST_FuncT funcs[] = {
        TEST_CreateDateDefault,
        TEST_CreateDate,
        TEST_CreateDateString,
        TEST_DatePlus,
        TEST_DateMinus,
        TEST_PlusDate,
        TEST_MinusDate,
        TEST_DatePlusPlus,
        TEST_PlusPlusDate,
        TEST_DateMinusMinus,
        TEST_MinusMinusDate,
        TEST_DatePlusEqually,
        TEST_DateMinusEqually,
        TEST_DateEqually,
        TEST_DateBrackets,
        TEST_DateDays,
        TEST_DaysDate,
        TEST_DateArithmetic
    };
    unsigned int i, size = sizeof(funcs) / sizeof(TEST_FuncT);

    cout << "TEST COUNT " << size << endl;
    for (i = 0; i < size; i++) {
        cout << "TEST " << i + 1 << " ";
        funcs[i]() ? cout << "OK" : cout << "FAIL";
        cout << endl;
    }
    cout << "TEST IS FINISHED" << endl;

    system("PAUSE");
    return 0;
}