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

    explicit ArraySequence(int count)
    {
        m_array = new DynamicArray<T>(count);
        m_count = count;
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

    int find(const T& item) const
    {
        for (int i = 0; i < this->getLength(); i++)
            if (this->get(i) == item)
                return i;

        return -1;
    }

public:
    T& operator[](int index)
    {
        if (index < 0 || index >= m_count)
            throw std::runtime_error("Index out of range\n");

        return (*m_array)[index];
    }

    ArraySequence<T>& operator =(const Sequence<T>& other)
    {
        if (this != &other)
        {
            DynamicArray<T> result(other.getLength());
            for (int i = 0; i < other.getLength(); i++)
                result[i] = other.get(i);

            *m_array = result;
            m_count = other.getLength();
        }
        return *this;
    }

    bool operator ==(const Sequence<T>& other)
    {
        if (m_count == other.getLength())
        {
            bool flag = true;
            for (int i = 0; i < m_count; i++)
                if (this->get(i) != other.get(i))
                    flag = false;

            return flag;
        }

        return false;
    }

public:
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

public:
    Sequence<T>* map(T func(const T&))
    {
        auto* result = new ArraySequence<T>(m_count);
        for (int i = 0; i < m_count; i++)
            (*result)[i] = func((*this)[i]);

        return result;
    }

    virtual Sequence<T>* where(bool func(const T&))
    {
        int count = 0;
        for (int i = 0; i < m_count; i++)
            if (func(m_array->get(i)))
                count += 1;

        auto* result = new ArraySequence<T>(count);

        int j = 0;
        for (int i = 0; i < m_count; i++)
            if (func(m_array->get(i)))
            {
                result->set(m_array->get(i), j);
                j += 1;
            }

        return result;
    }
};