#ifndef RBTREE_H
# define RBTREE_H

#include <iostream>

template <typename T>
class RBTree
{
    public:
    struct Node
    {
        public:
        enum        Color
        {
            RED = 0,
            BLACK = 1
        };
        Node*       l_child;
        Node*       r_child;
        Node*       parrent;
        const   T     value;
        Color        color;

        Node(const T& val, Color color = Node::RED, Node *left = nullptr, Node* right = nullptr, Node* par = nullptr):
            value{val}, color{color}, l_child{left}, r_child{right}, parrent{par}{}
    };
    public:
    RBTree();
    ~RBTree();
    public:

    void printBT(const Node* node);
    void printBT(const std::string& prefix, const Node* node, bool isLeft);

    bool    insert(const T& val);
    private:
    void correctColors(Node*);
    void leftRotate(Node*);
    void rightRotate(Node*);


    public: // must be privite
    Node* root{};
};


#include "rb_tree.hpp"


#endif // THREE_H
