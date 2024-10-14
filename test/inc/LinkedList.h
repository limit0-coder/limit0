#include <initializer_list>
#include <iostream>

template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val) { data = _val; }

        friend class SingleLinkedList<T>;
    };
    Node *head = nullptr;
    int size = 0;
    Node *currentPos = nullptr;
    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);

public:
    T getCurrentVal() const;
    void setCurrentVal(const T &_val);
    bool isEmpty() const;

    int getSize() const;
    void emptyList();
    bool find(const T &_val);
    SingleLinkedList() {};
    ~SingleLinkedList();
    SingleLinkedList(std::initializer_list<T> _l);
    void printList() const;
    SingleLinkedList(const SingleLinkedList<T> &_l);
    SingleLinkedList<T> &operator=(const SingleLinkedList<T> &_l);

    void insert(T _val);
    bool find(const T &_val) const;
    void remove();
};

template <typename T>
T SingleLinkedList<T>::getCurrentVal() const
{
    if (currentPos == nullptr)
    {
        puts("Empty current position! Can't get value!");
        exit(0);
    }
    return currentPos->data;
}

template <typename T>
void SingleLinkedList<T>::setCurrentVal(const T &_val)
{
    if (currentPos == nullptr)
    {
        puts("Empty current position! Can't set value!");
        exit(0);
    }
    currentPos->data = _val;
}

template <typename T>
bool SingleLinkedList<T>::find(const T &_val)
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->data == _val)
        {
            currentPos = p;
            return true;
        }
        p = p->next;
    }
    return false;
}

template <typename T>
void SingleLinkedList<T>::insert(T _val)
{
    Node *newNode = new Node(_val);
    if (head == nullptr)
    {
        head = newNode;
        currentPos = head;
        return;
    }
    Node *y = currentPos->next;
    currentPos->next = newNode;
    currentPos = currentPos->next;
    currentPos->next = y;
}

template <typename T>
void SingleLinkedList<T>::remove()
{
    if (head == nullptr)
        return;
    Node *p = head;
    if (p->next == nullptr)
    {
        head = nullptr;
        return;
    }
    while (p->next->next != nullptr)
        p = p->next;
    p->next = nullptr;
}

template <typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node *newNode = new Node(*i);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
}

template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    Node *p = head;
    while (p != nullptr)
    {
        Node *t = p;
        p = p->next;
        delete t;
    }
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node *p = head;
    while (p != nullptr)
    {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
};

template <typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    _copy(_l);
}

template <typename T>
void SingleLinkedList<T>::emptyList()
{
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template <typename T>
SingleLinkedList<T> &SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.head;
    while (p != nullptr)
    {
        Node *newNode = new Node(p->data);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
}