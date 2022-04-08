#ifndef H_SEQUENCE
#define H_SEQUENCE

template <class T>
class Sequence
{
public:
    virtual T getFirst() const = 0;
    virtual T getLast() const = 0;
    virtual T get(int index)  const= 0;
    virtual Sequence<T>* getSubSequence(int startIndex, int endIndex) const = 0;
    virtual int getLength() const = 0;

public:
    virtual T& operator[](int index) = 0;

public:
    virtual void set(T item, int index) = 0;
    virtual void append(T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insertAt(T item, int index) = 0;
    virtual Sequence<T>* concat(Sequence<T>* list) const = 0;
    virtual T pop(int index) = 0;
    virtual void print() const = 0;

};

#endif