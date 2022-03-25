#include <algorithm>
#include "DynamicArray.cpp"
#include "LinkedList.cpp"

int main()
{
    int items[5] = {5, 4, 3, 2, 1};

    LinkedList<int> list(items, 5);
    list.print();
    int b;
    b = list.get(1);

    std::cout << list.pop(2) << " " << b << std::endl;
    list.print();
}