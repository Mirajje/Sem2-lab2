#ifndef MAIN_CPP_RECTMATRIX_HPP
#define MAIN_CPP_RECTMATRIX_HPP

#include "Sequence_lib.h"
#include "Errors.h"

template <class T>
class RectMatrix
{
private:
    Sequence<Sequence<T>* >* m_Data;
    int m_Height = 0;
    int m_Width = 0;

    void deleteData();

public:
    RectMatrix();
    RectMatrix(int n, int m);
    RectMatrix(const RectMatrix<T>& other);
    RectMatrix(RectMatrix<T>&& other) noexcept;

    ~RectMatrix();
    Sequence<T>& operator [](int index);
    RectMatrix<T>& operator =(const RectMatrix<T>& other);
    RectMatrix<T>& operator =(RectMatrix<T>&& other) noexcept;

    bool operator ==(const RectMatrix<T>& other) const;

    void set(const T& value, int stringNumber, int columnNumber);
    const T& get(int stringNumber, int columnNumber) const;
    int getHeight() const;
    int getWidth() const;

    void print() const;
};

template<class T>
RectMatrix<T>&& operator +(const RectMatrix<T>& matrix1, const RectMatrix<T>& matrix2);

template<class T>
RectMatrix<T>&& operator *(const RectMatrix<T>& matrix, int multiplier);

template<class T>
RectMatrix<T>&& operator *(int multiplier, const RectMatrix<T>& matrix);



template <class T>
void RectMatrix<T>::deleteData()
{
    if (m_Data != nullptr)
    {
        for (int i = 0; i < m_Height; i++)
            delete m_Data->get(i);
        delete m_Data;
    }
}

template <class T>
RectMatrix<T>::RectMatrix()
{
    m_Data = new ArraySequence<Sequence<T>* >;
}

template <class T>
RectMatrix<T>::RectMatrix(int n, int m)
{
    m_Data = new ArraySequence<Sequence<T>* >(n);
    for (int i = 0; i < n; i++)
        (*m_Data)[i] = new ArraySequence<T>(m);

    m_Height = n;
    m_Width = m;
}

template <class T>
RectMatrix<T>::RectMatrix(const RectMatrix<T>& other)
{
    m_Height = other.getHeight();
    m_Width = other.getWidth();
    m_Data = new ArraySequence<Sequence<T>* >(m_Height);
    for (int i = 0; i < m_Height; i++)
        (*m_Data)[i] = new ArraySequence<T>(*(*other.m_Data)[i]);
}

template <class T>
RectMatrix<T>::RectMatrix(RectMatrix<T>&& other) noexcept
{
    m_Height = other.getHeight();
    m_Width = other.getWidth();
    m_Data = other.m_Data;

    other.m_Data = nullptr;
    other.m_Height = 0;
    other.m_Width = 0;
}

template <class T>
RectMatrix<T>::~RectMatrix()
{
    deleteData();
}

template <class T>
Sequence<T>& RectMatrix<T>::operator [](int index)
{
    return (*(*m_Data)[index]);
}

template <class T>
RectMatrix<T>& RectMatrix<T>::operator =(const RectMatrix<T>& other)
{
    if (this != &other)
    {
        if (this->getWidth() != other.getWidth() || this->getHeight() != other.getHeight())
        {
            deleteData();
            m_Height = other.getHeight();
            m_Width = other.getWidth();
            m_Data = new ArraySequence<Sequence<T>* >(m_Height);
            for (int i = 0; i < m_Height; i++)
                (*m_Data)[i] = new ArraySequence<T>(*(*other.m_Data)[i]);
        }
        else
            for (int i = 0; i < m_Height; i++)
                for (int j = 0; j < m_Width; j++)
                    (*this)[i][j] = other.get(i, j);
    }
    return *this;
}

template <class T>
RectMatrix<T>& RectMatrix<T>::operator =(RectMatrix<T>&& other)  noexcept
{
    if (this != &other)
    {
        deleteData();
        m_Data = other.m_Data;
        m_Height = other.getHeight();
        m_Width = other.getWidth();

        other.m_Data = nullptr;
        other.m_Height = 0;
        other.m_Width = 0;
    }
    return *this;
}

template <class T>
bool RectMatrix<T>::operator ==(const RectMatrix<T>& other) const
{
    if (this->getWidth() != other.getWidth() || this->getHeight() != other.getHeight())
        return false;

    for (int i = 0; i < m_Height; i++)
        for (int j = 0; j < m_Width; j++)
            if (this->get(i, j) != other.get(i, j))
                return false;

    return true;
}

template <class T>
void RectMatrix<T>::set(const T& value, int stringNumber, int columnNumber)
{
    (*(*m_Data)[stringNumber])[columnNumber] = value;
}

template <class T>
const T& RectMatrix<T>::get(int stringNumber, int columnNumber) const
{
    return m_Data->get(stringNumber)->get(columnNumber);
}

template <class T>
int RectMatrix<T>::getWidth() const
{
    return m_Width;
}
template <class T>
int RectMatrix<T>::getHeight() const
{
    return m_Height;
}

template <class T>
void RectMatrix<T>::print() const
{
    for (int i = 0; i < m_Height; i++)
        (*m_Data)[i]->print();
    printf("\n");
}

template <class T>
RectMatrix<T>&& operator +(const RectMatrix<T>& matrix1, const RectMatrix<T>& matrix2)
{
    if (matrix1.getHeight() != matrix2.getHeight() || matrix1.getWidth() != matrix2.getWidth())
        throw Errors(Errors::NOT_EQUAL_SIZES_ERROR);

    auto* new_Matrix = new RectMatrix<T>(matrix1.getHeight(), matrix1.getWidth());
    for (int i = 0; i < matrix1.getHeight(); i++)
        for (int j = 0; j < matrix1.getWidth(); j++)
            (*new_Matrix)[i][j] = matrix1.get(i, j) + matrix2.get(i, j);

    return std::move(*new_Matrix);
}

template <class T>
RectMatrix<T>&& operator *(const RectMatrix<T>& matrix, int multiplier)
{
    auto* new_Matrix = new RectMatrix<T>(matrix.getHeight(), matrix.getWidth());
    for (int i = 0; i < matrix.getHeight(); i++)
        for (int j = 0; j < matrix.getWidth(); j++)
            (*new_Matrix)[i][j] = matrix.get(i, j) * multiplier;

    return std::move(*new_Matrix);
}

template <class T>
RectMatrix<T>&& operator *(int multiplier, const RectMatrix<T>& matrix)
{
    auto* new_Matrix = new RectMatrix<T>(matrix.getHeight(), matrix.getWidth());
    for (int i = 0; i < matrix.getHeight(); i++)
        for (int j = 0; j < matrix.getWidth(); j++)
            (*new_Matrix)[i][j] = matrix.get(i, j) * multiplier;

    return std::move(*new_Matrix);
}

#endif
