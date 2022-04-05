#include <iostream>
#include <algorithm>

template <typename T>
class DynamicArray{
private:
    T* m_Data = nullptr;
    int m_Size = 0;

public:
    DynamicArray() = default;

    explicit DynamicArray(int size)
    {
        m_Size = size;
        m_Data = new T[m_Size]();
    }

    DynamicArray(T* items, int count)
    {
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
        printf("Destructor has been called\n");
    }

    T& operator[](int i)
    {
        if (i < 0 || i >= m_Size)
            throw std::out_of_range("Index out of range\n");
        return m_Data[i];
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
        if (this != &other)
        {
            delete[] m_Data;
            m_Size = other.m_Size;
            m_Data = other.m_Data;

            other.m_Data = nullptr;
        }
        return *this;
    }

    T* begin(){ return m_Data; }
    T* end(){ return &m_Data[m_Size]; }

    int getSize(){ return m_Size; }
    void setSize(int n){ m_Size = n; }

    void print()
    {
        for (int i = 0; i < m_Size; i++)
            std::cout << m_Data[i] << ' ';
        std::cout << '\n';
    }
};

int main()
{
    int items[5] = {5, 4, 3, 2, 1};
    DynamicArray<int> array2;
    DynamicArray<int> array3;

    array2 = DynamicArray<int>(items, 5);
    std::sort(array2.begin(), array2.end());

    array3 = array2;
    try
    {
        array3[16] += 2;
    }
    catch (const std::out_of_range& a)
    {
        std::cout << a.what();
    }

    array2.print();
    array3.print();
}