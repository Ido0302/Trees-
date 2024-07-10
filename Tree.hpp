
#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <queue>
#include <map>
#include <string>

#include <cstddef>

//#include <SFML/Graphics.hpp>
#include <type_traits>
#include <sstream>
#include <iomanip>

const float NODE_RADIUS = 50.0f; // constant for the radius of the nodes (GUI)

template <typename T, int K = 2> // by default, K is 2 (Binary tree)
class Tree
{
private:
    Node<T> *root;
    int k;

    /*
     * The following vectors are used to store the nodes in the order of traversal.
     */
    std::vector<Node<T> *> pre_order_vector;
    std::vector<Node<T> *> post_order_vector;
    std::vector<Node<T> *> in_order_vector;
    std::vector<Node<T> *> bfs_vector;
    std::vector<Node<T> *> dfs_vector;
    std::vector<Node<T> *> heap_vector;

    
    void preOrderSearch(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (node == nullptr)
            return;
        result.push_back(node);
        for (auto child : node->getChildren())
            preOrderSearch(child, result);
    }

    void postOrderSearch(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (node == nullptr)
            return;
        for (auto child : node->getChildren())
            postOrderSearch(child, result);
        result.push_back(node);
    }

    void inOrderSearch(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (node == nullptr)
            return;

        auto children = node->getChildren();
        if (children.size() > 0)
        {
            inOrderSearch(children[0], result); // Left child
        }
        result.push_back(node); // Root
        if (children.size() > 1)
        {
            inOrderSearch(children[1], result); // Right child
        }
    }

    void bfs(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (node == nullptr)
            return;
        std::queue<Node<T> *> q;
        q.push(node);
        while (!q.empty())
        {
            Node<T> *current = q.front();
            q.pop();
            result.push_back(current);
            for (auto child : current->getChildren())
            {
                q.push(child);
            }
        }
    }

    void dfs(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (node == nullptr)
            return;
        result.push_back(node);
        for (auto child : node->getChildren())
        {
            dfs(child, result);
        }
    }

    void myHeap(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (node == nullptr)
            return;
        dfs(node, result); 

        //Compare function
        auto comp = [](Node<T> *node1, Node<T> *node2)
        { return node1->getKey() > node2->getKey(); };

        //make heap from vector and the compare function
        std::make_heap(result.begin(), result.end(), comp);
    }

public:
    // Constructor
    Tree() : root(nullptr) { k = K; }

    // Destructor
    ~Tree()
    {
        delete_tree(root);
    }

    int get_k() const
    {
        return k;
    }

    void add_root(const Node<T> &node)
    {
        if (root != nullptr)
        {
            throw std::runtime_error("Root node already exists.");
        }
        root = new Node<T>(node.getKey());
    }

    void add_sub_node(const Node<T> &parent, const Node<T> &newChild)
    {
        if (root == nullptr)
        {
            throw std::runtime_error("Tree not created.");
        }

        //find the request node
        Node<T> *parent_ptr = find_node(root, parent.getKey());

        if (parent_ptr == nullptr)
        {
            throw std::runtime_error("The node not found.");
        }

        if (parent_ptr->children.size() >= (size_t)this->k)
        {
            throw std::runtime_error("Node has reached the maximum number of children.");
        }

        parent_ptr->addChild(newChild);
    }

    
    /**
     * The function get pointer to root and some value.
     * The function search in tree node with this value.
     * If found, return pointer to request node, else return null
     */
    Node<T> *find_node(Node<T> *node, const T &key)
    {
        if (node == nullptr)
            return nullptr;
        if (node->getKey() == key)
            return node;
        for (auto child : node->getChildren()) // search for each node's cheildren
        {
            Node<T> *found = find_node(child, key);
            if (found != nullptr)
                return found;
        }
        return nullptr;
    }

    Node<T> *getRoot() const
    {
        return root;
    }

    typename std::vector<Node<T> *>::iterator begin_pre_order()
    {
        if (K != 2)
        {
            return begin_dfs_scan();
        }
        pre_order_vector.clear();
        preOrderSearch(root, pre_order_vector);
        return pre_order_vector.begin();
    }

    typename std::vector<Node<T> *>::iterator end_pre_order()
    {
        if (K != 2)
        {
            return end_dfs_scan();
        }
        return pre_order_vector.end();
    }

    typename std::vector<Node<T> *>::iterator begin_post_order()
    {
        if (K != 2)
        {
            return begin_dfs_scan();
        }
        post_order_vector.clear();
        postOrderSearch(root, post_order_vector);
        return post_order_vector.begin();
    }

    typename std::vector<Node<T> *>::iterator end_post_order()
    {
        if (K != 2)
        {
            return end_dfs_scan();
        }
        return post_order_vector.end();
    }

    typename std::vector<Node<T> *>::iterator begin_in_order()
    {
        if (K != 2)
        {
            return begin_dfs_scan();
        }
        in_order_vector.clear();
        inOrderSearch(root, in_order_vector);
        return in_order_vector.begin();
    }

    typename std::vector<Node<T> *>::iterator end_in_order()
    {
        if (K != 2)
        {
            return end_dfs_scan();
        }
        return in_order_vector.end();
    }

    typename std::vector<Node<T> *>::iterator begin_bfs_scan()
    {
        bfs_vector.clear();
        bfs(root, bfs_vector);
        return bfs_vector.begin();
    }

    typename std::vector<Node<T> *>::iterator end_bfs_scan()
    {
        return bfs_vector.end();
    }

    typename std::vector<Node<T> *>::iterator begin_dfs_scan()
    {
        dfs_vector.clear();
        dfs(root, dfs_vector);
        return dfs_vector.begin();
    }

    typename std::vector<Node<T> *>::iterator end_dfs_scan()
    {
        return dfs_vector.end();
    }

    typename std::vector<Node<T> *>::iterator begin_heap()
    {
        heap_vector.clear();
        myHeap(root, heap_vector);
        return heap_vector.begin();
    }

    typename std::vector<Node<T> *>::iterator end_heap()
    {
        return heap_vector.end();
    }


    void delete_tree(Node<T> *node)
    {
        if (node == nullptr)
            return;
        for (auto child : node->getChildren())
        {
            delete_tree(child);
        }
        delete node;
    }

       
    // stream operator: launches the GUI to visualize the tree.
    friend std::ostream &operator<<(std::ostream &os, Tree<T, K> &tree)
    {
        Node<T> *root = tree.getRoot();

        if(root == nullptr)
        {
            os << "Tree is empty." << std::endl;
            return os;
        }

        os << "Launching GUI..." << std::endl;

        // Font initialization
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Failed to load font file 'arial.ttf'" << std::endl;
            return os;
        }

        // Window initialization
        sf::RenderWindow window(sf::VideoMode(700, 700), "EX4");
        window.setVerticalSyncEnabled(true); // Attempt to enable vertical sync


        // Main loop of GUI
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::Cyan);
            tree.drawTree(window, font); // Main function to draw the tree
            window.display();
        }

    return os;

    }


    //drawTree function: draws the tree on the window.
    //It calls the helper functions to calculate the positions of the nodes and draw them.

void drawTree(sf::RenderWindow &window, sf::Font &font)
{
    if (this->root == nullptr) return;

    // Create a map to store positions of each node
    std::map<Node<T>*, sf::_vector2f> positions;
    float start_x = window.getSize().x / 2;
    float start_y = NODE_RADIUS * 2;
    calculate_positions(this->root, positions, start_x, start_y, window.getSize().x / 4);

    for (auto &entry : positions)
    {
        draw_node(window, entry.first, entry.second, font, positions);
    }
}

//    calculate_positions function: calculates the positions of the nodes in the tree.
//    It uses a map to store the positions of each node.
//    it calculates the positions recursively by traversing the tree.

void calculate_positions(Node<T> *node, std::map<Node<T>*, sf::_vector2f> &positions, float x, float y, float horizontal_spacing)
{
    if (node == nullptr) return;

    positions[node] = sf::_vector2f(x, y);
    float child_x = x - ((node->getChildren().size() - 1) * horizontal_spacing / 2);
    float child_y = y + NODE_RADIUS * 3;

    for (auto child : node->getChildren())
    {
        calculate_positions(child, positions, child_x, child_y, horizontal_spacing / 2);
        child_x += horizontal_spacing;
    }
}

//    draw_node function: draws the node on the window.
//    It uses the SFML library to draw the node and the text.

void draw_node(sf::RenderWindow &window, Node<T> *node, sf::_vector2f position, sf::Font &font, const std::map<Node<T>*, sf::_vector2f> &positions)
{
    sf::CircleShape circle(NODE_RADIUS);
    circle.setFillColor(sf::Color::Green);
    circle.setOrigin(NODE_RADIUS, NODE_RADIUS);
    circle.setPosition(position);

    sf::Text text;
    text.setFont(font);
    if constexpr (std::is_same<T, std::string>::value)
    {
        text.setString(node->getKey());
    }
    else
    {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << node->getKey();
        text.setString(oss.str());
    }
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    text.setPosition(position);

    window.draw(circle);
    window.draw(text);

    // Draw lines to children
    // The lines are drawn using the positions map which contains the positions of each node.

    for (auto child : node->getChildren())
    {
        sf::Vertex line[] =
        {
            sf::Vertex(position),
            sf::Vertex(positions.at(child))
        };
        window.draw(line, 2, sf::Lines);
    }
}



}; // end class

#endif
