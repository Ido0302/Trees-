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
        T key;
        std::vector<Node*> children;

        Node(const T& key, size_t maxChildren);
};

#endif