#include "LinkedList.hpp"
#include "Sequence.hpp"

template <class T>
class ListSequence : public Sequence<T>
{
private:
    LinkedList<T>* m_List;

public:
    ListSequence()
    {
        m_List = new LinkedList<T>();
    }

    explicit ListSequence(int count)
    {
        m_List = new LinkedList<T>(count);
    }

    ListSequence(T* items, int count)
    {
        m_List = new LinkedList<T>(items, count);
    }

    explicit ListSequence(const LinkedList<T>& other)
    {
        m_List = new LinkedList<T>(other);
    }

    ListSequence(const ListSequence<T>& other)
    {
        m_List = new LinkedList<T>(*other.m_List);
    }

    explicit ListSequence(const Sequence<T>& other)
    {
        m_List = new LinkedList<T>;
        for (int i = 0; i < other.getLength(); i++)
            m_List->append(other.get(i));
    }

    ~ListSequence()
    {
        delete m_List;
    }

public:
    T get(int index) const
    {
        return m_List->get(index);
    }

    T getFirst() const
    {
        return m_List->getFirst();
    }

    T getLast() const
    {
        return m_List->getLast();
    }

    int getLength() const
    {
        return m_List->getSize();
    }

    int find(const T& item) const
    {
        return m_List->find(item);
    }

    void clear()
    {
        delete this;
    }

public:
    T& operator[](int index)
    {
        return (*m_List)[index];
    }

    ListSequence<T>& operator =(const Sequence<T>& other)
    {
        if (this != &other)
        {
            delete m_List;

            m_List = new LinkedList<T>;
            for (int i = 0; i < other.getLength(); i++)
                m_List->append(other.get(i));
        }
        return *this;
    }

    bool operator ==(const Sequence<T>& other) const
    {
        if (m_List->getSize() == other.getLength())
        {
            bool flag = true;
            for (int i = 0; i < m_List->getSize(); i++)
                if (this->get(i) != other.get(i))
                    flag = false;

            return flag;
        }

        return false;
    }

public:
    void set(T item, int index)
    {
        (*m_List)[index] = item;
    }

    Sequence<T>* getSubSequence(int startIndex, int endIndex) const
    {
        auto* res = new ListSequence<T>(*m_List->getSubList(startIndex, endIndex));
        return res;
    }

    void insertAt(T item, int index)
    {
        m_List->insertAt(item, index);
    }

    void append(T item)
    {
        m_List->append(item);
    }

    void prepend(T item)
    {
        m_List->prepend(item);
    }

    Sequence<T>* concat(Sequence<T>* other) const
    {
        if (other == nullptr)
            throw std::runtime_error("Null pointer error\n");

        auto* resultList = new ListSequence<T>;
        *(resultList->m_List) = *(m_List);

        for (int i = 0; i < other->getLength(); i++)
            resultList->append((*other)[i]);

        return resultList;
    }

    T pop(int index)
    {
        return m_List->pop(index);
    }

    void print() const
    {
        m_List->print();
    }

public:
    Sequence<T>* map(T func(const T&)) const
    {
        return new ListSequence<T>(*(m_List->map(func)));
    }

    Sequence<T>* where(bool func(const T&)) const
    {
        return new ListSequence<T>(*(m_List->where(func)));
    }

    T reduce(T func(const T&, const T&), T startValue) const
    {
        return m_List->reduce(func, startValue);
    }
};