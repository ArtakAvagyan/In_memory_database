template <typename T>
RBTree<T>::RBTree():root{nullptr}{}

template <typename T>
RBTree<T>::~RBTree(){}

template <typename T>
bool    RBTree<T>::insert(const T& val)
{
    Node* x = nullptr;
    Node* y = root;
    while (y)
    {
        x = y;
        if (val < y->value)
        {
            y = y->l_child;
        }
        else if (val > y->value)
        {
            y = y->r_child;
        }
    }
    if (!x)
    {
        root = new Node (val, Node::BLACK);
        return true;
    }
    else if (val < x->value)
    {
        x->l_child = new Node (val, Node::RED, nullptr, nullptr, x);
        x = x->l_child;
    }
    else if (val > x->value)
    {
        x->r_child = new Node (val, Node::RED, nullptr, nullptr, x);
        x = x->r_child; // y = x->r
    }
    correctColors(x);
    return true;
}

template <typename T>
void    RBTree<T>::correctColors(Node *current)
{
    while (current->parrent && current->parrent->color == Node::RED)
    {
        if (current->parrent == current->parrent->parrent->l_child)
        {
            Node* uncle = current->parrent->parrent->r_child;
            if (uncle && uncle->color == Node::RED)
            {
                current->parrent->parrent->color = Node::RED;   /* 1 case */
                current->parrent->color = Node::BLACK;
                uncle->color = Node::BLACK;
                current = current->parrent->parrent;
                continue;
            }
            else if (current == current->parrent->r_child)
            {
                current = current->parrent;                      /* 2 case */
                leftRotate(current);
            }
            current->parrent->color = Node::BLACK;              /* 3 case */
            current->parrent->parrent->color = Node::RED;
            rightRotate(current->parrent->parrent); 
        }
        else // right
        {
            Node* uncle = current->parrent->parrent->l_child;
            std::cout<<uncle<<std::endl;
            if (uncle && uncle->color == Node::RED)
            {
                current->parrent->parrent->color = Node::RED;   /* 1 case */
                current->parrent->color = Node::BLACK;
                uncle->color = Node::BLACK;
                current = current->parrent->parrent;
                // continue;
            }
            else if (current == current->parrent->l_child)
            {
                current = current->parrent;                      /* 2 case */
                std::cout<<"current : "<<current<<std::endl;
                rightRotate(current);
            }
            current->parrent->color = Node::BLACK;              /* 3 case */
            current->parrent->parrent->color = Node::RED;
            leftRotate(current->parrent->parrent); 
        }
    }
    root->color = Node::BLACK;
}

template <typename T>
void    RBTree<T>::leftRotate(Node *current)
{
    Node* y = current->r_child;
    current->r_child = y->l_child;
    if (y->l_child != nullptr) {
      y->l_child->parrent = current;
    }
    y->parrent = current->parrent;
    if (current->parrent == nullptr) {
      this->root = y;
    } else if (current == current->parrent->l_child) {
      current->parrent->l_child = y;
    } else {
      current->parrent->r_child = y;
    }
    y->l_child = current;
    current->parrent = y;
}

template <typename T>
void    RBTree<T>::rightRotate(Node *x)
{
    Node* y = x->l_child;
    x->l_child = y->r_child;
    if (y->r_child != nullptr) {
      y->r_child->parrent = x;
    }
    y->parrent = x->parrent;
    if (x->parrent == nullptr) {
      this->root = y;
    } else if (x == x->parrent->r_child) {
      x->parrent->r_child = y;
    } else {
      x->parrent->l_child = y;
    }
    y->r_child = x;
    x->parrent = y;
}

template <typename T>
void    RBTree<T>::printBT(const std::string& prefix, const Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->value << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->l_child, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->r_child, false);
    }
}

template <typename T>
void RBTree<T>::printBT(const Node* node)
{
    printBT("", node, false);    
}
