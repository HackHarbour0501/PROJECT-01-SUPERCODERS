template<typename T>
struct Node
{
    T data;
    Node<T>* next;
    

    Node(const T& value)
        : data(value),
          next(nullptr)
    {
    }
};
template<typename T>
class LinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;

    size_t size;
public:
    LinkedList(); // Constructor initializing an emplty Linked List 
    ~LinkedList(); // destructor destroy eveynodes
    LinkedList(const LinkedList<T>& other); //copy constructor
    LinkedList<T>& operator=(const LinkedList<T>& other);
    bool isEmpty() const; // check if the linked list is empty
    size_t getSize() const; // return the size of the linked list
    bool insertFront(const T& value); //insertion at front
    bool removeFront(); // remove the first node of the linked list
    bool insertBack(const T& value); // insert a new node at the end of the linked list
    bool removeBack(); // remove the last node of the linked list
    void display() const; //helps in debugging by displaying the content
    void clear(); // remove all nodes from the linked list`
    
    template<typename Predicate>  // find the first node that satisfies the given predicate 
    Node<T>* findIf(Predicate pred) const;  // Generaly used for the hashmap functions.
};
template<typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}
template<typename T>
LinkedList<T>::~LinkedList(){
    
    Node<T>* current = head;
    while (current != nullptr)
    {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
        
    }
    head=nullptr;
    tail=nullptr;
    size=0;
}
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
    head = nullptr;
    tail = nullptr;
    size = 0;

    Node<T>* current = other.head;

    while(current != nullptr)
    {
        insertBack(current->data);

        current = current->next;
    }
}
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
    if(this == &other)
    {
        return *this;
    }

    clear();

    Node<T>* current = other.head;

    while(current != nullptr)
    {
        insertBack(current->data);

        current = current->next;
    }

    return *this;
}
template<typename T>
bool LinkedList<T>::isEmpty() const
{
    return size == 0;
}
template<typename T>
size_t LinkedList<T>::getSize() const
{
    return size;
}
template<typename T>
bool LinkedList<T>::insertFront(const T& value)
{
    Node<T>* newNode = new Node<T>(value);

    if(head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = head;

        head = newNode;
    }

    ++size;

    return true;
}
template<typename T>
bool LinkedList<T>::removeFront()
{
    if(head == nullptr)
    {
        return false;
    }

    Node<T>* temp = head;

    head = head->next;

    delete temp;

    --size;

    if(size == 0)
    {
        tail = nullptr;
    }

    return true;
}
template<typename T>
bool LinkedList<T>::insertBack(const T& value)
{
    Node<T>* newNode = new Node<T>(value);

    if(head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;

        tail = newNode;
    }

    ++size;

    return true;
}
template<typename T>
void LinkedList<T>::display() const
{
    Node<T>* current = head;

    while(current != nullptr)
    {
        std::cout << current->data << " -> ";

        current = current->next;
    }

    std::cout << "nullptr" << std::endl;
}
template<typename T>
bool LinkedList<T>::removeBack()
{
    if(head == nullptr)
    {
        return false;
    }

    if(head == tail)
    {
        delete head;

        head = nullptr;
        tail = nullptr;

        --size;

        return true;
    }

    Node<T>* current = head;

    while(current->next != tail)
    {
        current = current->next;
    }

    Node<T>* temp = tail;

    tail = current;

    tail->next = nullptr;

    delete temp;

    --size;

    return true;
}
template<typename T>
void LinkedList<T>::clear()
{
    Node<T>* current = head;

    while(current != nullptr)
    {
        Node<T>* temp = current;

        current = current->next;

        delete temp;
    }

    head = nullptr;
    tail = nullptr;

    size = 0;
}
template<typename T>
template<typename Predicate>
Node<T>* LinkedList<T>::findIf(Predicate pred) const
{
    Node<T>* current = head;

    while(current != nullptr)
    {
        if(pred(current->data))
        {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}