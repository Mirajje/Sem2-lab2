#include "Sequence.hpp"
#include "DynamicArray.hpp"

template <class T>
class ArraySequence : public Sequence<T>
{
private:
    DynamicArray<T>* m_Array;
    int m_Count;

public:
    ArraySequence()
    {
        m_Array = new DynamicArray<T>();
        m_Count = 0;
    }

    explicit ArraySequence(int count)
    {
        m_Array = new DynamicArray<T>(count);
        m_Count = count;
    }

    ArraySequence(T* items, int count)
    {
        m_Array = new DynamicArray<T>(items, count);
        m_Count = count;
    }

    explicit ArraySequence(const DynamicArray<T>& other)
    {
        m_Array = new DynamicArray<T>(other);
        m_Count = other.getSize();
    }

    ArraySequence(const ArraySequence<T>& other)
    {
        m_Array = new DynamicArray<T>(*other.m_Array);
        m_Count = other.m_Count;
    }

    explicit ArraySequence(const Sequence<T>& other)
    {
        m_Array = new DynamicArray<T>(other.getLength());
        for (int i = 0; i < other.getLength(); i++)
            m_Array->set(i, other.get(i));
        m_Count = other.getLength();
    }

    ~ArraySequence()
    {
        delete m_Array;
    }

public:
    T get(int index) const
    {
        if (index < 0 || index >= m_Count)
            throw std::runtime_error("Index out of range\n");

        return m_Array->get(index);
    }

    T getFirst() const
    {
        if (m_Count == 0)
            throw std::runtime_error("Index out of range\n");

        return m_Array->get(0);
    }

    T getLast() const
    {
        if (m_Count == 0)
            throw std::runtime_error("Index out of range\n");

        return m_Array->get(m_Count - 1);
    }

    int getLength() const
    {
        return m_Count;
    }

    int find(const T& item) const
    {
        for (int i = 0; i < this->getLength(); i++)
            if (this->get(i) == item)
                return i;

        return -1;
    }

    void clear()
    {
        delete this;
    }

public:
    T& operator[](int index)
    {
        if (index < 0 || index >= m_Count)
            throw std::runtime_error("Index out of range\n");

        return (*m_Array)[index];
    }

    ArraySequence<T>& operator =(const Sequence<T>& other)
    {
        if (this != &other)
        {
            DynamicArray<T> result(other.getLength());
            for (int i = 0; i < other.getLength(); i++)
                result[i] = other.get(i);

            *m_Array = result;
            m_Count = other.getLength();
        }
        return *this;
    }

    bool operator ==(const Sequence<T>& other) const
    {
        if (m_Count == other.getLength())
        {
            bool flag = true;
            for (int i = 0; i < m_Count; i++)
                if (this->get(i) != other.get(i))
                    flag = false;

            return flag;
        }

        return false;
    }

public:
    void set(T item, int index)
    {
        if (index < 0 || index >= m_Count)
            throw std::runtime_error("Index out of range\n");

        (*m_Array)[index] = item;
    }

    Sequence<T>* getSubSequence(int startIndex, int endIndex) const
    {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= m_Count)
            throw std::runtime_error("Index out of range\n");

        DynamicArray<T> temp(endIndex - startIndex + 1);
        for (int i = startIndex; i < endIndex + 1; i++)
            temp[i - startIndex] = (*m_Array)[i];

        Sequence<T>* res = new ArraySequence<T>(temp);
        return res;
    }

    void insertAt(T item, int index)
    {
        if (index < 0 || index > m_Count)
            throw std::runtime_error("Index out of range\n");

        if (m_Count == m_Array->getSize())
        {
            if (m_Count != 0)
                m_Array->resize(m_Array->getSize() * 2);
            else
                m_Array->resize(m_Array->getSize() + 1);
        }
        m_Count += 1;

        T prev = (*m_Array)[index]; T temp;
        for (int i = index + 1; i < m_Count; i++)
        {
            temp = (*m_Array)[i];
            (*m_Array)[i] = prev;
            prev = temp;
        }
        (*m_Array)[index] = item;
    }

    void append(T item)
    {
        this->insertAt(item, m_Count);
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
        *(resultArray->m_Array) = *(m_Array);
        resultArray->m_Count = m_Count;

        for (int i = 0; i < other->getLength(); i++)
            resultArray->append((*other)[i]);

        return resultArray;
    }

    T pop(int index)
    {
        if (index >= m_Count || index < 0)
            throw std::runtime_error("Index out of range\n");

        m_Count -= 1;
        return m_Array->pop(index);
    }

    void print() const
    {
        m_Array->print(m_Count);
    }

public:
    Sequence<T>* map(T func(const T&)) const
    {
        auto* result = new ArraySequence<T>(m_Count);
        for (int i = 0; i < m_Count; i++)
            (*result)[i] = func(m_Array->get(i));

        return result;
    }

    Sequence<T>* where(bool func(const T&)) const
    {
        int count = 0;
        for (int i = 0; i < m_Count; i++)
            if (func(m_Array->get(i)))
                count += 1;

        auto* result = new ArraySequence<T>(count);

        int j = 0;
        for (int i = 0; i < m_Count; i++)
            if (func(m_Array->get(i)))
            {
                result->set(m_Array->get(i), j);
                j += 1;
            }

        return result;
    }

    T reduce(T func(const T&, const T&), T startValue) const
    {
        T result = startValue;
        for (int i = 0; i < m_Count; i++)
        {
            result = func(m_Array->get(i), result);
        }
        return result;
    }
};