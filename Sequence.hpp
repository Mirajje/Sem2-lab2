#include <iostream>

#ifndef HPP_SEQUENCE
#define HPP_SEQUENCE

template <class T> class Sequence;
template <class T> std::ostream& operator<<(std::ostream& out, Sequence<T>* seq);
template <class T> std::ostream& operator<<(std::ostream& out, const Sequence<T>& seq);

template <class T>
class Sequence
{
public:
    virtual T getFirst() const = 0;
    virtual T getLast() const = 0;
    virtual T get(int index)  const= 0;
    virtual int find(const T& item) const = 0; // returns index of the first occurrence; returns -1 if nothing was found
    virtual Sequence<T>* getSubSequence(int startIndex, int endIndex) const = 0;
    virtual int getLength() const = 0;
    virtual void clear() = 0;

public:
    virtual T& operator[](int index) = 0;
    virtual Sequence<T>& operator =(const Sequence<T>& other) = 0;
    virtual bool operator ==(const Sequence<T>& other) const = 0;

public:
    virtual void set(T item, int index) = 0;
    virtual void append(T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insertAt(T item, int index) = 0;
    virtual Sequence<T>* concat(Sequence<T>* list) const = 0;
    virtual T pop(int index) = 0;
    virtual void print() const = 0;

public:
    virtual Sequence<T>* map(T func(const T&)) const = 0;
    virtual Sequence<T>* where(bool func(const T&)) const = 0;
    virtual T reduce(T func(const T&, const T&), T startValue) const = 0;

public:
    friend std::ostream& operator<< <> (std::ostream& out, Sequence<T>* seq);
    friend std::ostream& operator<< <> (std::ostream& out, const Sequence<T>& seq);

};

template <class T>
std::ostream& operator<<(std::ostream& out, Sequence<T>* seq)
{
    for (int i = 0; i < seq->getLength(); i++)
        out << seq->get(i) << " ";

    return out;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Sequence<T>& seq)
{
    for (int i = 0; i < seq.getLength(); i++)
        out << seq.get(i) << " ";

    return out;
}

#endif