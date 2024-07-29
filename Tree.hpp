//ID: 207826694
//GMAIL: didooron@gmail.com

#ifndef TREE_HPP
#define TREE_HPP


#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <queue>

#include "Node.hpp"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <type_traits>
#include <sstream>
#include <map>
#include <iomanip> 


const float NODE_RADIUS = 40.0f; // constant for the radius of the nodes (GUI)

template <typename T, int K = 2> // by default, K is 2 (Binary tree)
class Tree
{
private:
    Node<T> *root;
    bool is_binary_tree;
    int k;
    
    /*
    * The following vectors are used to store the nodes in the order of traversal.
    */
    std::vector<Node<T> *> pre_order_nodes;
    std::vector<Node<T> *> post_order_nodes;
    std::vector<Node<T> *> in_order_nodes;
    std::vector<Node<T> *> bfs_nodes;
    std::vector<Node<T> *> dfs_nodes;
    std::vector<Node<T> *> heap_nodes;


public:
    // Constructor
    Tree() : root(nullptr), is_binary_tree(K == 2) {
        k = K;
    }

    // Destructor
    ~Tree()
    {
        delete_tree(root);
    }

    Node<T>* get_root() const
    {
        return root;
    }

    void set_root(Node<T>* newRoot){
        root = newRoot;
    }

    int get_k() const
    {
        return k;
    }


/**
 * create new root if wasn't exist tree before, else throw exeption
 */
    void add_root(const Node<T> &node)
    {
        if (root != nullptr)
        {
            throw std::runtime_error("Root node already exists.");
        }
        root = new Node<T>(node.get_value());
    }

/**
 * get exist node and other node and add the other to exist node's children
 */
    void add_sub_node(const Node<T> &parent, const Node<T> &child)
    {
        //chech if the tree exist
        if (root == nullptr)
            throw std::runtime_error("Root node not found.");
        
        Node<T> *parent_ptr = find_node(root, parent.get_value());

        //if the requested node not found
        if (parent_ptr == nullptr)
            throw std::runtime_error("Parent node not found.");

        //if the requested node is full
        if (parent_ptr->children.size() >= (size_t)this->k)
            throw std::runtime_error("Node has reached the maximum number of children.");

        parent_ptr->add_child(child);
    }

    /**
     * get some root of tree and value and search for node with this value.
     * if exist return the pointer of node, else return null
     */
    Node<T> *find_node(Node<T> *node, const T &value)
    {
        if (node == nullptr)
            return nullptr;

        if (node->get_value() == value)
            return node;
            
        for (auto child : node->get_children())
        {
            Node<T> *found = find_node(child, value);
            if (found != nullptr)
                return found;
        }
        return nullptr;
    }

//iterator implemantion

/**
 * return iterator to begin of vector who order as pre-order
 */
    typename std::vector<Node<T> *>::iterator begin_pre_order()
    {
        if (K != 2)
        {
            return begin_dfs_scan();
        }
        pre_order_nodes.clear();
        pre_order_traversal(root, pre_order_nodes);
        return pre_order_nodes.begin();
    }


/**
 * return iterator to end of vector who order as pre-order
 */
    typename std::vector<Node<T> *>::iterator end_pre_order()
    {
        if (K != 2)
        {
            return end_dfs_scan();
        }
        return pre_order_nodes.end();
    }

/**
 * pre-order travesal on tree 
 */
    void pre_order_traversal(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (node == nullptr)
            return;
        result.push_back(node);
        for (auto child : node->get_children())
        {
            pre_order_traversal(child, result);
        }
    }

/**
 * return iterator to begin of vector who order as post-order
 */
    typename std::vector<Node<T> *>::iterator begin_post_order()
    {
        if (K != 2)
        {
            return begin_dfs_scan();
        }
        post_order_nodes.clear();
        post_order_traversal(root, post_order_nodes);
        return post_order_nodes.begin();
    }

/**
 * return iterator to end of vector who order as post-order
 */
    typename std::vector<Node<T> *>::iterator end_post_order()
    {
        if (K != 2)
        {
            return end_dfs_scan();
        }
        return post_order_nodes.end();
    }

/*
*  post-order traversal on tree
*/   
    void post_order_traversal(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (node == nullptr)
            return;
        for (auto child : node->get_children())
        {
            post_order_traversal(child, result);
        }
        result.push_back(node);
    }

/**
 * return iterator to begin of vector who order as in-order
 */
    typename std::vector<Node<T> *>::iterator begin_in_order()
    {
        if (K != 2)
        {
            return begin_dfs_scan();
        }
        in_order_nodes.clear();
        in_order_traversal(root, in_order_nodes);
        return in_order_nodes.begin();
    }

/**
 * return iterator to end of vector who order as in-order
 */
    typename std::vector<Node<T> *>::iterator end_in_order()
    {
        if (K != 2)
        {
            return end_dfs_scan();
        }
        return in_order_nodes.end();
    }

/**
 * in-order traversal on tree 
 */ 
    void in_order_traversal(Node<T> *node, std::vector<Node<T> *> &result) {
    if (node == nullptr)
        return;

    auto children = node->get_children();
    if (children.size() > 0) {
        in_order_traversal(children[0], result); // Left child
    }
    result.push_back(node); // Root
    if (children.size() > 1) {
        in_order_traversal(children[1], result); // Right child
    }
    }

/**
 * return iterator to begin of vector who order as BFS
 */
    typename std::vector<Node<T> *>::iterator begin_bfs_scan()
    {
        bfs_nodes.clear();
        BFS_traversal(root, bfs_nodes);
        return bfs_nodes.begin();
    }

    
/**
 * return iterator to end of vector who order as BFS
 */
    typename std::vector<Node<T> *>::iterator end_bfs_scan()
    {
        return bfs_nodes.end();
    }

/**
 * BFS traversal on tree
 */
    void BFS_traversal(Node<T> *node, std::vector<Node<T> *> &result)
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
            for (auto child : current->get_children())
            {
                q.push(child);
            }
        }
    }

/**
 * return iterator to begin of vector who order as DFS
 */
    typename std::vector<Node<T> *>::iterator begin_dfs_scan()
    {
        dfs_nodes.clear();
        DFS_traversal(root, dfs_nodes);
        return dfs_nodes.begin();
    }


/**
 * return iterator to begin of vector who order as DFS
 */
    typename std::vector<Node<T> *>::iterator end_dfs_scan()
    {
        return dfs_nodes.end();
    }

/**
 * DFS traversal on tree
 */

    void DFS_traversal(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (node == nullptr)
            return;
        result.push_back(node);
        for (auto child : node->get_children())
        {
            DFS_traversal(child, result);
        }
    }


    typename std::vector<Node<T> *>::iterator begin_heap()
    {
        heap_nodes.clear();
        myHeap(root, heap_nodes);
        return heap_nodes.begin();
    }

    typename std::vector<Node<T> *>::iterator end_heap()
    {
        return heap_nodes.end();
    }

    

    void myHeap(Node<T> *node, std::vector<Node<T> *> &result)
    {
        if (node == nullptr)
            return;
        DFS_traversal(node, result);
        auto comp = [](Node<T> *lhs, Node<T> *rhs) { return lhs->get_value() > rhs->get_value(); };
        std::make_heap(result.begin(), result.end(), comp);
    }

    void delete_tree(Node<T> *node)
    {
        if (node == nullptr)
            return;
        for (auto child : node->get_children())
        {
            delete_tree(child);
        }
        delete node;
    }


    /*
    Stream operator: launches the GUI to visualize the tree.
    */
    friend std::ostream &operator<<(std::ostream &os, Tree<T, K> &tree)
    {
        Node<T> *root = tree.get_root();

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
            tree.draw_tree(window, font); // Main function to draw the tree
            window.display();
        }
        
    return os;
    
    }

    /*
    draw_tree function: draws the tree on the window.
    It calls the helper functions to calculate the positions of the nodes and draw them.
    */
void draw_tree(sf::RenderWindow &window, sf::Font &font)
{
    if (this->root == nullptr) return;

    // Create a map to store positions of each node
    std::map<Node<T>*, sf::Vector2f> positions;
    float start_x = window.getSize().x / 2;
    float start_y = NODE_RADIUS * 2;
    calculate_positions(this->root, positions, start_x, start_y, window.getSize().x / 4);

    for (auto &entry : positions)
    {
        draw_node(window, entry.first, entry.second, font, positions);
    }
}
/*
    calculate_positions function: calculates the positions of the nodes in the tree.
    It uses a map to store the positions of each node.
    it calculates the positions recursively by traversing the tree.
*/
void calculate_positions(Node<T> *node, std::map<Node<T>*, sf::Vector2f> &positions, float x, float y, float horizontal_spacing)
{
    if (node == nullptr) return;

    positions[node] = sf::Vector2f(x, y);
    float child_x = x - ((node->get_children().size() - 1) * horizontal_spacing / 2);
    float child_y = y + NODE_RADIUS * 3;

    for (auto child : node->get_children())
    {
        calculate_positions(child, positions, child_x, child_y, horizontal_spacing / 2);
        child_x += horizontal_spacing;
    }
}
/*
    draw_node function: draws the node on the window.
    It uses the SFML library to draw the node and the text.
*/
void draw_node(sf::RenderWindow &window, Node<T> *node, sf::Vector2f position, sf::Font &font, const std::map<Node<T>*, sf::Vector2f> &positions)
{
    sf::CircleShape circle(NODE_RADIUS);
    circle.setFillColor(sf::Color::Green);
    circle.setOrigin(NODE_RADIUS, NODE_RADIUS);
    circle.setPosition(position);

    sf::Text text;
    text.setFont(font);
    if constexpr (std::is_same<T, std::string>::value)
    {
        text.setString(node->get_value());
    }
    else
    {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << node->get_value();
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
    
    for (auto child : node->get_children())
    {
        sf::Vertex line[] =
        {
            sf::Vertex(position),
            sf::Vertex(positions.at(child))
        };
        window.draw(line, 2, sf::Lines);
    }
}

}; //end class

#endif 