#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

template<typename T>

class Node
{
    public:

    Tree(size_t maxChildren = 2);
    ~Tree();
    Node* addRoot(const T& key);
    Node* addChild(Node* parent, const T& key); 

};

#endif