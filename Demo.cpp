//ID: 207826694
//GMAIL: didooron@gmail.com

#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp" 
#include "Complex.hpp"

using namespace std;
int main()
{
/*
    // Binary tree that contains doubles
    Tree<double> tree; 

    Node<double> root_node = Node<double>(1.1);
    tree.add_root(root_node);

    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);
    
    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    //cout << tree;

    // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl << "Pre-Order Traversal:" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << endl << "Post-Order Traversal:" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl << "In-Order Traversal:" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl << "BFS Traversal:" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl << "DFS Traversal:" << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    cout << endl << "myHeap Traversal:" << endl;
    for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;
*/

// The binary tree should look like:
    /*
     *     root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */
    
 /*  
    // 3-ary tree that contain integer
    Tree<int, 3> three_ary_tree; 

    Node<int> root_node = Node<int>(1);
    three_ary_tree.add_root(root_node);

    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);

    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    cout << three_ary_tree;

    // prints: 1, 2, 3, 4, 5, 6
    cout << endl << "3-ary Tree BFS Traversal:" << endl;
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    // prints: 1, 2, 5, 3, 6, 4
    cout << endl << "3-ary Tree DFS Traversal:" << endl;
    for (auto node = three_ary_tree.begin_dfs_scan(); node != three_ary_tree.end_dfs_scan(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;
*/

// The 3-ary tree should look like:
    /*
     *       root = 1
     *     /   |   \
     *    2    3    4
     *   /      \
     *  5        6
     */

    

    //binart tree that contain complex numbers
    Tree<Complex> complex_tree;

    Node<Complex> complex_root_node = Node<Complex>(Complex(1, 1));
    complex_tree.add_root(complex_root_node);

    Node<Complex> complex_n2 = Node<Complex>(Complex(2, 2));
    Node<Complex> complex_n3 = Node<Complex>(Complex(3, 3));
    Node<Complex> complex_n4 = Node<Complex>(Complex(4, 4));
    Node<Complex> complex_n5 = Node<Complex>(Complex(5, 5));
    Node<Complex> complex_n6 = Node<Complex>(Complex(6, 6));
    Node<Complex> complex_n7 = Node<Complex>(Complex(7, 7));

    complex_tree.add_sub_node(complex_root_node, complex_n2);
    complex_tree.add_sub_node(complex_root_node, complex_n3);
    complex_tree.add_sub_node(complex_n2, complex_n4);
    complex_tree.add_sub_node(complex_n2, complex_n5);
    complex_tree.add_sub_node(complex_n3, complex_n6);
    complex_tree.add_sub_node(complex_n3, complex_n7);

    cout << endl << "Complex Tree DFS Traversal:" << endl;
    for (auto node = complex_tree.begin_dfs_scan(); node != complex_tree.end_dfs_scan(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    cout << endl << "Complex Tree BFS Traversal:" << endl;
    for (auto node = complex_tree.begin_bfs_scan(); node != complex_tree.end_bfs_scan(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;   

    cout << endl << "Complex Tree Pre-Order Traversal:" << endl;
    for (auto node = complex_tree.begin_pre_order(); node != complex_tree.end_pre_order(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    cout << endl << "Complex Tree Post-Order Traversal:" << endl;
    for (auto node = complex_tree.begin_post_order(); node != complex_tree.end_post_order(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    cout << endl << "Complex Tree In-Order Traversal:" << endl;
    for (auto node = complex_tree.begin_in_order(); node != complex_tree.end_in_order(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    cout << endl << "Complex Tree Heap Traversal:" << endl;
    for (auto node = complex_tree.begin_heap(); node != complex_tree.end_heap(); ++node) {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    
    // Complex Tree GUI Launch:
    cout << complex_tree;


    return 0;
}

