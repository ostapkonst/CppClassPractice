#include "class_string_dynamic.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>

using namespace std;

#define DEBUG_MODE 0

typedef bool (*TEST_FuncT)();

bool CompareDateArguments(const String &S, const char *C) {
#if DEBUG_MODE
    cout << C << '[' << strlen(C) << ']' << " = "
         << S << '[' << S.length() << ']' << endl;
#endif
    return strcmp(S.c_str(), C) == 0 && strlen(C) == S.length() ? true : false;
}

bool TEST_CreateStringDefault() {
    String S;
    return CompareDateArguments(S, "");
}

bool TEST_CreateString() {
    String S("Hi Anton");
    return CompareDateArguments(S, "Hi Anton");
}

bool TEST_CreateStringFromString() {
    String S1("Hi Anton"), S2(S1);
    return CompareDateArguments(S2, "Hi Anton");
}

bool TEST_CreatePointerString() {
    String S1("Hi Anton"), *S2 = new String(S1);
    bool r = CompareDateArguments(*S2, "Hi Anton");
    delete S2;
    return r;
}

bool TEST_CreateAndDestroyString() {
    String *S1 = new String("Hi Anton"),
           *S2 = new String("Bye Anton");
    *S2 = *S1;
    delete S1;
    bool r = CompareDateArguments(*S2, "Hi Anton");
    delete S2;
    return r;
}

bool TEST_Assign() {
    String S1("Hi Anton"), S2("Bye Anton");
    S2 = S2;
    S2 = S1;
    S2 = S2 = S2;
    return CompareDateArguments(S2, "Hi Anton");
}

bool TEST_PlusAssing() {
    String S1("Hi"), S2("Anto");
    S1 += "";
    S1 += " ";
    S1 += S2 += "n";
    return CompareDateArguments(S1, "Hi Anton");
}

bool TEST_Plus() {
    String S1("Hi"), S2("Anto");
    S1 = S1 + " ";
    S1 = S1 + S2 + "n";
    return CompareDateArguments(S1, "Hi Anton");
}

bool TEST_MultiplyAssing() {
    String S1("Hi "), S2("Anton");
    S1 *= 1;
    S1 *= 3;
    S1 += S2;
    S2 *= 0;
    S1 += S2;
    return CompareDateArguments(S1, "Hi Hi Hi Anton");
}

bool TEST_Multiply() {
    String S1("Hi "), S2("Anton");
    S1 = S1 * 3;
    S1 = S1 + S2;
    return CompareDateArguments(S1, "Hi Hi Hi Anton");
}

bool TEST_Compare() {
    String S1("Zhuplev Anton"),
           S2("Ivanov Anton"),
           S3("Zhuplev Anton"),
           S4("Zhuplev Anton Sergeevich");
    return strcmp(S1.c_str(), S2.c_str()) > 0 && S1 > S2 && S1 >= S2 && S2 < S1 &&
           strcmp(S1.c_str(), S3.c_str()) == 0 && S1 == S3 && S3 == S1 && !(S1 != S3) &&
           strcmp(S1.c_str(), S4.c_str()) < 0 && S1 < S4 && S1 <= S4 && S4 > S1;
}

bool TEST_Brackets() {
    const String S1("Anton");
    String S2("Antot");
    S2[4] = 'n';
    return S1[0] == 'A' && S2[1] == 'n' &&  S1[2] == 't' && S2[4] == 'n';
}

bool TEST_GetLength() {
    const String S1("Anton");
    return S1.length() == 5;
}

bool TEST_GetChar() {
    const String S1("Anton");
    return strcmp(S1.c_str(), "Anton") == 0;
}

bool TEST_Remove() {
    String S1("Hii "), S2("Anton");
    S1.remove(2, 1);
    return CompareDateArguments(S1 + S2, "Hi Anton");
}

bool TEST_Insert() {
    String S1("Hi "), S2("Anton");
    S1.insert(3, S2);
    S1.insert(3, "OK ");
    return CompareDateArguments(S1, "Hi OK Anton");
}

bool TEST_Substr() {
    const String S1("OK Hi Anton Yes");
    return CompareDateArguments(S1.substr(3, 8), "Hi Anton");
}

bool TEST_SubstrAssign() {
    String S1("NO IIIon");
    S1.substr(0, 2) = "Hi";
    S1.substr(3, 3) = "Ant";
    return CompareDateArguments(S1, "Hi Anton");
}

int main(){
    TEST_FuncT funcs[] = {
        TEST_CreateStringDefault,
        TEST_CreateString,
        TEST_CreateStringFromString,
        TEST_CreatePointerString,
        TEST_CreateAndDestroyString,
        TEST_Assign,
        TEST_PlusAssing,
        TEST_Plus,
        TEST_MultiplyAssing,
        TEST_Multiply,
        TEST_Compare,
        TEST_Brackets,
        TEST_GetLength,
        TEST_GetChar,
        TEST_Remove,
        TEST_Insert,
        TEST_Substr,
        TEST_SubstrAssign
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