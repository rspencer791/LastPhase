#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
class Item
{
public:
    Item *left;

    Item *right;

    Item(int k, string d)
    {
        key = k;

        isAccessible = false; // will turn accessible in player inventory once player finds item

        description = d;

        left = nullptr;

        right = nullptr;
    }

    string getDescription() // returns descriptiom of key
    {
        return description;
    }

    int getKey() // return key
    {
        return key;
    }

    void makeInAccessable()
    {
        isAccessible = false;
    }

    void setKey(int k)
    {
        key = k;
    }

    void makeAccessable()
    {
        isAccessible = true;
    }

    bool Accessable()
    {
        if (isAccessible)
        {
            return true;
        }

        return false;
    }

private:
    int key; // key<100 means it's a key. key>100 means its an artifact
    string description;
    bool isAccessible; // default value is false
};

#endif
