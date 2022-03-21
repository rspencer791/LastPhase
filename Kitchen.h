#ifndef KITCH
#define KITCH
#include "Player.h"
#include "Room.h"
class Kitchen : public Room
{
private:
    vector<Item *> pantry;
    vector<Item *> oven;
    vector<Item *> cupboard;

    Item *pickKey(Player *p)
    {
        int choice;

        int numA = p->getInventory()->numberOfaccessibleKeys();

        vector<Item *> dummy = p->returnsVectorOfAccessableKeys();

        if (numA == 0)
        {
            cout << "\nYou have no keys!\n";
            return nullptr;
        }
        else
        {
            cout << "\nWhich key would you like to attempt to open the door with?\n";

            for (int i = 1; i < dummy.size()+1; i++)
            {

                cout << i << "." << dummy.at(i-1)->getDescription() << endl;
            }

            cin >> choice;

            choice = inputCheck(dummy.size(), choice);

            choice = choice - 1;

            return dummy.at(choice);
        }
    }

public:
    Kitchen(Player *player)
    {

        initKeys(player);

        initDoors();

        thisRoom = "kitchen";

        initObjects();

        hasLeft = false;
    }

    void outputRoomName()
    {
        cout << "\nYou are in the kitchen.\nYou see a pantry, an oven, and a cupboard.\n";
    }

    void initObjects()
    {
        gameObject pantry("pantry");

        actualObjectDescriptions.push_back(pantry);

        gameObject oven("oven");

        actualObjectDescriptions.push_back(oven);

        gameObject cupboard("cupboard");

        actualObjectDescriptions.push_back(cupboard);
    }

    void initKeys(Player *ptr)
    { // pantry

        BST *temp = ptr->getInventory();
        Item *itemA = ptr->dummyptr;

        pantry.push_back(temp->searchAndReturnNodePointer(1, itemA));

        pantry.push_back(temp->searchAndReturnNodePointer(45, itemA));

        pantry.push_back(temp->searchAndReturnNodePointer(37, itemA));

        // oven

        oven.push_back(temp->searchAndReturnNodePointer(35, itemA));

        oven.push_back(temp->searchAndReturnNodePointer(38, itemA));

        oven.push_back(temp->searchAndReturnNodePointer(11, itemA));

        // cupboard

        cupboard.push_back(temp->searchAndReturnNodePointer(26, itemA));

        cupboard.push_back(temp->searchAndReturnNodePointer(27, itemA));

        cupboard.push_back(temp->searchAndReturnNodePointer(41, itemA));
    }

    void investigate(Player *player)
    {
        int choice;
        int take;
        int XXX;

        char Z;
        cout << "\nWhich would you like to do? Enter item number\n";

        cin >> choice;
        choice = inputCheck(3, choice);
        cout << endl
             << actualObjectDescriptions.at(choice - 1).getDescription() << " has :\n";

        if (choice == 1)
        {
            for (int i = 0; i < pantry.size(); i++)
            {
                cout << pantry.at(i)->getDescription();
                cout << endl;
            }
            Z = 'p';
        }
        else if (choice == 2)
        {
            for (int i = 0; i < oven.size(); i++)
            {
                cout << oven.at(i)->getDescription();
                cout << endl;
            }

            Z = 'o';
        }
        else
        {
            for (int i = 0; i < cupboard.size(); i++)
            {
                cout << cupboard.at(i)->getDescription();
                cout << endl;
            }
            Z = 'c';
        }

        cout << "\nSelect an action:\n";
        cout << "1.Insert items\n";
        cout << "2.Extract items\n";
        cout << "3.Close chest\n";
        cin >> XXX;

        XXX = inputCheck(3, XXX);


        while (XXX != 3)
        {

            if (XXX == 3)
            {
                cout << "\nOkay!\n";

                return;
            }

            else if (XXX == 2)
            {
                cout << "\nEnter the number of the item to take\n";

                if (!player->inventoryFull())
                {
                    cout << actualObjectDescriptions.at(choice-1).getDescription() << " has:\n";

                    if (choice == 1 && pantry.size() != 0)
                    {
                        for (int i = 1; i < pantry.size()+1; i++)
                        {
                            cout << i << "." << pantry.at(i-1)->getDescription() << endl;
                        }
                    }
                    else if (choice == 2 && oven.size() != 0)
                    {

                        for (int i = 1; i < oven.size()+1; i++)
                        {
                            cout << i << "." << oven.at(i-1)->getDescription() << endl;
                        }
                    }
                    else if (choice == 3 && cupboard.size() != 0)
                    {
                        for (int i = 1; i < cupboard.size()+1; i++)
                        {
                            cout << i << "." << cupboard.at(i-1)->getDescription() << endl;
                        }
                    }

                    else
                    {
                        cout << "Object is empty!" << endl;
                        return;
                    }

                    cin >> take;
                    if (choice==1)
                    take = inputCheck(pantry.size(), take);
                    else if (choice==2)
                        take = inputCheck(oven.size(), take);
                    else
                        take = inputCheck(cupboard.size(), take);
                    take = take - 1;

                    if (choice == 1)
                    {
                        if (take != 100 && take < pantry.size() && take >= 0)
                        {
                            Take(pantry.at(take), player);
                            pantry.erase(pantry.begin() + take);
                        }
                    }
                    else if (choice == 2)
                    {
                        if (take != 100 && take < oven.size() && take >= 0)
                        {
                            Take(oven.at(take), player);
                            oven.erase(oven.begin() + take);
                        }
                    }
                    else

                    {
                        if (take != 100 && take < cupboard.size() && take >= 0)
                        {
                            Take(cupboard.at(take), player);
                            cupboard.erase(cupboard.begin() + take);
                        }
                    }
                }
                else
                    cout << "\nStorage is full!\n";
            }

            else
            {
                int numAccessable = player->numberofAccessibleKeys();

                if (numAccessable == 0)
                {
                    cout << "\nInventory is empty\n ";
                }
                else if (Z == 'c' && cupboard.size() == 4)
                {
                    cout << "\nCupboard is full\n";
                }
                else if (Z == 'o' && oven.size() == 4)
                {
                    cout << "\nOven is full\n";
                }
                else if (Z == 'p' && pantry.size() == 4)
                {
                    cout << "\nPantry is full\n";
                }

                else

                    InputPrompt(player, Z);
            }

            cout << "\nSelect an action:\n";
            cout << "1.Insert items\n";
            cout << "2.Extract items\n";
            cout << "3.Close chest\n";
            cin >> XXX;
            XXX = inputCheck(3, XXX);

        }
    }

    void
    Take(Item *key, Player *player) // take key from object
    {
        key->makeAccessable();

        cout << "\nYou have taken the object!\n";

        updateAndDisplayInventory(player);
    }

    void Attempt2open(int choice, Player *p)
    {
        if (choice == 1 && !doors.at(1))
        {
            Item *attemptkey = pickKey(p);

            if (attemptkey->getKey() == 75)
            {
                cout << "\nThe door has been opened!\n";
                doors.at(0) = true; // open door
                p->Moved();
                room_ID_of_destination = -1;
            }
            else
            {
                cout << "\nThat is the wrong key!\n";
                return;
            }

            if (choice == 0)
            {
                cout << "\nThe door has been opened!\n";

                room_ID_of_destination = -1;

                hasLeft = true;
            }
        }
        // TODO: the rest of the doors once they're created
    }
    void initDoors()
    {
        doors.push_back(true); // south door is already empty
        doors.push_back(false);
    }

    void displayDoors(Player *user)
    {
        int choice;
        int choiceB;
        cout << "\nWhich door would you like to investigate:\n1.StartRoom Door\n2.ClosetA Door\n";

        cin >> choice;

        choice = inputCheck(2, choice);

        choice = choice - 1;

        if (doors.at(choice))
        {
            cout << "\nThe door is open and you pass through.\n";
            user->Moved(); // set moved to true
            if (choice == 0)
                room_ID_of_destination = -1;
            else
                room_ID_of_destination = -5;

            hasLeft = true;
        }
        else
        {
            cout << "\nThe door is locked. Attempt to open it?\n1.Yes\n2.No\n";
            cin >> choiceB;

            choiceB = inputCheck(2, choiceB);

            Attempt2open(choiceB, user);
        }
    }

    void InputPrompt(Player *player, char X)
    {

        inputItemsintoGameObjects(player, X);
    }

    void inputItemsintoGameObjects(Player *player, char X) // from inventory to object
    {
        int index;

        cout << "\nWhich item in your inventory would you like to insert?\nEnter number\n";

        vector<Item *> d = player->returnsVectorOfAccessableKeys();

        for (int i = 1; i < d.size()+1; i++)
        {
            cout << i << "." << d.at(i-1)->getDescription() << endl;
        }

        cin >> index;

        index = inputCheck(d.size(), index);

        index = index - 1;

        d.at(index)->makeInAccessable(); // player cant use key anymore

        if (X == 'o' && oven.size() <= 4)
        {
            oven.push_back(d.at(index));
        }
        else if (X == 'p' && pantry.size() <= 4)
        {
            pantry.push_back(d.at(index));
        }
        else if (X == 'c' && cupboard.size() <= 4)
            cupboard.push_back(d.at(index));

        cout << "\nItem is no longer in inventory\n";

        updateAndDisplayInventory(player);
    }

    void Combine(Player *player)
    {
        int choice;

        cout << "\nWould you like to investigate doors or objects?\n1.Objects\n2.Doors\n";

        cin >> choice;

        choice = inputCheck(2, choice);


        if (choice == 1)
        {
            displayObjects();
            investigate(player);
        }
        else
        {
            displayDoors(player);
        }
    }
};

#endif
