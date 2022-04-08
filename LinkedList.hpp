#include <iostream>

template<class T>
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
        if (items == nullptr)
            throw std::runtime_error("Null pointer error\n");
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
        {
            m_Head = new Node<T>;
        }

        m_Size = linkedList.m_Size;

        Node<T> *current = m_Head;
        Node<T> *previous = nullptr;

        for (int i = 0; i < m_Size; i++)
        {
            current->value = linkedList.get(i);
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
        if (m_Head != nullptr)
        {
            Node<T> *current = m_Head;
            while (current->next != nullptr)
            {
                current = current->next;
                delete current->prev;
            }
            delete current;
        }
        printf("List destructor has been called\n");
    }

public:
    T& operator[](int index)
    {
        if (index < 0 || index >= m_Size)
            throw std::runtime_error("Index out of range\n");

        Node<T>* current = m_Head;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        return current->value;
    }

    LinkedList& operator=(const LinkedList& other)
    {
        if (this != &other){
            Node<T>* current = m_Head;
            if (m_Head != nullptr)
            {
                while (current->next != nullptr)
                {
                    current = current->next;
                    delete current->prev;
                }
                delete current;
            }

            m_Head = nullptr; m_Tail = nullptr; m_Size = 0;
            if (other.m_Size > 0)
            {
                m_Size = other.m_Size;
                m_Head = new Node<T>;
            }

            current = m_Head;
            Node<T> *previous = nullptr;

            for (int i = 0; i < m_Size; i++)
            {
                current->value = other.get(i);
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
        return *this;
    }

    LinkedList& operator=(LinkedList&& other) noexcept
    {
        Node<T> *current = m_Head;
        if (m_Head != nullptr)
        {
            while (current->next != nullptr)
            {
                current = current->next;
                delete current->prev;
            }
            delete current;
        }
        m_Head = other.m_Head;
        m_Size = other.m_Size;
        m_Tail = other.m_Tail;

        other.m_Head = nullptr;
        other.m_Tail = nullptr;
        other.m_Size = 0;
        return *this;
    }

public:
    int getSize() const { return m_Size; }

    const T& get(int index) const
    {
        if (index < 0 || index >= m_Size)
            throw std::runtime_error("Index out of range\n");

        Node<T>* current = m_Head;

        for (int i = 0; i < index; i++)
            current = current->next;

        return current->value;
    }

    const T& getFirst() const
    {
        if (m_Size == 0)
            throw std::runtime_error("Index out of range\n");

        return m_Head->value;
    }

    const T& getLast() const
    {
        if (m_Size == 0)
            throw std::runtime_error("Index out of range\n");

        return m_Tail->value;
    }

    T pop(int index)
    {
        if (index < 0 || index >= m_Size)
            throw std::runtime_error("Index out of range\n");

        Node<T>* current = m_Head;

        for (int i = 0; i < index; i++)
            current = current->next;
        T result;

        if (index == 0)
        {
            if (m_Size == 1)
                m_Tail = nullptr;
            m_Head = current->next;
            if (m_Head != nullptr)
                m_Head->prev = nullptr;
            result = current->value;
            delete current;
        }
        else if (index == m_Size - 1)
        {
            m_Tail = current->prev;
            m_Tail->next = nullptr;
            result = current->value;
            delete current;
        }
        else {
            current->next->prev = current->prev;
            current->prev->next = current->next;
            result = current->value;
            delete current;
        }
        m_Size -= 1;
        return result;
    }

    LinkedList<T>* getSubList(int startIndex, int endIndex) const
    {
        if (startIndex < 0 || endIndex >= m_Size)
            throw std::runtime_error("Index out of range\n");

        Node<T>* current = m_Head;
        int count = 0;
        T items[endIndex - startIndex + 1];

        for (int i = 0; i < startIndex; i++)
            current = current->next;

        for (int i = startIndex; i < endIndex + 1; i++)
        {
            count += 1;
            items[i - startIndex] = current->value;
            current = current->next;
        }

        auto* result = new LinkedList(items, count);
        return result;
    }

    void append(const T& item)
    {
        if (m_Size == 0)
        {
            m_Head = new Node<T>;
            m_Head->value = item;
            m_Head->next = nullptr;
            m_Head->prev = nullptr;
            m_Tail = m_Head;
        }
        else
        {
            m_Tail->next = new Node<T>;
            m_Tail->next->value = item;
            m_Tail->next->prev = m_Tail;
            m_Tail->next->next = nullptr;
            m_Tail = m_Tail->next;
        }
        m_Size += 1;
    }

    void prepend(const T& item)
    {
        if (m_Size == 0)
        {
            m_Head = new Node<T>;
            m_Head->value = item;
            m_Head->next = nullptr;
            m_Head->prev = nullptr;
            m_Tail = m_Head;
        }
        else
        {
            m_Head->prev = new Node<T>;
            m_Head->prev->value = item;
            m_Head->prev->next = m_Head;
            m_Head->prev->prev = nullptr;
            m_Head = m_Head->prev;
        }
        m_Size += 1;
    }

    void insertAt(const T& item, int index)
    {
        if (index < 0 || index > m_Size)
            throw std::runtime_error("Index out of range\n");

        if (index == 0)
            this->prepend(item);

        else if (index == m_Size)
            this->append(item);

        else
        {
            Node<T>* current = m_Head;
            for (int i = 0; i < index; i++)
                current = current->next;
            auto* new_Node = new Node<T>;
            new_Node->next = current;
            new_Node->prev = current->prev;
            new_Node->value = item;
            new_Node->prev->next = new_Node;
            new_Node->next->prev = new_Node;
            m_Size += 1;
        }
    }

    LinkedList<T>* concat(LinkedList<T>* other){
        if (other == nullptr)
            throw std::runtime_error("Null pointer error\n");

        auto* resultList = new LinkedList<T>;
        *resultList = *this;

        for (int i = 0; i < other->getSize(); i++)
            resultList->append((*other)[i]);

        return resultList;
    }

    void print() const
    {
        Node<T>* current = m_Head;
        for (int i = 0; i < m_Size; i++)
        {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void reversed_print() const
    {
        Node<T>* current = m_Tail;
        for (int i = 0; i < m_Size; i++)
        {
            std::cout << current->value << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }
};