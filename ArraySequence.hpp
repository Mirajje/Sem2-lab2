#include "Sequence.hpp"
#include "DynamicArray.hpp"

template <class T>
class ArraySequence : public Sequence<T>
{
private:
    DynamicArray<T>* m_array;
    int m_count;

public:
    ArraySequence()
    {
        m_array = new DynamicArray<T>();
        m_count = 0;
    }

    ArraySequence(T* items, int count)
    {
        m_array = new DynamicArray<T>(items, count);
        m_count = count;
    }

    explicit ArraySequence(const DynamicArray<T>& other)
    {
        m_array = new DynamicArray<T>(other);
        m_count = other.getSize();
    }

    ArraySequence(const ArraySequence<T>& other)
    {
        m_array = new DynamicArray<T>(*other.m_array);
        m_count = other.m_count;
    }

    ~ArraySequence()
    {
        delete m_array;
    }

public:
    T& operator[](int index)
    {
        if (index < 0 || index >= m_count)
            throw std::runtime_error("Index out of range\n");

        return (*m_array)[index];
    }

public:
    T get(int index) const
    {
        if (index < 0 || index >= m_count)
            throw std::runtime_error("Index out of range\n");

        return m_array->get(index);
    }

    T getFirst() const
    {
        if (m_count == 0)
            throw std::runtime_error("Index out of range\n");

        return m_array->get(0);
    }

    T getLast() const
    {
        if (m_count == 0)
            throw std::runtime_error("Index out of range\n");

        return m_array->get(m_count - 1);
    }

    int getLength() const
    {
        return m_count;
    }

    void set(T item, int index)
    {
        if (index < 0 || index >= m_count)
            throw std::runtime_error("Index out of range\n");

        (*m_array)[index] = item;
    }

    Sequence<T>* getSubSequence(int startIndex, int endIndex) const
    {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= m_count)
            throw std::runtime_error("Index out of range\n");

        DynamicArray<T> temp(endIndex - startIndex + 1);
        for (int i = startIndex; i < endIndex + 1; i++)
            temp[i - startIndex] = (*m_array)[i];

        Sequence<T>* res = new ArraySequence<T>(temp);
        return res;
    }

    void insertAt(T item, int index)
    {
        if (index < 0 || index > m_count)
            throw std::runtime_error("Index out of range\n");

        if (m_count == m_array->getSize())
            m_array->resize(m_array->getSize() * 2);
        m_count += 1;

        T prev = (*m_array)[index]; T temp;
        for (int i = index + 1; i < m_count; i++)
        {
            temp = (*m_array)[i];
            (*m_array)[i] = prev;
            prev = temp;
        }
        (*m_array)[index] = item;
    }

    void append(T item)
    {
        this->insertAt(item, m_count);
    }

    void prepend(T item)
    {
        this->insertAt(item, 0);
    }

    Sequence<T>* concat(Sequence<T>* other) const
    {
        if (other == nullptr)
            throw std::runtime_error("Null pointer error\n");

        auto* resultArray = new ArraySequence<T>;
        *(resultArray->m_array) = *(m_array);
        resultArray->m_count = m_count;

        for (int i = 0; i < other->getLength(); i++)
            resultArray->append((*other)[i]);

        return resultArray;
    }

    T pop(int index)
    {
        if (index >= m_count || index < 0)
            throw std::runtime_error("Index out of range\n");

        m_count -= 1;
        return m_array->pop(index);
    }

    void print() const
    {
        m_array->print(m_count);
    }
};