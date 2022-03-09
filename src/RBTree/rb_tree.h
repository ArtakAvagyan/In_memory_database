#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include "../Vector/vector.h"

template <typename T>
class RBTree
{	
public:
    RBTree();
    ~RBTree();

public:
    struct Node
    {
    public:
        enum Color
        {
            RED = 0,
            BLACK = 1
        };
        Node* l_child;
        Node* r_child;
        Node* parrent;
        const T value;
        Color color;

        Node(const T& val, Color color = Node::RED, Node *left = nullptr, Node* right = nullptr, Node* par = nullptr):
            value{val}, color{color}, l_child{left}, r_child{right}, parrent{par}{}
    };
	
public:
    void clear();
    bool insert(const T& val);
    Vector<T> print();
	
private:
    void correctColors(Node*);
    void leftRotate(Node*);
    void rightRotate(Node*);
    void printBT(const Node*, Vector<T>&);
    void clear(Node*);

private:
    Node* root{};
};

#include "rb_tree.hpp"
#endif // THREE_H