#ifndef HPP_ARRAY_SEQUENCE
#define HPP_ARRAY_SEQUENCE

#include "Sequence.h"
#include "DynamicArray.hpp"
#include "Errors.h"

template <class T>
class ArraySequence : public Sequence<T>
{
private:
    DynamicArray<T>* m_Array;

public:
    ArraySequence();
    explicit ArraySequence(int count);
    ArraySequence(T* items, int count);
    explicit ArraySequence(const DynamicArray<T>& other);
    ArraySequence(const ArraySequence<T>& other);
    explicit ArraySequence(const Sequence<T>& other);
    ~ArraySequence();

public:
    T get(int index) const;
    T getFirst() const;
    T getLast() const;
    int getLength() const;
    int find(const T& item) const;
    void clear();

public:
    T& operator[](int index);
    ArraySequence<T>& operator =(const Sequence<T>& other);
    bool operator ==(const Sequence<T>& other) const;

public:
    void set(T item, int index);
    Sequence<T>* getSubSequence(int startIndex, int endIndex) const;
    void insertAt(T item, int index);
    void append(T item);
    void prepend(T item);
    Sequence<T>* concat(Sequence<T>* other) const;
    T pop(int index);
    void print() const;

public:
    Sequence<T>* map(T func(const T&)) const;
    Sequence<T>* where(bool func(const T&)) const;
    T reduce(T func(const T&, const T&), T startValue) const;

};

template <class T>
ArraySequence<T>::ArraySequence()
{
    m_Array = new DynamicArray<T>();
}

template <class T>
ArraySequence<T>::ArraySequence(int count)
{
    m_Array = new DynamicArray<T>(count);
}

template <class T>
ArraySequence<T>::ArraySequence(T* items, int count)
{
    m_Array = new DynamicArray<T>(items, count);
}

template <class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& other)
{
    m_Array = new DynamicArray<T>(other);
}

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other)
{
    m_Array = new DynamicArray<T>(*other.m_Array);
}

template <class T>
ArraySequence<T>::ArraySequence(const Sequence<T>& other)
{
    m_Array = new DynamicArray<T>(other.getLength());
    for (int i = 0; i < other.getLength(); i++)
        m_Array->set(i, other.get(i));
}

template <class T>
ArraySequence<T>::~ArraySequence()
{
    delete m_Array;
}

template <class T>
T ArraySequence<T>::get(int index) const
{
    if (m_Array->getSize() == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= m_Array->getSize())
        throw Errors(Errors::INDEX_OUR_OF_RANGE_ERROR);

    return m_Array->get(index);
}

template <class T>
T ArraySequence<T>::getFirst() const
{
    if (m_Array->getSize() == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    return m_Array->get(0);
}

template <class T>
T ArraySequence<T>::getLast() const
{
    if (m_Array->getSize() == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    return m_Array->get(m_Array->getSize() - 1);
}

template <class T>
int ArraySequence<T>::getLength() const
{
    return m_Array->getSize();
}

template <class T>
int ArraySequence<T>::find(const T& item) const
{
    for (int i = 0; i < m_Array->getSize(); i++)
        if (this->get(i) == item)
            return i;

    return -1;
}

template <class T>
void ArraySequence<T>::clear()
{
    delete this;
}

template <class T>
T& ArraySequence<T>::operator[](int index)
{
    if (m_Array->getSize() == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= m_Array->getSize())
        throw Errors(Errors::INDEX_OUR_OF_RANGE_ERROR);

    return (*m_Array)[index];
}

template <class T>
ArraySequence<T>& ArraySequence<T>::operator =(const Sequence<T>& other)
{
    if (this != &other)
    {
        DynamicArray<T> result(other.getLength());
        for (int i = 0; i < other.getLength(); i++)
            result[i] = other.get(i);

        *m_Array = result;
    }
    return *this;
}

template <class T>
bool ArraySequence<T>::operator ==(const Sequence<T>& other) const
{
    if (m_Array->getSize() == other.getLength())
    {
        bool flag = true;
        for (int i = 0; i < m_Array->getSize(); i++)
            if (this->get(i) != other.get(i))
                flag = false;

        return flag;
    }

    return false;
}

template <class T>
void ArraySequence<T>::set(T item, int index)
{
    if (m_Array->getSize() == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= m_Array->getSize())
        throw Errors(Errors::INDEX_OUR_OF_RANGE_ERROR);

    (*m_Array)[index] = item;
}

template <class T>
Sequence<T>* ArraySequence<T>::getSubSequence(int startIndex, int endIndex) const
{
    if (m_Array->getSize() == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (startIndex > endIndex || startIndex < 0 || endIndex >= m_Array->getSize())
        throw Errors(Errors::INDEX_OUR_OF_RANGE_ERROR);

    DynamicArray<T> temp(endIndex - startIndex + 1);
    for (int i = startIndex; i < endIndex + 1; i++)
        temp[i - startIndex] = (*m_Array)[i];

    Sequence<T>* res = new ArraySequence<T>(temp);
    return res;
}

template <class T>
void ArraySequence<T>::insertAt(T item, int index)
{
    if (index < 0 || index > m_Array->getSize())
        throw Errors(Errors::INDEX_OUR_OF_RANGE_ERROR);

    m_Array->resize(m_Array->getSize() + 1);

    T prev = (*m_Array)[index]; T temp;
    for (int i = index + 1; i < m_Array->getSize(); i++)
    {
        temp = (*m_Array)[i];
        (*m_Array)[i] = prev;
        prev = temp;
    }
    (*m_Array)[index] = item;
}

template <class T>
void ArraySequence<T>::append(T item)
{
    this->insertAt(item, m_Array->getSize());
}

template <class T>
void ArraySequence<T>::prepend(T item)
{
    this->insertAt(item, 0);
}

template <class T>
Sequence<T>* ArraySequence<T>::concat(Sequence<T>* other) const
{
    if (other == nullptr)
        throw Errors(Errors::NULL_POINTER_ERROR);

    auto* resultArray = new ArraySequence<T>;
    *(resultArray->m_Array) = *(m_Array);

    for (int i = 0; i < other->getLength(); i++)
        resultArray->append((*other)[i]);

    return resultArray;
}

template <class T>
T ArraySequence<T>::pop(int index)
{
    if (m_Array->getSize() == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index >= m_Array->getSize() || index < 0)
        throw Errors(Errors::INDEX_OUR_OF_RANGE_ERROR);

    return m_Array->pop(index);
}

template <class T>
void ArraySequence<T>::print() const
{
    m_Array->print();
}

template <class T>
Sequence<T>* ArraySequence<T>::map(T func(const T&)) const
{
    auto* result = new ArraySequence<T>(m_Array->getSize());
    for (int i = 0; i < m_Array->getSize(); i++)
        (*result)[i] = func(m_Array->get(i));

    return result;
}

template <class T>
Sequence<T>* ArraySequence<T>::where(bool func(const T&)) const
{
    int count = 0;
    for (int i = 0; i < m_Array->getSize(); i++)
        if (func(m_Array->get(i)))
            count += 1;

    auto* result = new ArraySequence<T>(count);

    int j = 0;
    for (int i = 0; i < m_Array->getSize(); i++)
        if (func(m_Array->get(i)))
        {
            result->set(m_Array->get(i), j);
            j += 1;
        }

    return result;
}

template <class T>
T ArraySequence<T>::reduce(T func(const T&, const T&), T startValue) const
{
    T result = startValue;
    for (int i = 0; i < m_Array->getSize(); i++)
    {
        result = func(m_Array->get(i), result);
    }
    return result;
}

#endif