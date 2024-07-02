#include <iostream>
#include <stdexcept>
#include <vector>

#include "Node.hpp"

using namespace std;

template <typename T>


Node::Node(const T &key, size_t maxChildren) : key(key)
{
    children.reserve(maxChildren);
}
