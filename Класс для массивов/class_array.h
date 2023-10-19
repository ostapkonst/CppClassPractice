#pragma once

#include <algorithm>

template<typename T>
class Allocator {
protected:
    static const unsigned initial_value = 1;
    static const unsigned factor_value = 2;
public:
    T *dt;
    unsigned cap, size;

    Allocator(unsigned n = 0) { allocate(n); }

    ~Allocator() { deallocate(); }

    void assign(const Allocator &other) {
        size = other.size;
        cap = other.cap;
        dt = static_cast<T*>(realloc(dt, sizeof(T)* cap));
        memcpy(dt, other.dt, sizeof(T)* cap);
    }

    void fill_array(unsigned idx, unsigned n, const T &val = T()) {
        for (unsigned i = idx; i < idx + n; i++)
            dt[i] = val;
    }

    void allocate(unsigned n) {
        size = n;
        cap = std::max(n, initial_value);
        dt = static_cast<T*>(malloc(sizeof(T)* cap));
        for (unsigned i = 0; i < cap; i++)
            new (dt + i) T();

    }

    void reallocate_add(unsigned idx, unsigned n) {
        if ((size += n) >= cap) {
            cap = size * factor_value;
            dt = static_cast<T*>(realloc(dt, sizeof(T)* cap));
            for (unsigned i = size; i < cap; i++)
                new (dt + i) T();
        }

        memmove(dt + idx + n, dt + idx, sizeof(T)* (size - idx - n));
    }

    void reallocate_del(unsigned idx, unsigned n) {
        if (size < 1) return;

        memmove(dt + idx, dt + idx + n, sizeof(T)* (size - idx - n));

        if ((size -= n) < cap / factor_value && cap / factor_value >= initial_value) {
            cap /= factor_value;
            for (unsigned i = cap * factor_value; i > cap; i--)
                dt[i - 1].~T();
            dt = static_cast<T*>(realloc(dt, sizeof(T)* cap));
        }
    }

    void deallocate() {
        for (unsigned i = cap; i > 0; i--)
            dt[i - 1].~T();

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
        friend Array;

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
    Array(unsigned size, const T &val) { al = new A(size); al->fill_array(0, size, val); }
    ~Array() { delete al; }

    unsigned size() const { return al->size; };
    unsigned capacity() const { return al->cap; }

    T* data() { return al->dt; }
    const T* data() const { return al->dt; }

    T& front() { return al->dt[0]; }
    const T& front() const { return al->dt[0]; }

    T& back() { return al->dt[al->size - 1]; }
    const T& back() const { return al->dt[al->size - 1]; }

    T& operator[] (unsigned idx) { return al->dt[idx]; }
    const T& operator[] (unsigned idx) const { return al->dt[idx]; }

    void clear() { delete al; al = new A; }

    bool empty() const { return al->size == 0; }

    void assign(const Array& other) {
        al->assign(*other.al);
    }

    T& at(unsigned idx) {
        if (idx < al->size)
            return al->dt[idx];
        else
            throw out_of_range("array: idx out of range");
    }

    const T& at(unsigned idx) const {
        if (idx < al->size)
            return al->dt[idx];
        else
            throw out_of_range("const array: idx out of range");
    }

    void shrink_to_fit() {
        if (al->cap <= al->size) return;

        al->cap = al->size;
        al->dt = static_cast<T*>(realloc(al->dt, sizeof(T)* al->cap));
    }

    void reserve(unsigned n) {
        if (n < al->size) return;

        al->cap = n;
        al->dt = static_cast<T*>(realloc(al->dt, sizeof(T)* al->cap));
    }

    void push_back(const T& val) {
        al->reallocate_add(al->size, 1);
        al->dt[al->size - 1] = val;
    }

    void pop_back() {
        al->reallocate_del(al->size - 1, 1);
    }

    void insert(ConstIterator position, unsigned n, const T& val) {
        al->reallocate_add(position.idx, n);
        al->fill_array(position.idx, n, val);
    }

    Iterator begin() { return Iterator(*this, 0); }
    ConstIterator begin() const { return ConstIterator(*this, 0); }

    Iterator end() { return Iterator(*this, al->size); }
    ConstIterator end() const { return ConstIterator(*this, al->size); }
};