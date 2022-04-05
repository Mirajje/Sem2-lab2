#ifndef H_SEQUENCE
#define H_SEQUENCE

template <typename T>
class Sequence
{
public:
    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(int index) = 0;
    virtual Sequence<T>* getSubSequence(int startIndex, int endIndex) = 0;
    virtual int getLength() = 0;

public:
    virtual void set(T item, int index) = 0;

public:
    virtual void append(T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insertAt(T item, int index) = 0;
    //virtual Sequence<T>* concat(Sequence<T>* list) = 0;
    virtual void print() = 0;

public:
    virtual T& operator[](int index) = 0;
};

#endif