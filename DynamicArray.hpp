#include <iostream>

template <class T>
class DynamicArray{
private:
    T* m_Data = nullptr;
    int m_Size = 0;

public:
    DynamicArray();
    explicit DynamicArray(int size);
    DynamicArray(T* items, int count);
    DynamicArray(const DynamicArray<T>& dynamicArray);
    ~DynamicArray();

public:
    T& operator[](int index);
    DynamicArray<T>& operator=(const DynamicArray<T>& other);
    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept;

public:
    const T& get(int index) const;
    int getSize() const;
    void set(int index, const T& value);
    void resize(int new_Size);
    T* begin();
    T* end();
    T pop(int index);
    void print(int count) const;
    void print() const;

};

template <class T>
DynamicArray<T>::DynamicArray() = default;

template <class T>
DynamicArray<T>::DynamicArray(int size)
{
    if (size < 0)
        throw std::runtime_error("Negative size error\n");
    m_Size = size;
    m_Data = new T[m_Size]();
}

template <class T>
DynamicArray<T>::DynamicArray(T* items, int count)
{
    if (items == nullptr)
        throw std::runtime_error("Null pointer error\n");

    if (count < 0)
        throw std::runtime_error("Negative size error\n");

    m_Size = count;
    m_Data = new T[m_Size];

    for (int i = 0; i < count; i++)
        m_Data[i] = items[i];
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray)
{
    m_Size = dynamicArray.m_Size;
    m_Data = new T[m_Size];

    for (int i = 0; i < m_Size; i++)
        m_Data[i] = dynamicArray.m_Data[i];
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
    delete[] m_Data;
}

template <class T>
T& DynamicArray<T>::operator[](int index)
{
    if (index < 0 || index >= m_Size)
        throw std::runtime_error("Index out of range\n");
    return m_Data[index];
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
    if (this != &other)
    {
        delete[] m_Data;
        m_Size = other.m_Size;
        m_Data = new T[m_Size];
        for (int i = 0; i < m_Size; i++)
            m_Data[i] = other.m_Data[i];
    }
    return *this;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other) noexcept
{
    delete[] m_Data;
    m_Size = other.m_Size;
    m_Data = other.m_Data;

    other.m_Data = nullptr;
    return *this;
}

template <class T>
const T& DynamicArray<T>::get(int index) const
{
    if (index < 0 || index >= m_Size)
        throw std::runtime_error("Index out of range\n");
    return m_Data[index];
}

template <class T>
int DynamicArray<T>::getSize() const { return m_Size; }

template <class T>
void DynamicArray<T>::set(int index, const T& value)
{
    if (index < 0 || index >= m_Size)
        throw std::runtime_error("Index out of range\n");
    m_Data[index] = value;
}

template <class T>
void DynamicArray<T>::resize(int new_Size)
{
    if (new_Size < 0)
        throw std::runtime_error("Negative size error\n");
    T* new_Data = new T[new_Size]();

    for (int i = 0; i < std::min(new_Size, m_Size); i++)
        new_Data[i] = m_Data[i];

    delete[] m_Data;
    m_Data = new_Data;
    m_Size = new_Size;
}

template <class T>
T* DynamicArray<T>::begin(){ return m_Data; }

template <class T>
T* DynamicArray<T>::end(){ return &m_Data[m_Size]; }

template <class T>
T DynamicArray<T>::pop(int index)
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

template <class T>
void DynamicArray<T>::print(int count) const
{
    for (int i = 0; i < count; i++)
        std::cout << m_Data[i] << ' ';
    std::cout << '\n';
}

template <class T>
void DynamicArray<T>::print() const
{
    for (int i = 0; i < m_Size; i++)
        std::cout << m_Data[i] << ' ';
    std::cout << '\n';
}