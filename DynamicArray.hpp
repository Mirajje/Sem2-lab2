#include <iostream>

template <class T>
class DynamicArray{
private:
    T* m_Data = nullptr;
    int m_Size = 0;

public:
    DynamicArray() = default;

    explicit DynamicArray(int size)
    {
        if (size < 0)
            throw std::runtime_error("Negative size error\n");
        m_Size = size;
        m_Data = new T[m_Size]();
    }

    DynamicArray(T* items, int count)
    {
        if (items == nullptr)
            throw std::runtime_error("Null pointer error\n");

        if (count < 0)
            throw std::runtime_error("Negative size error\n");

        m_Size = count;
        m_Data = new T[m_Size];
        memcpy(m_Data, items, m_Size * sizeof(T));
    }

    DynamicArray(const DynamicArray<T>& dynamicArray)
    {
        m_Size = dynamicArray.m_Size;
        m_Data = new T[m_Size];
        memcpy(m_Data, dynamicArray.m_Data, m_Size * sizeof(T));
    }

    ~DynamicArray()
    {
        delete[] m_Data;
        printf("Array destructor has been called\n");
    }

public:
    T& operator[](int index)
    {
        if (index < 0 || index >= m_Size)
            throw std::runtime_error("Index out of range\n");
        return m_Data[index];
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& other)
    {
        if (this != &other)
        {
            delete[] m_Data;
            m_Size = other.m_Size;
            m_Data = new T[m_Size];
            memcpy(m_Data, other.m_Data, sizeof(T) * m_Size);
        }
        return *this;
    }

    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept
    {
        delete[] m_Data;
        m_Size = other.m_Size;
        m_Data = other.m_Data;

        other.m_Data = nullptr;
        return *this;
    }

public:
    const T& get(int index) const
    {
        if (index < 0 || index >= m_Size)
            throw std::runtime_error("Index out of range\n");
        return m_Data[index];
    }

    void set(int index, const T& value)
    {
        if (index < 0 || index >= m_Size)
            throw std::runtime_error("Index out of range\n");
        m_Data[index] = value;
    }

    int getSize() const { return m_Size; }

    void resize(int new_Size)
    {
        if (new_Size < 0)
            throw std::runtime_error("Negative size error\n");
        T* new_Data = new T[new_Size]();
        memcpy(new_Data, m_Data, sizeof(T) * std::min(new_Size, m_Size));
        delete[] m_Data;
        m_Data = new_Data;
        m_Size = new_Size;
    }

    T* begin(){ return m_Data; }
    T* end(){ return &m_Data[m_Size]; }

    T pop(int index)
    {
        if (index >= m_Size || index < 0)
            throw std::runtime_error("Index out of range\n");

        T ans = m_Data[index];

        DynamicArray<T> result(m_Size - 1);

        for (int i = 0; i < m_Size - 1; i++)
            if (i < index)
                result[i] = m_Data[i];
            else
                result[i] = m_Data[i + 1];

        *this = result;
        return ans;
    }

    void print(int count) const
    {
        for (int i = 0; i < count; i++)
            std::cout << m_Data[i] << ' ';
        std::cout << '\n';
    }

    void print() const
    {
        for (int i = 0; i < m_Size; i++)
            std::cout << m_Data[i] << ' ';
        std::cout << '\n';
    }
};