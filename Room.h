#ifndef ROOM_H
#define ROOM_H
#include "BST.h"
#include "Player.h"
#include "gameObject.h"
class Room
{

protected:
    
    void ignoreLine()
    {
        cin.clear();
        cin.ignore();
    }

    // object representation                // contains description of keys and their key values. Holds acessible keys
    vector<Item *> storage;                      // contains players inventory
 
    vector<gameObject> actualObjectDescriptions; // a vector of game objects.
    vector<bool> doors;                          // 0 = N, 1 = S, 2 = E, 3 = W if door is open then true, false otherwise
    string thisRoom;                             // contains beginning state
    int room_ID_of_destination;                  // contains end state
    bool hasLeft;                                // contains if player has left

    virtual void initKeys(Player *ptr) = 0;               // puts integer values of keys into vector of integers
    virtual void Attempt2open(int choice, Player *u) = 0; // attempts to open door

    // virtual void transferPlayerInventory(Player *player) = 0; this may not be needed

    // virtual void updateStorage() = 0; //for when user leaves and comes back. May not be necessary

    virtual void initDoors() = 0; // sets doors to open or closed
    
    int inputCheck(int maxValue, int value2bChecked)
    {
        
        if (value2bChecked<=maxValue && value2bChecked >0)
        {
            return value2bChecked;
        }
        else
        {
            while (value2bChecked<=0 || value2bChecked>maxValue || cin.fail())
            {
                ignoreLine();
                
                cout<<endl<<"Entry invalid. Please enter a correct value:"<<endl;
                cin>>value2bChecked;
            }
            
        }
        return value2bChecked;
    }

public:
    virtual void investigate(Player *player) = 0;
    virtual void outputRoomName() = 0;
    virtual void inputItemsintoGameObjects(Player *player, char X) = 0;
    virtual void InputPrompt(Player *player, char X) = 0;

    virtual void Combine(Player *player) = 0;

    void displayObjects()
    {
        cout << "\nThe objects in this room are:\n";

        for (int i = 1; i < actualObjectDescriptions.size()+1; i++)
        {
            cout << i << "." << actualObjectDescriptions.at(i-1).getDescription();
            cout << endl;
        }
    }

    string thisRoomX()
    {
        return thisRoom;
    }

    virtual int returnroom_ID_of_destination()
    {
        return room_ID_of_destination;
    }
    virtual void displayDoors(Player *user) = 0;

    void reinithasMoved(Player *p)
    {
        p->makeHasMovedFalse();
    }

    void ReinithasLeft()
    {
        hasLeft = false;
    }

    bool hasLeftX()
    {
        return hasLeft;
    }

    void updateAndDisplayInventory(Player *player)
    {
        cout << "\nYour inventory now contains:\n";

        vector<Item *> keysinInventory = player->returnsVectorOfAccessableKeys();

        for (int i = 0; i < keysinInventory.size(); i++)
        {
            cout << keysinInventory.at(i)->getDescription() << endl;
        }
    }
};

#endif
