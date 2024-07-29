//ID: 207826694
//GMAIL: didooron@gmail.com

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

    T get_value() const { return key; }
    vector<Node<T>*> get_children() const { return children; }

    void add_child(const Node<T>& child) {
        children.push_back(new Node<T>(child));
    }


}; //end class

#endif 