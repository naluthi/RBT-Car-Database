//************************************************************************
// ASU CSE310 Assignment #6 Spring 2024
// Author: Nicolas Luthi
// ASU ID: 1260261684
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
using namespace std;

// This function used to get the key of a Car which is the combination of vin, model & make
void getCarKey(string oneLine, int &vin, string &model, string &make);

// This function used to get all info. of a Car
void getCarInfo(string oneLine, int &vin, string &model, string &make, double &price);

int main()
{

   int vin;
   string model, make;
   double price;
   string command, oneLine, token;
   string delimiter = ",";

   int pos = 0;

   RedBlackTree rbt; // Create an instance of the RedBlackTree object
    do
   {
      getline(cin, oneLine);
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      command = token;
      oneLine.erase(0, pos + delimiter.length());

      if(command.compare("quit")==0)
      {
         cout << "\nCommand: quit" << endl;
         break;
      }

      // Pre-order traversal
      else if(command.compare("tree_preorder")==0)
      {
         cout << "\nCommand: tree_preorder" << endl;
         rbt.preOrderTraversal(rbt.getRoot());        // call the appropriate function
      }


      // In-order traversal
      else if(command.compare("tree_inorder")==0)
      {
         cout << "\nCommand: tree_inorder" << endl;
         rbt.inorderTraversal(rbt.getRoot());        // call the appropriate function
      }


      // Post-order traversal
      else if(command.compare("tree_postorder")==0)
      {
         cout << "\nCommand: tree_postorder" << endl;
         rbt.postOrderTraversal(rbt.getRoot());        // call the appropriate function
      }


      // Find the minimum of the entire RBT Tree
      else if(command.compare("tree_minimum")==0)
      {
         cout << "\nCommand: tree_minimum" << endl;
         Node *minNode = rbt.findMinimumNode(rbt.getRoot());   // find minimum given a node (root node)
         if (minNode != nullptr)                               // if minNode is not null
         {
            cout << "The MINIMUM is:" << endl;
            rbt.print(minNode);                             
         }
         else
         {
            cout << "Tree is empty. No Minimum." << endl;
         }
      }


      // Find the maximum of the entire RBT Tree
      else if(command.compare("tree_maximum")==0)
      {
         cout << "\nCommand: tree_maximum" << endl;
         Node *maxNode = rbt.findMaximumNode(rbt.getRoot()); // find maximum given a node (root node)
         if (maxNode != nullptr)                            // if maxNode is not null
         {
            cout << "The MAXIMUM is:" << endl;
            rbt.print(maxNode);                             // print the node
         }
         else
         {
            cout << "Tree is empty. No Maximum." << endl;  // if tree is empty
         }
      }


      // Find the Predecessor of a given node
      else if(command.compare("tree_predecessor")==0)
      {
         getCarKey(oneLine, vin, model, make);              // get the key of the node
         cout << "\nCommand: tree_predecessor" << endl;
         Node *node = rbt.treeSearch(vin, model, make);     // find the node given the key
         if (node != nullptr)
         {
            Node *predecessor = rbt.findPredecessorNode(node);    // find the predecessor given the node
            if (predecessor != nullptr)                           // if predecessor exists
            {
               getCarInfo(oneLine, vin, model, make, price);      // get all info. of the node
               cout << left;
               cout << setw(8) << vin
                    << setw(12) << model
                    << setw(12) << make
                    << setw(10) << " is FOUND." << endl;          // Print that node was succesfully found
               cout << "Its Predecessor is: " << endl;            // Print Predecessor car info and key
               rbt.print(predecessor);
            }
            else
            {
               getCarInfo(oneLine, vin, model, make, price);      // else if predecessor does not exist

               cout << left
                    << setw(8) << vin
                    << setw(12) << model
                    << setw(12) << make
                    << setw(10) << " is FOUND." << endl;          // print that node was succesfully found
               cout << "Its Predecessor does NOT EXIST" << endl;  // print that the Predecesoor of the given node does not exist
            }
         }
         else
         {
            cout << "Node not found." << endl;              // given node was not found
         }
      }


      // Find the Successor of a given node
      else if(command.compare("tree_successor")==0)
      {
         getCarKey(oneLine, vin, model, make);              // get the key of the node
         cout << "\nCommand: tree_successor" << endl;
         Node *node = rbt.treeSearch(vin, model, make);     // find the node given the key
         if (node != nullptr)                               // if node exists
         {
            Node *successor = rbt.findSuccessorNode(node);  // find the successor given the node

            if (successor != nullptr)                             // if successor exists but node was found
            {
               getCarInfo(oneLine, vin, model, make, price);
               cout << left
                    << setw(8) << vin
                    << setw(12) << model
                    << setw(12) << make
                    << setw(10) << " is FOUND." << endl;         // print that node was succesfully found
               cout << "Its Successor is: " << endl;              // print that the Successor of the given node does not exist
               rbt.print(successor);
            }
            else
            {
               getCarInfo(oneLine, vin, model, make, price);            // if the nod was found but successor does not exist
               cout << left
                    << setw(8) << vin
                    << setw(12) << model
                    << setw(12) << make;
               cout << " is FOUND." << endl;          // print that node was succesfully found
               cout << "Its Successor does NOT EXIST" << endl;    //  print that the Successor of the given node does not exist
            }
         }
         else
         {
            cout << "Node not found." << endl;              // Given node does not exist
         }
      }


      // Find a given node in the RBT Tree
      else if(command.compare("tree_search")==0)
      {
         getCarKey(oneLine, vin, model, make);              // get the key of the node
          cout << "\nCommand: tree_search" << endl;
         Node *result = rbt.treeSearch(vin, model, make);   // find the node given the key
         if (result != nullptr)                             // if node exists
         {
            getCarInfo(oneLine, vin, model, make, price);   // get all info of the node
            cout << left;
            cout << setw(8)  << vin
                 << setw(12) << model
                 << setw(12) << make;
            cout << " is FOUND." << endl;       // print that node was succesfully found
         }
         else
         {
            getCarInfo(oneLine, vin, model, make, price);
            cout << left;
            cout << setw(8)  << vin
                 << setw(12) << model
                 << setw(12) << make;
            cout << " is NOT FOUND." << endl;         // same as above but not was not found
         }
      }


      // Insert a new node into the RBT Tree
      else if(command.compare("tree_insert")==0)
      {
         getCarInfo(oneLine, vin, model, make, price);            // get all info of the node
         cout << "\nCommand: tree_insert" << endl;
         cout << left;
         cout << setw(8)  << vin
              << setw(12) << model
              << setw(12) << make
              << setw(10) << fixed << setprecision(2) << price << endl;      // Print out the car info
         rbt.treeInsert(vin, model, make, price);                             // insert the node into the tree
      }
   } while (true);            // continue until 'quit'
   return 0;
}

//*********************************************************************************
// This function from one line, extracts the vin, model, make of a Car.
// You should already know how to extract tokens from Assignment5.cpp file
void getCarKey(string oneLine, int &vin, string &model, string &make)
{
   stringstream ss(oneLine);
   string item;
   getline(ss, item, ',');
   vin = stoi(item);
   getline(ss, model, ',');
   getline(ss, make, ',');
}

//************************************************************************************************
// This function from one line, extract tokens and get all info. of a Car
void getCarInfo(string oneLine, int &vin, string &model, string &make, double &price)
{
   stringstream ss(oneLine);
   string item;
   getline(ss, item, ',');
   vin = stoi(item);
   getline(ss, model, ',');
   getline(ss, make, ',');
   getline(ss, item, ',');
   price = stod(item);
}
