#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>

using namespace std;

template <typename T>

class Node {
public:
    T key;
    std::vector<Node<T>*> children;

    Node(T key) : key(key) {};
    ~Node() {}

    T getKey() const { return key; }
    vector<Node<T>*> getChildren() const { return children; }

    void addChild(const Node<T>& child) {
        children.push_back(new Node<T>(child));
    }


}; //end class

#endif 