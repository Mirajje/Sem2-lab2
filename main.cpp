#include <algorithm>
#include "Sequence.h"

int main()
{
    std::string items[5] = {"123", "13", "123", "13", "12"};
    std::string items2[3] = {"12", "23", "23"};


    ListSequence<std::string> list1(items, 5);
    ListSequence<std::string> list2(items2, 3);
    list1.print();

    Sequence<std::string>* seq = list1.concat(&list2);
    Sequence<std::string>* seq2 = seq->getSubSequence(0, 3);
    std::cout << seq->pop(6) << std::endl;
    seq2->print();
    seq->print();
}