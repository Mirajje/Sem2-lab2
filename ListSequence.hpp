#include "LinkedList.hpp"
#include "Sequence.hpp"

template <typename T>
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

    T get(int index)
    {
        return m_list->get(index);
    }

    T getFirst()
    {
        return m_list->getFirst();
    }

    T getLast()
    {
        return m_list->getLast();
    }

    int getLength()
    {
        return m_list->getSize();
    }

    T& operator[](int index)
    {
        return (*m_list)[index];
    }

    void set(T item, int index)
    {
        (*m_list)[index] = item;
    }

    Sequence<T>* getSubSequence(int startIndex, int endIndex)
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

    /*Sequence<T>* concat(Sequence<T>* other)
    {
        if (other == nullptr)
            throw std::runtime_error("Null pointer error\n");

        for (int i = 0; i < other->getLength(); i++)
        {
            m_list->append(other->get(i));
        }
        return this;
    }*/

    void print()
    {
        m_list->print();
    }
};