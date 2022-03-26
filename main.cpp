#include <algorithm>
#include "DynamicArray.cpp"
#include "LinkedList.cpp"

int main()
{
    int items[5] = {5, 4, 3, 2, 1};
    int items2[3] = {3, 2, 1};

    LinkedList<int> empty_list;
    LinkedList<int> list(items, 5);
    LinkedList<int> list2(items2, 3);
    LinkedList<int> a;
    list2 = list;
    empty_list.insertAt(items[1], 0);
    empty_list.insertAt(items[2], 1);
    empty_list.insertAt(items[4], 0);
    empty_list.insertAt(15, 3);
    empty_list.insertAt(-2, 0);
    empty_list.insertAt(4, 1);
    empty_list.print();
    empty_list[0] += 100;
    empty_list.reversed_print();
    list2.print();
    list.print();

    list.concat(&empty_list);
    list2.print();
    list.print();
    //list[7] += 20;
    list.print();
    empty_list.print();
}