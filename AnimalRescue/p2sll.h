template <typename T>
struct List {
    // List is made up of a sequence of Nodes,
    // each pointing to the next
    // User doesn't know about Nodes
    template <typename NT>
    struct Node {
        NT value;
        Node<NT>* next;
    };
    
    Node<T>* head;
    
    List()
    {
        head = NULL;
    }
    
    ~List()
    {
        while( head != NULL )
        {
            Node<T>* del = head;
            head = head->next;
            delete del;
        }
    }
    
    void append(T newValue)
    {
        // allocate memory and assign values for new Node
        Node<T>* newNode = new Node<T>;
        newNode->value = newValue;
        newNode->next  = NULL;
        
        // handle special case for empty list
        if( head == NULL )
        {
            head = newNode;
            return; // we're done, so get out
        }
        
        // get pointer to last node in list
        Node<T>* last = head;
        while( last->next != NULL )
            last = last->next;
        
        // now append newNode to the list
        last->next = newNode;
    }
    
    void prepend(T newValue)
    {
        // allocate memory and assign values for new Node
        Node<T>* newNode = new Node<T>;
        newNode->value = newValue;
        newNode->next  = head; // point next to current head value
        head = newNode;
    }
    
    bool contains(T search)
    {
        Node<T>* walker = head;
        while( walker != NULL )
        {
            if( walker->value == search )
                return true;
            walker = walker->next;
        }
        return false;
    }
    
    bool isEmpty()
    {
        return( head == NULL );
    }
    
    int getSize()
    {
        int count = 0;
        Node<T>* walker = head;
        while( walker != NULL )
        {
            count++;
            walker = walker->next;
        }
        return count;
    }
    
    // assume at least k values in the list
    // assume k > 0
    T getKth(int k)
    {
        // try to help stupid users
        if( k > getSize() )
            k = getSize();
        // find the kth value in the list and return it
        Node<T>* walker = head;
        for( int step = 1; step < k; step++ )
            walker = walker->next;
        return walker->value;
    }
    
    // remove the first value from the list
    // assume the list is non-empty?
    void decapitate()
    {
        if( head != NULL ) // make sure it won't crash if list empty
        {
            Node<T>* del = head; // remember the current head
            head = head->next;
            delete del;
        }
    }
    
    // assume list is non-empty
    void removeKth(int k)
    {
        // if list empty, nothing to remove, so just end the function
        if( head == NULL )
            return;
        
        // special case : remove head of the list
        if( k == 1 )
        {
            decapitate();
            return;
        }
        
        Node<T>* before = head;
        for( int step = 1; step < k-1 && before->next->next != NULL; step++ )
            before = before->next;
        Node<T>* del = before->next;
        before->next = before->next->next; // before->next = del->next;
        delete del;
    }
    
    void printList(std::ostream& out)
    {
        // special case : empty list
        if( head == NULL )
        {
            out << "[empty]";
            return;
        }
        
        // list has at least two values
        out << head->value;
        Node<T>* walker = head->next;
        while( walker != NULL )
        {
            out << ", " << walker->value;
            walker = walker->next;
        }
        
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, List<T>& L)
{
    L.printList(out);
    return out;
}
