#pragma once

#include <iostream>
#include <algorithm>

template <typename T> class Allocator;

template <> class Allocator <bool> {
public:
    unsigned char *dt;
    unsigned cap, size;

    Allocator(unsigned n = 0) {
        allocate(n);
    }

    ~Allocator() {
        deallocate();
    }

    bool get_element(unsigned idx) {
        return (dt[idx / 8] & _Pow_int(2, 7 - idx % 8)) > 0;
    }

    void set_element(unsigned idx, bool value) {
        dt[idx / 8] = value ? dt[idx / 8] + _Pow_int(2, 7 - idx % 8) : get_element(idx) ? dt[idx / 8] - _Pow_int(2, 7 - idx % 8) : dt[idx / 8];
    }

    void fill_array(unsigned idx, unsigned n, bool val = false) {
        for (unsigned i = idx; i < idx + n; i++)
            set_element(i, val);
    }

    void allocate(unsigned n) {
        size = n;
        cap = (n + 7) / 8;
        dt = static_cast <unsigned char*> (calloc(cap, sizeof(unsigned char)));
    }

    void deallocate() {
        free(dt);
    }

};

template<typename T, class A = Allocator<T>>
class Array {
private:
    A *al;
public:

    class ConstIterator {
    protected:
        Array *obj;
        int idx;

        int valid_range(int n, int min_v, int max_v) const {
            if (n < min_v)
                return min_v;
            else
                if (n > max_v)
                    return max_v;

            return n;
        }
    public:
        ConstIterator(Array& object, int index = 0) : obj(&object), idx(valid_range(index, 0, obj->size())) {}

        bool operator==(const ConstIterator& other) const { return idx == other.idx; };
        bool operator!=(const ConstIterator& other) const { return !(*this == other); };
        bool operator<(const ConstIterator& other) const { return idx < other.idx; };
        bool operator<=(const ConstIterator& other) const { return *this < other && *this == other; };
        bool operator>(const ConstIterator& other) const { return other <= *this; };
        bool operator>=(const ConstIterator& other) const { return other < *this; };


        const T& operator*() const {
            return (*obj)[valid_range(idx, 0, obj->size() - 1)];
        }
    };

    class Iterator : public ConstIterator {
    public:
        Iterator(Array& object, int index = 0) : ConstIterator(object, index) {}

        Iterator operator+(int n) const {
            Iterator iter(*this);
            iter.idx = valid_range(idx + n, 0, obj->size());
            return iter;
        }

        Iterator operator-(int n) const {
            Iterator iter(*this);
            iter.idx = valid_range(idx - n, 0, obj->size());
            return iter;
        }

        Iterator& operator+=(int n) { return *this = *this + n; }
        Iterator& operator-=(int n) { return *this = *this - n; }
        Iterator& operator++() { return *this += 1; }
        Iterator operator++(int) { return ++*this - 1; }
        Iterator& operator--() { return *this -= 1; }
        Iterator operator--(int) { return --*this + 1; }
    };

    Array(unsigned size = 0) { al = new A(size); }
    Array(unsigned size, const T& val) { al = new A(size); al->fill_array(0, size, val); }
    ~Array() { delete al; }

    unsigned size() const { return al->size; };
    unsigned capacity() const { return al->cap; }

    const T& front() const { return al->get_element(0); }

    const T& back() const { return al->get_element(al->size - 1); }

    const T& operator[] (unsigned idx) const { return al->get_element(idx); }

    void operator() (unsigned idx, const T& val) { al->set_element(idx, val); }

    void clear() { delete al; al = new A; }

    bool empty() const { return al->size == 0; }

    Iterator begin() { return Iterator(*this, 0); }
    ConstIterator begin() const { return ConstIterator(*this, 0); }

    Iterator end() { return Iterator(*this, al->size); }
    ConstIterator end() const { return ConstIterator(*this, al->size); }
};