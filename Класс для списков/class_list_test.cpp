#include "class_list.h"
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

template< typename T > bool CompareList(List<T> &A, const T *C, int size) {
    List<T>::Iterator it(A.begin());

#if _DEBUG
    cout << endl << "LIST(" << A.size() << ")" << endl;
    for (int i = 0; i < A.size(); i++)
        cout << *(it + i) << " ";
    cout << endl;

    cout << "ARRAY(" << size << ")" << endl;
    for (int i = 0; i < size; i++)
        cout << C[i] << " ";
    cout << endl;
#endif

    bool result = A.size() == size;

    if (result == false)
        return false;

    for (int i = 0; i < A.size(); i++)
        if (*(it + i) != C[i])
            return false;

    return true;
}

bool TEST_CreateListDefault() {
    List<int> L;

    return L.size() == 0;
}

bool TEST_CreateListFromList() {
    List<int> L;
    List<int> L2(L);
    return L.size() == L2.size() && L2.size() == 0;
}

bool TEST_ListAssign() {
    List<int> L;
    List<int> L2;
    int a[] = { 0 };

    return CompareList<int>(L = L2, a, 0);
}

bool TEST_ListPushFront() {
    List<int> L;
    int a[] = { 1, 2, 3, 4 };

    L.push_front(4);
    L.push_front(3);
    L.push_front(2);
    L.push_front(1);

    return CompareList<int>(L, a, 4);
}

bool TEST_ListPushBack() {
    List<int> L;
    int a[] = { 1, 2, 3, 4 };

    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);

    return CompareList<int>(L, a, 4);
}

bool TEST_ListPopFront() {
    List<int> L;
    int a[] = { 3, 4 };

    L.push_front(4);
    L.push_front(3);
    L.push_front(2);
    L.push_front(1);

    L.pop_front();
    L.pop_front();

    return CompareList<int>(L, a, 2);
}

bool TEST_ListPopBack() {
    List<int> L;
    int a[] = { 1, 2 };

    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);

    L.pop_back();
    L.pop_back();

    return CompareList<int>(L, a, 2);
}

bool TEST_ListSize() {
    List<int> L;
    int sz = L.size();

    L.push_back(1);
    sz += L.size();
    L.push_back(2);
    sz += L.size();

    return sz == 0 + 1 + 2;
}

bool TEST_ListEmpty() {
    List<int> L;
    bool res = false;

    L.push_back(1);
    L.push_back(2);

    res = res && L.empty();

    L.pop_front();
    L.pop_front();

    return L.empty() != res;
}

bool TEST_CreateListFromFillList() {
    List<int> L;
    int a[] = { 1, 2, 3, 4 };

    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);

    List<int> L2(L);
    *L.begin() = 10;

    return CompareList<int>(L2, a, 4);
}

bool TEST_ListAssignFromFillList() {
    List<int> L;
    List<int> L2;
    int a[] = { 1, 2, 3, 4 };

    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);

    L2 = L;
    *L.begin() = 10;

    return CompareList<int>(L2, a, 4);
}

bool TEST_ListClear() {
    List<int> L;

    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);

    L.clear();

    return L.empty() && L.size() == 0;
}

bool TEST_ListIterator() {
    List<int> L;

    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);

    List<int>::Iterator it2(L.begin());
    List<int>::Iterator it3(L.end());

    *it2 = -1;

    return *it2 == -1
        && *it3 == 4
        && *(it3 - 1) == 3
        && *(--it3) == 3
        && *L.begin() == -1
        && *(it3--) == 3
        && *(it3 -= 2) == -1
        && *(it3 + 1) == 2;
}

bool TEST_ListConstIterator() {
    List<int> L;

    L.push_back(2);
    L.push_back(1);

    List<int>::ConstIterator it2(L.cbegin());
    List<int>::ConstIterator it3(L.cbegin());
    it3 = L.cend();

    return it2 < it3 && *it3 < *it2;
}

bool TEST_ListInsert() {
    List<int> L;
    int a[] = { 0, 1, 2, 3, 4, 5 };

    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(5);

    List<int>::Iterator it2(L.begin());
    L.insert(it2, 0);
    L.insert(L.end(), 4);

    return CompareList<int>(L, a, 6);
}

bool TEST_ListErase() {
    List<int> L;
    int a[] = { 2, 3, 4, 5, 7, 8, 9 };

    for (int i = 1; i <= 10; i++) L.push_back(i);

    L.erase(L.begin() + 5);
    L.erase(L.end());
    L.erase(L.begin());

    return CompareList<int>(L, a, 7);
}

int main(){
    TEST_FuncT funcs[] = {
        TEST_CreateListDefault,
        TEST_CreateListFromList,
        TEST_ListAssign,
        TEST_ListPushFront,
        TEST_ListPushBack,
        TEST_ListPopFront,
        TEST_ListPopBack,
        TEST_ListSize,
        TEST_ListEmpty,
        TEST_CreateListFromFillList,
        TEST_ListAssignFromFillList,
        TEST_ListClear,
        TEST_ListIterator,
        TEST_ListConstIterator,
        TEST_ListInsert,
        TEST_ListErase
    };

    TEST_FUNCTION(funcs, sizeof(funcs) / sizeof(TEST_FuncT));

    system("PAUSE");

    return 0;
}