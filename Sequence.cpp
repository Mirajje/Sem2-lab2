#include "Sequence.h"

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