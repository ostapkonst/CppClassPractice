#pragma once

#include <assert.h>

template <class T> class List {

    struct ListItem {
        ListItem *Next, *Previous;
        T Data;
        ListItem(const T& init)
            : Data(init) {}
    };

    struct ListHeader {
        int Size;
        ListItem *pFront, *pTail;
        ListHeader()
            : Size(0), pFront(0), pTail(0) {}
    } *m_header;

    void Delete() {
        assert(m_header);
        ListItem *p = m_header->pFront;

        while (p != 0) {
            ListItem *p2 = p;
            p = p->Next;
            delete p2;
        }

        delete m_header;
    }

    ListHeader* Copy() const {
        assert(m_header);
        ListHeader *m_h = new ListHeader;

        for (ListItem* p = m_header->pFront; p != 0; p = p->Next) {
            ListItem* item = new ListItem(p->Data);
            item->Next = 0;
            item->Previous = m_h->pTail;

            if (m_h->pTail != 0) m_h->pTail->Next = item;
            m_h->pTail = item;

            if (m_h->pFront == 0) m_h->pFront = item;
        }

        m_h->Size = m_header->Size;

        return m_h;
    }

public:

    class ConstIterator {
    protected:
        ListItem *list;
    public:
        friend List;

        explicit ConstIterator(ListItem &object) : list(&object) {}

        bool operator == (const ConstIterator& other) const { return list == other.list; }
        bool operator != (const ConstIterator& other) const { return !(*this == other); }
        bool operator < (const ConstIterator& other) const { return list < other.list; }
        bool operator <= (const ConstIterator& other) const { return *this < other && *this == other; }
        bool operator > (const ConstIterator& other) const { return !(*this <= other); }
        bool operator >= (const ConstIterator& other) const { return !(*this < other); }

        const T& operator * () const { return list->Data; }
    };

    struct Iterator : public ConstIterator {
        explicit Iterator(ListItem &object) : ConstIterator(object) {}

        Iterator operator + (int n) const {
            Iterator iter(*this);

            while (iter.list->Next != 0 && n-- > 0) {
                iter.list = iter.list->Next;
            }

            return iter;
        }

        Iterator operator - (int n) const {
            Iterator iter(*this);

            while (iter.list->Previous != 0 && n-- > 0) {
                iter.list = iter.list->Previous;
            }

            return iter;
        }

        Iterator& operator += (int n) { return *this = *this + n; }
        Iterator& operator -= (int n) { return *this = *this - n; }
        Iterator& operator ++ () { return *this += 1; }
        Iterator operator ++ (int) { return ++*this - 1; }
        Iterator& operator -- () { return *this -= 1; }
        Iterator operator -- (int) { return --*this + 1; }

        T& operator * () { return list->Data; }
    };



    List()
        : m_header(new ListHeader) {}

    List(const List& list) {
        m_header = list.Copy();
    }

    ~List() {
        Delete();
    }

    List& operator = (const List &list) {
        Delete();
        m_header = list.Copy();
        return *this;
    }

    bool empty() const {
        return m_header->pFront == 0;
    }

    int size() const {
        return m_header->Size;
    }

    void push_front(const T& item) {
        ListItem* li = new ListItem(item);

        li->Next = m_header->pFront;
        li->Previous = 0;
        if (m_header->pFront != 0) m_header->pFront->Previous = li;
        m_header->pFront = li;
        if (m_header->pTail == 0) m_header->pTail = li;

        m_header->Size++;
    }

    void pop_front() {
        assert(m_header->pFront != 0 && m_header->pTail != 0 && m_header->Size > 0);
        ListItem* front = m_header->pFront;

        m_header->pFront = front->Next;
        if (m_header->pTail == front)
            m_header->pTail = 0;
        else
            m_header->pFront->Previous = 0;

        delete front;

        m_header->Size--;
    }

    void push_back(const T& item) {
        ListItem* li = new ListItem(item);

        li->Next = 0;
        li->Previous = m_header->pTail;
        if (m_header->pTail != 0) m_header->pTail->Next = li;
        m_header->pTail = li;
        if (m_header->pFront == 0) m_header->pFront = li;

        m_header->Size++;
    }

    void pop_back() {
        assert(m_header->pFront != 0 && m_header->pTail != 0 && m_header->Size > 0);
        ListItem* back = m_header->pTail;

        m_header->pTail = back->Previous;
        if (m_header->pFront == back)
            m_header->pFront = 0;
        else
            m_header->pTail->Next = 0;

        delete back;

        m_header->Size--;
    }

    void clear() {
        Delete();
        m_header = new ListHeader;
    }

    Iterator begin() {
        return Iterator(*m_header->pFront);
    }

    ConstIterator begin() const {
        return ConstIterator(*m_header->pFront);
    }

    ConstIterator cbegin() {
        return ConstIterator(*m_header->pFront);
    }

    Iterator end() {
        return Iterator(*m_header->pTail);
    }

    ConstIterator end() const {
        return ConstIterator(*m_header->pTail);
    }

    ConstIterator cend() {
        return ConstIterator(*m_header->pTail);
    }

    Iterator insert(Iterator pos, const T& val) {
        ListItem *it = new ListItem(val);
        ListItem *p = pos.list;

        it->Next = p;
        if (p != 0) {
            it->Previous = p->Previous;
            if (p->Previous != 0) {
                p->Previous->Next = it;
                p->Previous = it;
            }
            else
                m_header->pFront = it;
        }
        else {
            it->Previous = 0;
            m_header->pFront = it;
            m_header->pTail = it;
        }

        m_header->Size++;

        return Iterator(*it);
    }

    Iterator erase(Iterator pos) {
        ListItem *p = pos.list;
        assert(p != 0 && m_header->pFront != 0 && m_header->pTail != 0 && m_header->Size > 0);
        Iterator res(*p->Next);

        if (p == m_header->pTail)
            m_header->pTail = p->Previous;
        else
            p->Next->Previous = p->Previous;

        if (p == m_header->pFront)
            m_header->pFront = p->Next;
        else
            p->Previous->Next = p->Next;

        delete p;

        m_header->Size--;

        return res;
    }
};