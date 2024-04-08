//************************************************************************
// ASU CSE310 Assignment #6 Spring 2024
// Author: Nicolas Luthi
// ASU ID: 1260261684
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************
#include "RedBlackTree.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
using namespace std;

// Constructor
RedBlackTree::RedBlackTree()
{
      root = nullptr;
}

// Destructor
RedBlackTree::~RedBlackTree()
{
      int nodeCount = deleteNode(root);
      cout << "The number of nodes deleted: " << nodeCount;
}

// Delete Node
int RedBlackTree::deleteNode(Node *node)
{
      if (node == nullptr)
      { // Base Case
            return 0;
      }

      int leftCount = deleteNode(node->leftChild);   // Delete left subtree
      int rightCount = deleteNode(node->rightChild); // Delete right subtree

      delete node; // Delete node

      return leftCount + rightCount + 1; // Count of nodes deleted
}

// Root Accessor
Node *RedBlackTree::getRoot()
{
      return root; // Return root node
}

// Insert Node
void RedBlackTree::insertNode(Node *newNode)
{
      Node *y = nullptr; // New Node to be inserted
      Node *x = root;    // Current node

      while (x != nullptr)
      {            // While current node is not null
            y = x; // Set new node's parent
            if (newNode->vin < x->vin)
            {                       // If new node is less than current node
                  x = x->leftChild; // new Node is left child of current node
            }
            else
            {
                  x = x->rightChild; // new Node is right child of current node
            }
      }

      newNode->parent = y; // Set new node's parent
      if (y == nullptr)
      {                     // If root is null
            root = newNode; // Set root to new node
      }
      else if (newNode->vin < y->vin)
      {                             // if new node is less than current node
            y->leftChild = newNode; // Set new node as left child of current node
      }
      else
      {
            y->rightChild = newNode; // Set new node as right hcild of current node
      }

      newNode->color = "RED"; // newly inserted node is always RED
      fixUp(newNode);         // Fix the tree to keep RBT properties
}

// Fix Tree to keep RBT Properties
void RedBlackTree::fixUp(Node *node)
{
      Node *parent = nullptr;
      while (node != root && node->color == "RED" && node->parent->color == "RED") // node and its parent are both red
      { 
            parent = node->parent->parent;            // Get the grandparent of node
            if (node->parent == parent->leftChild)    // Case 1: Node's parent is a left child
            {
                  Node *uncle = parent->rightChild;               // Get the uncle node
                  if (uncle != nullptr && uncle->color == "RED")  // Case 1.1 - Uncle is also red (Recolor)
                  {
                        node->parent->color = "BLACK";  // Recolor parent
                        uncle->color = "BLACK";         // Recolor Uncle
                        parent->color = "RED";          // Recolor grandparent
                        node = parent;                  // move current node to grandparent for next step
                  }
                  else        // Case 2: Node's Uncle is black (Rotate)
                  {
                        if (node == node->parent->rightChild) // Case 2.1: Node is a right child
                        {
                              node = node->parent;
                              leftRotate(node);             // Left Rotate
                        }
                        node->parent->color = "BLACK";      // Case 2.2: Node is a left child
                        parent->color = "RED";
                        rightRotate(parent);                // Right rotate
                  }
            }
            else        // Case 3: Node's parent is a right child 
            {
                  Node *uncle = parent->leftChild;
                  if (uncle != nullptr && uncle->color == "RED")
                  {
                        // Case 1: Parent and Uncle are both RED
                        node->parent->color = "BLACK";
                        uncle->color = "BLACK";
                        parent->color = "RED";
                        node = parent;
                  }
                  else
                  {
                        if (node == node->parent->leftChild)
                        {
                              //Node is a left child
                              node = node->parent;
                              rightRotate(node);
                        }
                        
                        node->parent->color = "BLACK";
                        parent->color = "RED";
                        leftRotate(parent);
                  }
            }
      }
      root->color = "BLACK";        // Always make the root node black
}

// Preorder traversal
void RedBlackTree::preOrderTraversal(Node *node)     
{
      if (node == nullptr)
            return;
      print(node);                              // Recursively print node -> left child -> right child
      preOrderTraversal(node->leftChild);       
      preOrderTraversal(node->rightChild);
}

// Inorder traversal
void RedBlackTree::inorderTraversal(Node *node)
{
      if (node == nullptr)
            return;
      inorderTraversal(node->leftChild);        // Recursively print left -> node child -> right child
      print(node);
      inorderTraversal(node->rightChild);
}

// Postorder traversal
void RedBlackTree::postOrderTraversal(Node *node)
{
      if (node == nullptr)
            return;
      postOrderTraversal(node->leftChild);        // Recursively print left -> right child -> node child
      postOrderTraversal(node->rightChild);
      print(node);
}

// Minimum Given Node
Node *RedBlackTree::findMinimumNode(Node *node)
{
      if (node == nullptr || node->leftChild == nullptr)
      {
            return node;
      }
      else
      {
            return findMinimumNode(node->leftChild);
      }
}

// Find Max given NODE
Node *RedBlackTree::findMaximumNode(Node *node)
{
      if (node == nullptr || node->rightChild == nullptr)
      {
            return node;
      }
      else
      {
            return findMaximumNode(node->rightChild);
      }
}

// Search Tree given key
Node *RedBlackTree::treeSearch(int vin, string model, string make)
{
      Node *current = root;
      while (current != nullptr)
      {     // Check current node before moving on 
            if (current->vin == vin && current->model == model && current->make == make) 
            {
                  return current;
            } // it was not current so go to left child and check that node
            else if (current->vin > vin || (current->vin == vin && (current->model > model || (current->model == model && current->make > make))))
            {
                  current = current->leftChild;
            } // was not the left child so go to right child and check it
            else
            {
                  current = current->rightChild;
            }
      }
      return nullptr; // Node not found
}

// Left Rotate
void RedBlackTree::leftRotate(Node *x)
{
      Node *y = x->rightChild;            // assign y to x's right child
      x->rightChild = y->leftChild;       // Turn left subtree of y into x's right subtree
      if (y->leftChild != nullptr)
      {
            y->leftChild->parent = x;     // Set parent of y's left child to x if it has one
      }
      y->parent = x->parent;              // make x's old parent y's parent
      if (x->parent == nullptr)           // if it was a root then y is the new root
      {
            this->root = y;
      }
      else if (x == x->parent->leftChild) // If x was a left child
      {
            x->parent->leftChild = y;     // y is left child of x's parent
      }
      else                                // if x was a right child
      {
            x->parent->rightChild = y;    // set y as the right child of x's parent 
      }
      y->leftChild = x;             // put x as y's left child
      x->parent = y;                // set x's parent to y
}

// Right Rotate at Node
void RedBlackTree::rightRotate(Node *x)
{
      Node *y = x->leftChild;             // assign y to x's left child
      x->leftChild = y->rightChild;       // Turn right subtree of y into x's left subtree
      if (y->rightChild != nullptr)       
      {
            y->rightChild->parent = x;     // Set parent of y's right child to x if it has one
      }
      y->parent = x->parent;              // make x's old parent y's parent
      if (x->parent == nullptr)           // if it was a root then y is the new root
      {
            this->root = y;
      }
      else if (x == x->parent->rightChild)      // If x was a right child
      {
            x->parent->rightChild = y;    // set y as the right child of x's parent 
      }
      else                                      // If x was a left child
      {
            x->parent->leftChild = y;     // set y as the left child of x's parent 
      }
      y->rightChild = x;            // set x as y's right child
      x->parent = y;                // set x's parent to y
}

// Predecessor given Node
Node *RedBlackTree::findPredecessorNode(Node *node)
{
      if (node->leftChild != nullptr)
            return findMaximumNode(node->leftChild);

      Node *y = node->parent;
      while (y != nullptr && node == y->leftChild)
      {
            node = y;
            y = y->parent;
      }
      return y;
}

// Successor Given Node
Node *RedBlackTree::findSuccessorNode(Node *node)
{
      if (node->rightChild != nullptr)
            return findMinimumNode(node->rightChild);

      Node *y = node->parent;
      while (y != nullptr && node == y->rightChild)
      {
            node = y;
            y = y->parent;
      }
      return y;
}

// Minimum of a RBT
void RedBlackTree::treeMinimum()
{
      Node *minNode = findMinimumNode(root);          // start at root to find min
      if (minNode != nullptr)
      {
            print(minNode);                     // root was not null so look for min
      }
      else
      {
            cout << "Tree is empty. No Minimum." << endl;         // root is null so stop looking
      }
}

// Max of Entire RBT
void RedBlackTree::treeMaximum()
{
      Node *maxNode = findMaximumNode(root);    // Start at the root
      if (maxNode != nullptr)
      {
            print(maxNode);         // if root is not null find maxNode
      }
      else
      {
            cout << "Tree is empty. No Maximum." << endl;         // if root is null then stop looking
      }
}

// Predecessor of Entire Tree
// Same process as successor just looking for next smallest
void RedBlackTree::treePredecessor(int vin, string model, string make)
{
      Node *node = treeSearch(vin, model, make);
      if (node == nullptr)
      {
            cout << "The car with VIN " << vin << ", Model " << model << ", and Make " << make << " is NOT FOUND." << endl;
      }
      else
      {
            Node *predecessor = findPredecessorNode(node);
            if (predecessor != nullptr)
            {
                  cout << "Command: tree_predecessor" << endl;
                  cout << vin << " " << model << " " << make << " is FOUND." << endl;
                  cout << "Its Predecessor is:" << endl;
                  print(predecessor);
            }
            else
            {
                  cout << "Command: tree_predecessor" << endl;
                  cout << vin << " " << model << " " << make << " is FOUND." << endl;
            }
      }
}

// Successor of Entire Tree
void RedBlackTree::treeSucessor(int vin, string model, string make)
{
      Node *node = treeSearch(vin, model, make);    // Given key look for node in tree
      if (node == nullptr)    // Node is null so Not Found
      {
            cout << "The car with VIN " << vin << ", Model " << model << ", and Make " << make << " is NOT FOUND." << endl;
      }
      else
      {
            Node *successor = findSuccessorNode(node);      // Node was found so look for successor
            if (successor != nullptr)                       // If the successor is not Null print it out
            {
                  cout << "Command: tree_successor" << endl;
                  cout << vin << " " << model << " " << make << " is FOUND." << endl;
                  cout << "Its Successor is:" << endl;
                  print(successor);
            }
            else  // If the successor is null then print that it does not exist
            {
                  cout << "Command: tree_successor" << endl;
                  cout << vin << " " << model << " " << make << " is FOUND." << endl;
                  cout << "Its Successor does NOT EXIST." << endl;
            }
      }
}

// Insert Given Key
void RedBlackTree::treeInsert(int vin, string model, string make, double price)
{
      Node *newNode = new Node;
      newNode->vin = vin;
      newNode->model = model;
      newNode->make = make;
      newNode->price = price;
      newNode->leftChild = nullptr;
      newNode->rightChild = nullptr;
      newNode->parent = nullptr;
      newNode->color = "RED";  

      
      insertNode(newNode);    // Insert the node as a regular BST would be inserted
      fixUp(newNode);         // Call fixup from newNode to maintain RB tree properties
}

// Print Function Given
void RedBlackTree::print(Node *node)
{
      cout << left;
      cout << setw(8) << node->vin
           << setw(12) << node->model
           << setw(12) << node->make
           << setw(10) << fixed << setprecision(2) << node->price;
      cout << right << setw(7) << node->color << endl;
}

// Compare two Nodes
int RedBlackTree::compareNodes(Node *node1, string key2)
{
      string key1 = to_string(node1->vin) + node1->model + node1->make; // Simple string comparison
      if (key1 < key2)
      {
            return -1;
      }
      else if (key1 > key2)
      {
            return 1;
      }
      else
      {
            return 0;
      }
}