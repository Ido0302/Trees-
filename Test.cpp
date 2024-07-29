//ID: 207826694
//GMAIL: didooron@gmail.com

#include <iostream>
#include <sstream>

#include "doctest.h"
#include "Complex.hpp"
#include "Node.hpp"
#include "Tree.hpp"

using namespace std;


TEST_CASE("Tests for creatue tree"){

Node<int> n1 = Node<int>(10);
Node<int> n2 = Node<int>(20);
Node<int> n3 = Node<int>(30);
Node<int> n4 = Node<int>(40);

Tree<int> tree;
tree.add_root(n1);
CHECK_THROWS(tree.add_root(n2));         //add root again

CHECK_THROWS(tree.add_sub_node(n2, n1)); //add root for to other node
tree.add_sub_node(n1, n2);

CHECK_THROWS(tree.add_sub_node(n4, n3)); //add node to node who not exist in tree
tree.add_sub_node(n1,n3);

CHECK_THROWS(tree.add_sub_node(n1, n4)); //add third child in binary tree

Tree<int, 3> tree2;
tree2.add_root(n1);
tree2.add_sub_node(n1,n2);
tree2.add_sub_node(n1,n3);
CHECK_NOTHROW(tree2.add_sub_node(n1,n4)); //make 3-ary tree

}

TEST_CASE("Tests for Binary Tree Iterators - Pre-order, In-order, Post-order, BFS, DFS"){

    Node<int> n1 = Node<int>(10);
    Node<int> n2 = Node<int>(20);
    Node<int> n3 = Node<int>(30);
    Node<int> n4 = Node<int>(40);
    Node<int> n5 = Node<int>(50);
    Node<int> n6 = Node<int>(60);
    Node<int> n7 = Node<int>(70);

    Tree<int> tree;
    tree.add_root(n1);

    tree.add_sub_node(n1, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n2, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n3, n6);
    tree.add_sub_node(n3, n7);

    vector<int> expected_pre_order_nodes = {10, 20, 40, 50, 30 ,60, 70};
    size_t i =0;
    for ( auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        CHECK((*node)->get_value() == expected_pre_order_nodes[i]);
        i++;
    }

    vector<int> expected_in_order_nodes = {40, 20, 50, 10, 60 ,30, 70};
    i =0;
    for ( auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        CHECK((*node)->get_value() == expected_in_order_nodes[i]);
        i++;
    }

    vector<int> expected_post_order_nodes = {40, 50, 20, 60, 70 ,30, 10};
    i =0;
    for ( auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        CHECK((*node)->get_value() == expected_post_order_nodes[i]);
        i++;
    }

    vector<int> expected_bfs_nodes = {10, 20, 30, 40, 50 ,60, 70};
    i =0;
    for ( auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        CHECK((*node)->get_value() == expected_bfs_nodes[i]);
        i++;
    }

    vector<int> expected_dfs_nodes = {10, 20, 40, 50, 30 ,60, 70};
    i =0;
    for ( auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        CHECK((*node)->get_value() == expected_dfs_nodes[i]);
        i++;
    }

    vector<int> expected_heap_nodes = {10, 20, 40, 50, 30 ,60, 70};
    i =0;
    for ( auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
        CHECK((*node)->get_value() == expected_heap_nodes[i]);
        i++;
    }

}

TEST_CASE("Tests for 3-ary Tree Iterators - BFS, DFS"){
    
    Node<int> n1 = Node<int>(10);
    Node<int> n2 = Node<int>(20);
    Node<int> n3 = Node<int>(30);
    Node<int> n4 = Node<int>(40);
    Node<int> n5 = Node<int>(50);
    Node<int> n6 = Node<int>(60);
    Node<int> n7 = Node<int>(70);

    Tree<int,3> tree;
    tree.add_root(n1);

    tree.add_sub_node(n1, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);
    tree.add_sub_node(n3, n7);

    vector<int> expected_bfs_nodes = {10, 20, 30, 40, 50 ,60, 70};
    size_t i =0;
    for ( auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        CHECK((*node)->get_value() == expected_bfs_nodes[i]);
        i++;
    }

    vector<int> expected_dfs_nodes = {10, 20, 50, 60, 30 ,70, 40};
    i =0;
    for ( auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        CHECK((*node)->get_value() == expected_dfs_nodes[i]);
        i++;
    }

    //pre-order iterator on 3-ary tree like dfs iterator 
    i =0;
    for ( auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        CHECK((*node)->get_value() == expected_dfs_nodes[i]);
        i++;
    }
 
}


TEST_CASE("Tests for Complex Tree"){

    Complex c1(6,8);
    Complex c2(-5,12);
    Complex c3(3,-4);

    Node<Complex> complex_root_node = Node<Complex>(c1);
    Node<Complex> complex_left_child_node = Node<Complex>(c2);
    Node<Complex> complex_right_child_node = Node<Complex>(c3);


    Tree<Complex> complex_tree;
    complex_tree.add_root(complex_root_node);
    complex_tree.add_sub_node(complex_root_node, complex_left_child_node);
    complex_tree.add_sub_node(complex_root_node, complex_right_child_node);

    CHECK(c1.magnitude() == 10.0);
    CHECK(c2.magnitude() == 13.0);
    CHECK(c3.magnitude() == 5.0);


    vector<Complex> expected_pre_order_nodes = {c1, c2, c3};
    size_t i =0;
    for ( auto node = complex_tree.begin_pre_order(); node != complex_tree.end_pre_order(); ++node) {
        CHECK((*node)->get_value() == expected_pre_order_nodes[i]);
        i++;
    }

    vector<Complex> expected_in_order_nodes = {c2, c1, c3};
    i =0;
    for ( auto node = complex_tree.begin_in_order(); node != complex_tree.end_in_order(); ++node) {
        CHECK((*node)->get_value() == expected_in_order_nodes[i]);
        i++;
    }

    vector<Complex> expected_post_order_nodes = {c2, c3, c1};
    i =0;
    for ( auto node = complex_tree.begin_post_order(); node != complex_tree.end_post_order(); ++node) {
        CHECK((*node)->get_value() == expected_post_order_nodes[i]);
        i++;
    }

    vector<Complex> expected_bfs_nodes = {c1, c2, c3};
    i =0;
    for ( auto node = complex_tree.begin_bfs_scan(); node != complex_tree.end_bfs_scan(); ++node) {
        CHECK((*node)->get_value() == expected_bfs_nodes[i]);
        i++;
    }

    vector<Complex> expected_dfs_nodes = {c1, c2, c3};
    i =0;
    for ( auto node = complex_tree.begin_dfs_scan(); node != complex_tree.end_dfs_scan(); ++node) {
        CHECK((*node)->get_value() == expected_dfs_nodes[i]);
        i++;
    }

    vector<Complex> expected_heap_nodes = {c3, c2, c1};
    i =0;
    for ( auto node = complex_tree.begin_heap(); node != complex_tree.end_heap(); ++node) {
        CHECK((*node)->get_value() == expected_heap_nodes[i]);
        i++;
    }
}



TEST_CASE("Test Complex's Arithmetic Operators"){
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex c3 = c1 + c2;
    CHECK(c3.get_real() == 4);
    CHECK(c3.get_imag() == 6);

    Complex c4 = c1 - c2;
    CHECK(c4.get_real() == -2);
    CHECK(c4.get_imag() == -2);

    Complex c5 = c1 * c2;
    CHECK(c5.get_real() == -5);
    CHECK(c5.get_imag() == 10);

    Complex c6 = c1 / c2;
    CHECK(c6.get_real() == 0.44);
    CHECK(c6.get_imag() == 0.08);

    Complex c7 = -c1;
    CHECK(c7.get_real() == -1);
    CHECK(c7.get_imag() == -2);

    c1 += c2;
    CHECK(c1.get_real() == 4);
    CHECK(c1.get_imag() == 6);

    c1 -= c2;
    CHECK(c1.get_real() == 1);
    CHECK(c1.get_imag() == 2);

    c1 *= c2;
    CHECK(c1.get_real() == -5);
    CHECK(c1.get_imag() == 10);

    c1 /= c2;
    CHECK(c1.get_real() == 1);
    CHECK(c1.get_imag() == 2);
    CHECK(c1 == Complex(1, 2));
    CHECK(c1 != Complex(2, 1));
}

TEST_CASE("Test Complex's Comparison Operators"){
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex c3(1, 2);
    Complex c4(0, 0);

    CHECK(c1 == c1);
    CHECK(c1 != c2);
    CHECK(c2 == c2);
    CHECK(c2 != c1);

    CHECK(c1 <= c2);
    CHECK(c1 <= c3);
    CHECK(c1 <= c1);
    CHECK(!(c1 <= c4));

    CHECK(!(c1 >= c2));
    CHECK(c1 >= c3);
    CHECK(c1 >= c1);
    CHECK(c1 >= c4);
    
    CHECK(c1 < c2);
    CHECK(!(c1 < c3));
    CHECK(!(c1 < c1));
    CHECK(!(c1 < c4));
    
    CHECK(!(c1 > c2));
    CHECK(!(c1 > c3));
    CHECK(!(c1 > c1));
    CHECK(c1 > c4);
}
