#include "class_bool_array.h"
#include <iostream>

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
bool CompareArrays(const Array<T> &A, const T *C, unsigned size) {
#if _DEBUG
    cout << endl << "Array(" << A.size() << ", " << A.capacity() << ")" << endl;
    for (unsigned i = 0; i < A.size(); i++)
        cout << A[i] << " ";
    cout << endl;

    cout << "Answer(" << size << ")" << endl;
    for (unsigned i = 0; i < size; i++)
        cout << C[i] << " ";
    cout << endl;
#endif

    bool result = A.size() == size;
    if (result == false)
        return false;

    for (unsigned i = 0; i < A.size(); i++)
        if (A[i] != C[i])
            return false;

    return true;
}

bool TEST_1() {
    Array<bool> A;

    return A.size() == 0 && A.capacity() == 0;
}

bool TEST_2() {
    Array<bool> A(9);
    bool C[9] = {};

    return CompareArrays<bool>(A, C, 9);
}

bool TEST_3() {
    Array<bool> A1(8);
    Array<bool> A2(9);
    Array<bool> A3(16);
    Array<bool> A4(17);

    return A1.capacity() == 1 &&
        A2.capacity() == 2 &&
        A3.capacity() == 2 &&
        A4.capacity() == 3;
}

bool TEST_4() {
    Array<bool> A1(8);
    Array<bool> A2(9);
    Array<bool> A3(16);
    Array<bool> A4(17);

    return A1.size() == 8 &&
        A2.size() == 9 &&
        A3.size() == 16 &&
        A4.size() == 17;
}

bool TEST_5() {
    Array<bool> A1(8);

    A1(4, true);
    A1(5, true);

    return A1[3] == false &&
        A1[4] == true &&
        A1[5] == true &&
        A1[6] == false;
}

bool TEST_6() {
    Array<bool> A1(8);

    A1(4, false);
    A1(5, true);

    return
        A1[3] == false &&
        A1[4] == false &&
        A1[5] == true &&
        A1[6] == false;
}

bool TEST_7() {
    Array<bool> A1(8);

    A1(4, true);
    A1(5, false);

    return
        A1[3] == false &&
        A1[4] == true &&
        A1[5] == false &&
        A1[6] == false;
}

bool TEST_8() {
    Array<bool> A1(8);

    A1(4, false);
    A1(5, false);

    return
        A1[3] == false &&
        A1[4] == false &&
        A1[5] == false &&
        A1[6] == false;
}

bool TEST_9() {
    Array<bool> A1(17);

    A1(14, true);
    A1(15, true);

    return A1[13] == false &&
        A1[14] == true &&
        A1[15] == true &&
        A1[16] == false;
}

bool TEST_10() {
    Array<bool> A1(17);

    A1(14, false);
    A1(15, true);

    return
        A1[13] == false &&
        A1[14] == false &&
        A1[15] == true &&
        A1[16] == false;
}

bool TEST_11() {
    Array<bool> A1(17);

    A1(14, true);
    A1(15, false);

    return
        A1[13] == false &&
        A1[14] == true &&
        A1[15] == false &&
        A1[16] == false;
}

bool TEST_12() {
    Array<bool> A1(17);

    A1(14, false);
    A1(15, false);

    return
        A1[13] == false &&
        A1[14] == false &&
        A1[15] == false &&
        A1[16] == false;
}

int main() {
    TEST_FuncT funcs[] = {
        TEST_1,
        TEST_2,
        TEST_3,
        TEST_4,
        TEST_5,
        TEST_6,
        TEST_7,
        TEST_8,
        TEST_9,
        TEST_10,
        TEST_11,
        TEST_12
    };
    unsigned size = sizeof(funcs) / sizeof(TEST_FuncT);

    TEST_FUNCTION(funcs, size);

    system("PAUSE");
    return 0;
}