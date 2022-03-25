#include <iostream>

template<typename T>
struct Node
{
    T value;
    Node* next;
    Node* prev;
};

template<typename T>
class LinkedList{
private:
    Node<T>* m_Head = nullptr;
    Node<T>* m_Tail = nullptr;
    int m_Size = 0;

public:
    LinkedList() = default;

    LinkedList(T* items, int count)
    {
        if (count < 0)
            throw std::runtime_error("Negative size error\n");
        if (count > 0)
            m_Head = new Node<T>;
        Node<T> *current = m_Head;
        Node<T> *previous = nullptr;

        for (int i = 0; i < count; i++)
        {
            current->value = items[i];
            current->prev = previous;
            if (i != count - 1)
            {
                previous = current;
                current->next = new Node<T>;
                current = current->next;
            }
        }
        if (current != nullptr){
            m_Tail = current;
            m_Tail->next = nullptr;
        }
        m_Size = count;
    }

    LinkedList(const LinkedList& linkedList)
    {
        if (linkedList.m_Size > 0)
            m_Size = linkedList.m_Size;

        if (m_Size > 0)
            m_Head = new Node<T>;
        Node<T> *current = m_Head;
        Node<T> *previous = nullptr;

        for (int i = 0; i < m_Size; i++)
        {
            current->value = linkedList[i];
            current->prev = previous;
            if (i != m_Size - 1)
            {
                previous = current;
                current->next = new Node<T>;
                current = current->next;
            }
        }
        if (current != nullptr)
        {
            m_Tail = current;
            m_Tail->next = nullptr;
        }
    }

    ~LinkedList()
    {
        Node<T>* current = m_Head;
        while (current->next != nullptr)
        {
            current = current->next;
            delete current->prev;
        }
        delete current;
        printf("List destructor has been called\n");
    }

    T& operator[](int index)
    {
        if (index < 0 || index >= m_Size)
            throw std::runtime_error("Index out of range\n");
        Node<T>* current;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        return current->value;
    }

    int getSize(){ return m_Size; }

    const T& get(int index)
    {
        if (index < 0 || index >= m_Size)
            throw std::runtime_error("Index out of range\n");
        Node<T>* current = m_Head;

        for (int i = 0; i < index; i++)
            current = current->next;

        return current->value;
    }

    T pop(int index)
    {
        if (index < 0 || index >= m_Size)
            throw std::runtime_error("Index out of range\n");
        Node<T>* current = m_Head;

        for (int i = 0; i < index; i++)
            current = current->next;
        current->next->prev = current->prev;
        current->prev->next = current->next;
        T result = current->value;
        delete current;
        return result;
    }

    void print()
    {
        Node<T>* current = m_Head;
        for (int i = 0; i < m_Size; i++)
        {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};