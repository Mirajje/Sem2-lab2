#include <algorithm>
#include "Sequence.h"

int main()
{
    std::string items[5] = {"123", "13", "123", "13", "12"};
    std::string items2[3] = {"12", "23", "23"};

    ArraySequence<std::string> array1(items, 5);
    ListSequence<std::string> array2(items2, 3);


    Sequence<std::string>* seq = array1.concat(&array2);
    seq->append("abobina");
    seq->print();
    Sequence<std::string>* seq2 = new ArraySequence<std::string>();

    *seq2 = *seq;
    seq2->append("131312312321");
    seq2->print();

    std::cout << seq2->getFirst() << " " << seq2->getLast() << std::endl;
    std::cout << seq2->get(2) << " "  << std::endl;

    Sequence<std::string>* seq3 = seq2->getSubSequence(1, seq2->getLength() - 1);
    seq3->print();

    (*seq3)[4] += "ahahah";
    seq3->set("aboba", 0);
    seq3->append("a");
    seq3->prepend("b");
    seq3->insertAt("789987", seq3->getLength());

    std::cout << seq3->pop(seq3->getLength() - 3) << " "  << std::endl;
    seq3->print();

    seq3 = seq2->concat(seq3);
    seq3->print();
    (*seq2) = (*seq3);
    seq2->print();

    std::cout << (*seq2 == *seq3) << std::endl;

    seq3->pop(8);
    seq2->pop(17);
    std::cout << seq3->find("abobina") << std::endl;

    seq2 = seq2->map(func);
    seq2->print();

    int items5[5] = {1, 2, 3};
    Sequence<int>* new_seq = new ArraySequence<int>(items5, 3);

    std::cout << new_seq->where(func2) << std::endl;
    std::cout << *new_seq->where(func2) << std::endl;
}