#include <iostream>
#include <stdexcept>
#include <vector>

#include "Node.hpp"
#include "Tree.hpp"

using namespace std;

template <typename T>

    Tree::Tree(size_t maxChildren = 2) : maxChildren(maxChildren), root(nullptr) {}

    ~Tree() {
        clear(root);
    }

    Node* Tree::getRoot() const {
        return root;
    }

    Node* Tree::addRoot(const T& key) {
        root = new Node(key, maxChildren);
        return root;
    }

    Node* Tree::addChild(Node* parent, const T& key) {
        if (parent->children.size() < maxChildren) {
            Node* child = new Node(key, maxChildren);
            parent->children.push_back(child);
            return child;
        } else {
            std::cerr << "Cannot add more children to this node." << std::endl;
            return nullptr;
        }
    }