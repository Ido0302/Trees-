#include <iostream>
#include <vector>
#include <stack>
#include <queue>

#include "Node.hpp"

template<typename T>
class Tree {
public:

    Tree(size_t maxChildren = 2) : maxChildren(maxChildren), root(nullptr) {}

    ~Tree() {
        clear(root);
    }

    Node* getRoot() const {
        return root;
    }

    Node* addRoot(const T& key) {
        root = new Node(key, maxChildren);
        return root;
    }

    Node* addChild(Node* parent, const T& key) {
        if (parent->children.size() < maxChildren) {
            Node* child = new Node(key, maxChildren);
            parent->children.push_back(child);
            return child;
        } else {
            std::cerr << "Cannot add more children to this node." << std::endl;
            return nullptr;
        }
    }

    class PreOrderIterator {
    public:
        explicit PreOrderIterator(Node* root) {
            if (root) {
                stack.push(root);
            }
        }

        bool hasNext() const {
            return !stack.empty();
        }

        Node* next() {
            if (!hasNext()) throw std::out_of_range("No more elements in PreOrderIterator");
            Node* current = stack.top();
            stack.pop();
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                stack.push(*it);
            }
            return current;
        }

    private:
        std::stack<Node*> stack;
    };

    class PostOrderIterator {
    public:
        explicit PostOrderIterator(Node* root) {
            if (root) {
                fillStack(root);
            }
        }

        bool hasNext() const {
            return !stack.empty();
        }

        Node* next() {
            if (!hasNext()) throw std::out_of_range("No more elements in PostOrderIterator");
            Node* current = stack.top();
            stack.pop();
            return current;
        }

    private:
        std::stack<Node*> stack;

        void fillStack(Node* node) {
            std::stack<Node*> tempStack;
            tempStack.push(node);
            while (!tempStack.empty()) {
                Node* current = tempStack.top();
                tempStack.pop();
                stack.push(current);
                for (auto& child : current->children) {
                    tempStack.push(child);
                }
            }
        }
    };

    class InOrderIterator {
    public:
        explicit InOrderIterator(Node* root) {
            if (root) {
                fillStack(root);
            }
        }

        bool hasNext() const {
            return !stack.empty();
        }

        Node* next() {
            if (!hasNext()) throw std::out_of_range("No more elements in InOrderIterator");
            Node* current = stack.top();
            stack.pop();
            return current;
        }

    private:
        std::stack<Node*> stack;

        void fillStack(Node* node) {
            std::stack<Node*> tempStack;
            Node* current = node;
            while (current || !tempStack.empty()) {
                while (current) {
                    tempStack.push(current);
                    current = current->children.empty() ? nullptr : current->children[0];
                }
                current = tempStack.top();
                tempStack.pop();
                stack.push(current);
                current = current->children.size() > 1 ? current->children[1] : nullptr;
            }
        }
    };

    PreOrderIterator preOrderBegin() const {
        return PreOrderIterator(root);
    }

    PostOrderIterator postOrderBegin() const {
        return PostOrderIterator(root);
    }

    InOrderIterator inOrderBegin() const {
        return InOrderIterator(root);
    }

private:
    Node* root;
    size_t maxChildren;

    void clear(Node* node) {
        if (node) {
            for (auto& child : node->children) {
                clear(child);
            }
            delete node;
        }
    }
};

int main() {
    Tree<int> tree;
    auto* root = tree.addRoot(1);
    auto* left = tree.addChild(root, 2);
    auto* right = tree.addChild(root, 3);
    tree.addChild(left, 4);
    tree.addChild(left, 5);
    tree.addChild(right, 6);
    tree.addChild(right, 7);

    std::cout << "Pre-Order Traversal: ";
    for (auto it = tree.preOrderBegin(); it.hasNext(); ) {
        std::cout << it.next()->key << " ";
    }
    std::cout << std::endl;

    std::cout << "Post-Order Traversal: ";
    for (auto it = tree.postOrderBegin(); it.hasNext(); ) {
        std::cout << it.next()->key << " ";
    }
    std::cout << std::endl;

    std::cout << "In-Order Traversal: ";
    for (auto it = tree.inOrderBegin(); it.hasNext(); ) {
        std::cout << it.next()->key << " ";
    }
    std::cout << std::endl;

    return 0;
}
