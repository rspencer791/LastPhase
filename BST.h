#ifndef BINARYTREE
#define BINARYTREE
#include <vector>
#include "Item.h"
class BST
{
private:
    int size; // contains size of BST

    Item *root; // contains pointer to root of BST

    void destroy(Item *ptr) // deallocates memory of all nodes in BST
    {
        if (ptr)
        {
            destroy(ptr->left);
            destroy(ptr->right);
            delete ptr;
        }
    }

public:
    string search(int key, Item *rootA) // searches key in BST, returns description of key
    {

        if (rootA == nullptr)
        {

            return "\nkey not found\n";
        }

        if (rootA->getKey() == key)
        {
            return rootA->getDescription();
        }

        if (key < rootA->getKey())
        {
            return search(key, rootA->left);
        }

        return search(key, rootA->right);
    }

    Item *searchAndReturnNodePointer(int key, Item *rootA) // searches key and returns pointer to node containing key
    {

        if (rootA == nullptr)
        {

            return nullptr;
        }

        if (rootA->getKey() == key)
        {
            return rootA;
        }

        if (key < rootA->getKey())
        {
            return searchAndReturnNodePointer(key, rootA->left);
        }

        return searchAndReturnNodePointer(key, rootA->right);
    }

    void traverse(Item *x, int &n) // post order traversal of nodes to get number of accessable keys
    {
        if (x)
        {
            traverse(x->left, n);
            traverse(x->right, n);
            if (x->Accessable())
            {
                n++;
            }
        }
    }

    BST(Item *x) // constructor, takes in a node pointer and makes it the root. size = 1 because of the root
    {
        size = 1;
        root = x;
    }

    Item *insert(Item *rootX, int k, string d) // inserts new item into the BST
    {
        if (!rootX)
        {
            size++;
            return new Item(k, d);
        }
        if (k < rootX->getKey())

            rootX->left = insert(rootX->left, k, d);

        else
            rootX->right = insert(rootX->right, k, d);

        return rootX;
    }
    ~BST() // destructor
    {
        destroy(root);
    }

    int getSize()
    {
        return size;
    }

    int numberOfaccessibleKeys() // returns the number of keys that are accessable
    {
        int x = 0;

        Item *dummy = root;

        traverse(dummy, x);

        return x;
    }

    void TraverseAndInsertVector(Item *p, vector<Item *> &x)
    {

        if (p)
        {
            TraverseAndInsertVector(p->left, x);
            TraverseAndInsertVector(p->right, x);
            if (p->Accessable())
            {
                x.push_back(p);
            }
        }
    }
};

#endif
