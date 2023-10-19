#include "class_string.h"
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

bool TEST_CreateAndDestroy() {
    String *S1 = new String("Hi Anton"),
           *S2 = new String("Bye Anton");
    *S2 = *S1;
    delete S1;
    bool r = CompareDateArguments(*S2, "Hi Anton");
    delete S2;
    return r;
}

bool TEST_AssignString() {
    String S1("Hi Anton"), S2("Bye Anton");
    S2 = S2;
    S2 = S1;
    S2 = S2 = S2;
    return CompareDateArguments(S2, "Hi Anton");
}

bool TEST_PlusAssingString() {
    String S1("Hi"), S2("Anto");
    S1 += "";
    S1 += " ";
    S1 += S2 += "n";
    return CompareDateArguments(S1, "Hi Anton");
}

bool TEST_PlusString() {
    String S1("Hi"), S2("Anto");
    S1 = S1 + " ";
    S1 = S1 + S2 + "n";
    return CompareDateArguments(S1, "Hi Anton");
}

bool TEST_MultiplyAssingString() {
    String S1("Hi "), S2("Anton");
    S1 *= 1;
    S1 *= 3;
    S1 += S2;
    S2 *= 0;
    S1 += S2;
    return CompareDateArguments(S1, "Hi Hi Hi Anton");
}

bool TEST_MultiplyString() {
    String S1("Hi "), S2("Anton");
    S1 = S1 * 3;
    S1 = S1 + S2;
    return CompareDateArguments(S1, "Hi Hi Hi Anton");
}

bool TEST_CompareStrings() {
    String S1("Zhuplev Anton"),
           S2("Ivanov Anton"),
           S3("Zhuplev Anton"),
           S4("Zhuplev Anton Sergeevich");
    return strcmp(S1.c_str(), S2.c_str()) > 0 && S1 > S2 && S1 >= S2 && S2 < S1 &&
           strcmp(S1.c_str(), S3.c_str()) == 0 && S1 == S3 && S3 == S1 && !(S1 != S3) &&
           strcmp(S1.c_str(), S4.c_str()) < 0 && S1 < S4 && S1 <= S4 && S4 > S1;
}

bool TEST_BracketsString() {
    const String S1("Anton");
    String S2("Anton");
    return S1[0] == 'A' && S2[1] == 'n' &&  S1[2] == 't';
}

bool TEST_GetLengthString() {
    const String S1("Anton");
    return S1.length() == 5;
}

bool TEST_GetCharString() {
    const String S1("Anton");
    return strcmp(S1.c_str(), "Anton") == 0;
}

int main(){
    TEST_FuncT funcs[] = {
        TEST_CreateStringDefault,
        TEST_CreateString,
        TEST_CreateStringFromString,
        TEST_CreatePointerString,
        TEST_CreateAndDestroy,
        TEST_AssignString,
        TEST_PlusAssingString,
        TEST_PlusString,
        TEST_MultiplyAssingString,
        TEST_MultiplyString,
        TEST_CompareStrings,
        TEST_BracketsString,
        TEST_GetLengthString,
        TEST_GetCharString
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