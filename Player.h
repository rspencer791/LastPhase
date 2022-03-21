#ifndef PLAYER_H
#define PLAYER_H
#include "BST.h"
class Player
{
private:
    BST *inventory;

    bool hasmoved;

public:
    bool inventoryFull()
    {
        if (inventory->numberOfaccessibleKeys() == 3)
            return true;

        return false;
    }

    // hardcode all keys into player's inventory and make them not accesible

    Player()
    {
        dummyptr = new Item(50, "dummy");
        inventory = new BST(dummyptr);
        createInventory(dummyptr);
        hasmoved = false;
    }
    // call this when user leaves room
    void Moved()
    {
        hasmoved = true;
    }

    BST *getInventory()
    {
        return inventory;
    }

    bool returnifhasMoved()
    {
        return hasmoved;
    }
    string returnDescription(int key)
    {
        return inventory->search(key, dummyptr);
    }

    void makeHasMovedFalse()
    {
        hasmoved = false;
    }

    void createInventory(Item *dummyptrX)
    {

        inventory->insert(dummyptrX, 50, "root");
        inventory->insert(dummyptrX, 30, "Piano Key");
        inventory->insert(dummyptrX, 40, "Coffin Key");
        inventory->insert(dummyptrX, 20, "Skull Key");
        inventory->insert(dummyptrX, 10, "Plant Key");
        inventory->insert(dummyptrX, 1, "Lost Key");
        inventory->insert(dummyptrX, 45, "Infinite Key");
        inventory->insert(dummyptrX, 37, "Wrath Key");
        inventory->insert(dummyptrX, 35, "Candle Key");
        inventory->insert(dummyptrX, 38, "Yogurt Key");
        inventory->insert(dummyptrX, 11, "Fortune Key");
        inventory->insert(dummyptrX, 26, "Cloud Key");
        inventory->insert(dummyptrX, 27, "Sky Key");
        inventory->insert(dummyptrX, 41, "Brown Key");
        inventory->insert(dummyptrX, 47, "XXX Key");
        inventory->insert(dummyptrX, 80, "Grey Key");
        inventory->insert(dummyptrX, 75, "Egg Key");
        inventory->insert(dummyptrX, 65, "Dream Key");
        inventory->insert(dummyptrX, 60, "Rock Key");
        inventory->insert(dummyptrX, 67, "Fire Key");
        inventory->insert(dummyptrX, 100, "Water Key");
        inventory->insert(dummyptrX, 78, "Zero Key");
        inventory->insert(dummyptrX, 77, "Mirror Key");
        inventory->insert(dummyptrX, 79, "Air Key");
        inventory->insert(dummyptrX, 87, "Wind Key");
        inventory->insert(dummyptrX, 86, "Unlucky Key");

        //NEW KEYS

        inventory->insert(dummyptrX, 200, "Alex Key");
        inventory->insert(dummyptrX, 210, "Robert Key");
        inventory->insert(dummyptrX, 230, "Marlon Key");
        inventory->insert(dummyptrX, 240, "Dirt Key");
        inventory->insert(dummyptrX, 250, "Window Key");
        inventory->insert(dummyptrX, 260, "Rose Key");
        inventory->insert(dummyptrX, 300, "Turkey Key");
        inventory->insert(dummyptrX, 280, "Monkey Key");
        inventory->insert(dummyptrX, 270, "Donkey Key");
        inventory->insert(dummyptrX, 290, "Key Key");
        inventory->insert(dummyptrX, 310, "Moon Key");
        inventory->insert(dummyptrX, 320, "Sun Key");
        inventory->insert(dummyptrX, 330, "House Key");
        inventory->insert(dummyptrX, 340, "Car Key");
        inventory->insert(dummyptrX, 350, "Omega Key");
        inventory->insert(dummyptrX, 86, "Alpha Key");
        inventory->insert(dummyptrX, 120, "Artifact D");
        inventory->insert(dummyptrX, 110, "Artifact C");
        inventory->insert(dummyptrX, 90, "Artifact B");
        inventory->insert(dummyptrX, 121, "Artifact A");
    }

    Item *dummyptr;

    ~Player()
    {
        delete inventory;
    }

    int numberofAccessibleKeys()
    {
        return inventory->numberOfaccessibleKeys();
    }

    vector<Item *> returnsVectorOfAccessableKeys()
    {
        vector<Item *> dummy;

        inventory->TraverseAndInsertVector(dummyptr, dummy);

        return dummy;
    }
};

#endif
