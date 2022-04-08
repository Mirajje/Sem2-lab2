#include "LinkedList.hpp"
#include "Sequence.hpp"

template <class T>
class ListSequence : public Sequence<T>
{
private:
    LinkedList<T>* m_list;

public:
    ListSequence()
    {
        m_list = new LinkedList<T>();
    }

    ListSequence(T* items, int count)
    {
        m_list = new LinkedList<T>(items, count);
    }

    explicit ListSequence(const LinkedList<T>& other)
    {
        m_list = new LinkedList<T>(other);
    }

    ListSequence(const ListSequence<T>& other)
    {
        m_list = new LinkedList<T>(*other.m_list);
    }

    ~ListSequence()
    {
        delete m_list;
    }

public:
    T get(int index) const
    {
        return m_list->get(index);
    }

    T getFirst() const
    {
        return m_list->getFirst();
    }

    T getLast() const
    {
        return m_list->getLast();
    }

    int getLength() const
    {
        return m_list->getSize();
    }

public:
    T& operator[](int index)
    {
        return (*m_list)[index];
    }

public:
    void set(T item, int index)
    {
        (*m_list)[index] = item;
    }

    Sequence<T>* getSubSequence(int startIndex, int endIndex) const
    {
        auto* res = new ListSequence<T>(*m_list->getSubList(startIndex, endIndex));
        return res;
    }

    void insertAt(T item, int index)
    {
        m_list->insertAt(item, index);
    }

    void append(T item)
    {
        m_list->append(item);
    }

    void prepend(T item)
    {
        m_list->prepend(item);
    }

    Sequence<T>* concat(Sequence<T>* other) const
    {
        if (other == nullptr)
            throw std::runtime_error("Null pointer error\n");

        auto* resultList = new ListSequence<T>;
        *(resultList->m_list) = *(m_list);

        for (int i = 0; i < other->getLength(); i++)
            resultList->append((*other)[i]);

        return resultList;
    }

    T pop(int index)
    {
        return m_list->pop(index);
    }

    void print() const
    {
        m_list->print();
    }
};