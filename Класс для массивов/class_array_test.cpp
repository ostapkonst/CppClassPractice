#include "class_array.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

typedef bool(*TEST_FuncT)();

void TEST_FUNCTION(TEST_FuncT funcs[], int size) {
    cout << "TEST COUNT " << size << endl;
    for (int i = 0; i < size; i++) {
        cout << "TEST " << i + 1 << " ";
        funcs[i]() ? cout << "OK" : cout << "FAIL";
        cout << endl;
    }
    cout << "TEST IS FINISHED" << endl;
}

template<typename T>
bool CompareArrays(const Array<T> &A, const T *C, unsigned size, unsigned cap) {
#if _DEBUG
    cout << endl << "Array(" << A.size() << ", " << A.capacity() << ")" << endl;
    for (unsigned i = 0; i < A.size(); i++)
        cout << A.at(i) << " ";
    cout << endl;

    cout << "Answer(" << size << ", " << cap << ")" << endl;
    for (unsigned i = 0; i < size; i++)
        cout << C[i] << " ";
    cout << endl;
#endif

    bool result = A.size() == size && A.capacity() == cap;
    if (result == false)
        return false;

    for (unsigned i = 0; i < A.size(); i++)
        if (A.at(i) != C[i])
            return false;

    return true;
}

bool TEST_CreateArrayDefault() {
    Array<int> A;

    return A.size() == 0 && A.capacity() == 1;
}

bool TEST_CreateArraySized() {
    Array<int> A(9);
    int C[9] = {};

    return CompareArrays<int>(A, C, 9, 9);
}

bool TEST_CreateArray() {
    Array<int> A(3, 4);
    int C[3] = { 4, 4, 4 };

    return CompareArrays<int>(A, C, 3, 3);
}

bool TEST_Brackets() {
    Array<int> A(3, 2);

    A[0] = 1;
    A[2] = 3;

    return A[0] == 1 && A[1] == 2 && A[2] == 3;
}

bool TEST_At() {
    Array<int> A(3, 2);

    try {
        A.at(3) = 0;
    }
    catch (out_of_range) {
        return true;
    }

    return false;
}

bool TEST_Front() {
    Array<int> A(9, 2);

    A.front() = 16;

    return A.front() == 16 && A[0] == 16;
}

bool TEST_Back() {
    Array<int> A(9, 2);

    A.back() = 32;

    return A.back() == 32 && A[8] == 32;
}

bool TEST_Empty() {
    Array<int> A(2), B;

    return !A.empty() == B.empty();
}

bool TEST_Push_Back() {
    Array<int> A(1, 1);
    int C[2] = { 1, 2 };

    A.push_back(2);

    return CompareArrays<int>(A, C, 2, 4);
}

bool TEST_Pop_Back() {
    Array<int> A(4, 1);
    int C[3] = { 1, 1, 1 };

    A.pop_back();

    return CompareArrays<int>(A, C, 3, 4);
}

bool TEST_Assign() {
    Array<int> A, B(3, 3);
    int C[3] = { 3, 3, 3 };

    A.assign(B);

    return CompareArrays<int>(A, C, 3, 3);
}

bool TEST_Push_Pop() {
    Array<int> A(3, 3);
    int C1[5] = { 3, 3, 3, 1, 2 }, C2[3] = { 3, 3, 3 };
    bool result;

    A.push_back(1);
    A.push_back(2);

    result = CompareArrays<int>(A, C1, 5, 8);

    A.pop_back();
    A.pop_back();

    result = result && CompareArrays<int>(A, C2, 3, 4);

    A.pop_back();
    A.pop_back();
    A.pop_back();
    A.pop_back();
    A.pop_back();

    return result && A.size() == 0 && A.capacity() == 1;

}

bool TEST_Clear() {
    Array<int> A(3, 3);
    int C[3] = { 3, 3, 3 };

    A.clear();
    A.size();

    return A.empty();
}

bool TEST_IterBegin() {
    Array<int> A(3, 3);
    Array<int>::Iterator I(A, 0);

    A[0] = 5;

    return I == (A.begin()) && *I == 5;
}

bool TEST_IterEnd() {
    Array<int> A(3, 3);
    Array<int>::Iterator I(A, 2);
    Array<int>::Iterator O(A.end() - 1);

    A[2] = 6;

    return I == O-- && *I == 6 && *++O == 6;
}

bool TEST_Insert() {
    Array<int, Allocator<int>> A(3, -1);
    Array<int>::Iterator I(A, 3);
    int O[5] = { 1, 2, 3, 4, 5 };
    int C1[8] = { -1, -1, -1, 10, 10, 10, 10, 10 };

    A.insert(I, 5, 10);

    return CompareArrays<int>(A, C1, 8, 16);
}

bool TEST_Shrink() {
    Array<int> A(9);

    A.push_back(0);
    A.shrink_to_fit();

    return A.capacity() == 10;
}

bool TEST_Reserve() {
    Array<int> A(9);

    A.push_back(0);
    A.reserve(16);

    return A.capacity() == 16;
}

int main(){
    TEST_FuncT funcs[] = {
        TEST_CreateArrayDefault,
        TEST_CreateArraySized,
        TEST_CreateArray,
        TEST_Brackets,
        TEST_At,
        TEST_Front,
        TEST_Back,
        TEST_Empty,
        TEST_Push_Back,
        TEST_Pop_Back,
        TEST_Assign,
        TEST_Push_Pop,
        TEST_Clear,
        TEST_IterBegin,
        TEST_IterEnd,
        TEST_Insert,
        TEST_Shrink,
        TEST_Reserve
    };
    unsigned size = sizeof(funcs) / sizeof(TEST_FuncT);

    TEST_FUNCTION(funcs, size);

    system("PAUSE");
    return 0;
}