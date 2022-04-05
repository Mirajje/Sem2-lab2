#include <algorithm>
#include "ListSequence.hpp"
#include "ArraySequence.hpp"

template <typename T>
void printSequence(Sequence<T>* seq)
{
    seq->print();
}

int main()
{
    int items[5] = {5, 4, 3, 2, 1};
    int items2[3] = {3, 2, 1};

    DynamicArray<int> temp(items2, 3);

    ArraySequence<int> array3(temp);
    ListSequence<int> array(items, 5);
    //ArraySequence<int> array2(array);
    array[3] += 15;
    ListSequence<int> list(items, 5);
    array.print();
    //array2.print();
    array3.print();

    array.print();
    Sequence<int>* seq = array.getSubSequence(0, 4);
    seq = seq->getSubSequence(0, 4);
    std::cout << array.get(2) << array.getFirst() << array.getLast() << array.getLength() << std::endl;
    seq->print();

    seq->insertAt(147, 2);
    seq->append(-5);
    seq->prepend(7);
    seq->print();
}