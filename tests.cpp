#include "Sequence.h"

template <class T>
T func1(const T& s)
{
    return s + "ah";
}

template <class T>
bool func2(const T& s)
{
    return (s.size() > 3);
}

template <class T>
T func3(const T& v1, const T& v2)
{
    return (v1 + v2);
}

void tests()
{
    // ListSequence test ===================================================================================================

    printf("LIST SEQUENCE TESTS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    std::string items[5] = {"123", "13", "123", "13", "12"};
    Sequence<std::string>* seq1 = new ListSequence<std::string>(items, 5);
    Sequence<std::string>* seq2 = new ListSequence<std::string>(items, 5);

    if (seq1->getLength() == 5)
        std::cout << "getLength test successfully passed!\n";
    else
        std::cout << "getLength test failed! =============================================================================\n";

    if (seq1->getFirst() == "123")
        std::cout << "getFirst test successfully passed!\n";
    else
        std::cout << "getFirst test failed! =============================================================================\n";

    if (seq1->getLast() == "12")
        std::cout << "getLast test successfully passed!\n";
    else
        std::cout << "getLast test failed! =============================================================================\n";

    if (seq1->get(1) == "13")
        std::cout << "get test successfully passed!\n";
    else
        std::cout << "get test failed! =============================================================================\n";

    if (seq1->find("13") == 1)
        std::cout << "find test successfully passed!\n";
    else
        std::cout << "find test failed! =============================================================================\n";

    if (*seq2 == *seq1)
        std::cout << "== test successfully passed!\n";
    else
        std::cout << "== test failed! =============================================================================\n";

    if (*seq1->getSubSequence(0, 1) == *seq1->getSubSequence(2, 3))
        std::cout << "getSubSequence test successfully passed!\n";
    else
        std::cout << "getSubSequence test failed! =============================================================================\n";

    if ((*seq1)[3] == "13")
        std::cout << "[] test successfully passed!\n";
    else
        std::cout << "[] test failed! =============================================================================\n";

    if (seq1->get(1) == "13")
        std::cout << "get test successfully passed!\n";
    else
        std::cout << "get test failed! =============================================================================\n";

    Sequence<std::string>* seq3 = new ListSequence<std::string>(*seq2);

    if (*seq3 == *seq2)
        std::cout << "= test successfully passed!\n";
    else
        std::cout << "= test failed! =============================================================================\n";

    seq1->set("kek", 2);
    if (seq1->get(2) == "kek")
        std::cout << "set test successfully passed!\n";
    else
        std::cout << "set test failed! =============================================================================\n";

    seq1->append("kek");
    if (seq1->get(5) == "kek")
        std::cout << "append test successfully passed!\n";
    else
        std::cout << "append test failed! =============================================================================\n";

    seq1->prepend("kek");
    if (seq1->get(0) == "kek")
        std::cout << "prepend test successfully passed!\n";
    else
        std::cout << "prepend test failed! =============================================================================\n";

    seq1->insertAt("meme", 4);
    if (seq1->get(4) == "meme")
        std::cout << "insertAt test successfully passed!\n";
    else
        std::cout << "insertAt test failed! =============================================================================\n";

    seq1->insertAt("meme", 4);
    if (seq1->get(4) == "meme")
        std::cout << "insertAt test successfully passed!\n";
    else
        std::cout << "insertAt test failed! =============================================================================\n";

    *seq2 = *seq3;
    seq3 = seq3->concat(seq1);
    for (int i = 0; i < seq1->getLength(); i++)
        seq2->append(seq1->get(i));
    if (*seq2 == *seq3)
        std::cout << "concat test successfully passed!\n";
    else
        std::cout << "concat test failed! =============================================================================\n";

    *seq2 = *seq1;
    std::string k = seq1->pop(1);

    bool flag = false;
    if (k == seq2->get(1) && seq1->getLength() == seq2->getLength() - 1)
    {
        flag = true;
        for (int i = 0; i < seq1->getLength(); i++)
            if (i < 1)
                if (seq1->get(i) != seq2->get(i))
                    flag = false;
            else if (i > 1)
                if (seq1->get(i) != seq2->get(i + 1))
                    flag = false;
    }
    if (flag)
        std::cout << "pop test successfully passed!\n";
    else
        std::cout << "pop test failed! =============================================================================\n";

    *seq2 = *seq1;
    for (int i = 0; i < seq2->getLength(); i++)
        (*seq2)[i] += "ah";

    if (*seq1->map(func1) == *seq2)
        std::cout << "map test successfully passed!\n";
    else
        std::cout << "map test failed! =============================================================================\n";

    seq2->clear();
    seq2 = new ListSequence<std::string>;
    for (int i = 0; i < seq1->getLength(); i++)
        if (func2((*seq1)[i]))
            seq2->append((*seq1)[i]);

    if (*seq1->where(func2) == *seq2)
        std::cout << "where test successfully passed!\n";
    else
        std::cout << "where test failed! =============================================================================\n";

    std::string result;
    for (int i = 0; i < seq1->getLength(); i++)
        result = seq1->get(i) + result;

    if (seq1->reduce(func3, "") == result)
        std::cout << "reduce test successfully passed!\n";
    else
        std::cout << "reduce test failed! =============================================================================\n";

    // ArraySequence test ===================================================================================================

    printf("ARRAY SEQUENCE TESTS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    seq1 = new ArraySequence<std::string>(items, 5);
    seq2 = new ArraySequence<std::string>(items, 5);

    if (seq1->getLength() == 5)
        std::cout << "getLength test successfully passed!\n";
    else
        std::cout << "getLength test failed! =============================================================================\n";

    if (seq1->getFirst() == "123")
        std::cout << "getFirst test successfully passed!\n";
    else
        std::cout << "getFirst test failed! =============================================================================\n";

    if (seq1->getLast() == "12")
        std::cout << "getLast test successfully passed!\n";
    else
        std::cout << "getLast test failed! =============================================================================\n";

    if (seq1->get(1) == "13")
        std::cout << "get test successfully passed!\n";
    else
        std::cout << "get test failed! =============================================================================\n";

    if (seq1->find("13") == 1)
        std::cout << "find test successfully passed!\n";
    else
        std::cout << "find test failed! =============================================================================\n";

    if (*seq2 == *seq1)
        std::cout << "== test successfully passed!\n";
    else
        std::cout << "== test failed! =============================================================================\n";

    if (*seq1->getSubSequence(0, 1) == *seq1->getSubSequence(2, 3))
        std::cout << "getSubSequence test successfully passed!\n";
    else
        std::cout << "getSubSequence test failed! =============================================================================\n";

    if ((*seq1)[3] == "13")
        std::cout << "[] test successfully passed!\n";
    else
        std::cout << "[] test failed! =============================================================================\n";

    if (seq1->get(1) == "13")
        std::cout << "get test successfully passed!\n";
    else
        std::cout << "get test failed! =============================================================================\n";

    seq3 = new ArraySequence<std::string>(*seq2);

    if (*seq3 == *seq2)
        std::cout << "= test successfully passed!\n";
    else
        std::cout << "= test failed! =============================================================================\n";

    seq1->set("kek", 2);
    if (seq1->get(2) == "kek")
        std::cout << "set test successfully passed!\n";
    else
        std::cout << "set test failed! =============================================================================\n";

    seq1->append("kek");
    if (seq1->get(5) == "kek")
        std::cout << "append test successfully passed!\n";
    else
        std::cout << "append test failed! =============================================================================\n";

    seq1->prepend("kek");
    if (seq1->get(0) == "kek")
        std::cout << "prepend test successfully passed!\n";
    else
        std::cout << "prepend test failed! =============================================================================\n";

    seq1->insertAt("meme", 4);
    if (seq1->get(4) == "meme")
        std::cout << "insertAt test successfully passed!\n";
    else
        std::cout << "insertAt test failed! =============================================================================\n";

    seq1->insertAt("meme", 4);
    if (seq1->get(4) == "meme")
        std::cout << "insertAt test successfully passed!\n";
    else
        std::cout << "insertAt test failed! =============================================================================\n";

    *seq2 = *seq3;
    seq3 = seq3->concat(seq1);
    for (int i = 0; i < seq1->getLength(); i++)
        seq2->append(seq1->get(i));
    if (*seq2 == *seq3)
        std::cout << "concat test successfully passed!\n";
    else
        std::cout << "concat test failed! =============================================================================\n";

    *seq2 = *seq1;
    k = seq1->pop(1);

    flag = false;
    if (k == seq2->get(1) && seq1->getLength() == seq2->getLength() - 1)
    {
        flag = true;
        for (int i = 0; i < seq1->getLength(); i++)
            if (i < 1)
                if (seq1->get(i) != seq2->get(i))
                    flag = false;
                else if (i > 1)
                    if (seq1->get(i) != seq2->get(i + 1))
                        flag = false;
    }
    if (flag)
        std::cout << "pop test successfully passed!\n";
    else
        std::cout << "pop test failed! =============================================================================\n";

    *seq2 = *seq1;
    for (int i = 0; i < seq2->getLength(); i++)
        (*seq2)[i] += "ah";

    if (*seq1->map(func1) == *seq2)
        std::cout << "map test successfully passed!\n";
    else
        std::cout << "map test failed! =============================================================================\n";

    seq2->clear();
    seq2 = new ArraySequence<std::string>;
    for (int i = 0; i < seq1->getLength(); i++)
        if (func2((*seq1)[i]))
            seq2->append((*seq1)[i]);

    if (*seq1->where(func2) == *seq2)
        std::cout << "where test successfully passed!\n";
    else
        std::cout << "where test failed! =============================================================================\n";

    result = "";
    for (int i = 0; i < seq1->getLength(); i++)
        result = seq1->get(i) + result;

    seq1->print();
    if (seq1->reduce(func3, "") == result)
        std::cout << "reduce test successfully passed!\n";
    else
        std::cout << "reduce test failed! =============================================================================\n";

}