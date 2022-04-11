#ifndef BASEMENT
#define BASEMENT
#include "Player.h"
#include "Room.h"
class Basement : public Room
{
private:
    vector<Item *> Coffin;
    vector<Item *> Hamper;
    vector<Item *> Toolbox;
    vector<Item *> closet;

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
    Basement(Player *player)
    {

        initKeys(player);

        initDoors();

        thisRoom = "Basement";

        initObjects();

        hasLeft = false;
    }

    void outputRoomName()
    {
        cout << "\nYou are in the Basement.\nYou see a Coffin, an Hamper, and a Toolbox.\n";
    }

    void initObjects()
    {
        gameObject Coffin("Coffin");

        actualObjectDescriptions.push_back(Coffin);

        gameObject Hamper("Hamper");

        actualObjectDescriptions.push_back(Hamper);

        gameObject Toolbox("Toolbox");

        actualObjectDescriptions.push_back(Toolbox);
    }

    void initKeys(Player *ptr)
    { // Coffin

        BST *temp = ptr->getInventory();
        Item *itemA = ptr->dummyptr;

        Coffin.push_back(temp->searchAndReturnNodePointer(47, itemA));

        Coffin.push_back(temp->searchAndReturnNodePointer(80, itemA));

        Coffin.push_back(temp->searchAndReturnNodePointer(75, itemA));

        // Hamper

        Hamper.push_back(temp->searchAndReturnNodePointer(65, itemA));

        Hamper.push_back(temp->searchAndReturnNodePointer(60, itemA));

        Hamper.push_back(temp->searchAndReturnNodePointer(67, itemA));

        // Toolbox

        Toolbox.push_back(temp->searchAndReturnNodePointer(100, itemA));

        Toolbox.push_back(temp->searchAndReturnNodePointer(78, itemA));

        Toolbox.push_back(temp->searchAndReturnNodePointer(77, itemA));

        // Closet

        closet.push_back(temp->searchAndReturnNodePointer(90, itemA));
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
            for (int i = 0; i < Coffin.size(); i++)
            {
                cout << Coffin.at(i)->getDescription();
                cout << endl;
            }
            Z = 'p';
        }
        else if (choice == 2)
        {
            for (int i = 0; i < Hamper.size(); i++)
            {
                cout << Hamper.at(i)->getDescription();
                cout << endl;
            }

            Z = 'o';
        }
        else
        {
            for (int i = 0; i < Toolbox.size(); i++)
            {
                cout << Toolbox.at(i)->getDescription();
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

                    if (choice == 1 && Coffin.size() != 0)
                    {
                        for (int i = 1; i < Coffin.size()+1; i++)
                        {
                            cout << i << "." << Coffin.at(i-1)->getDescription() << endl;
                        }
                    }
                    else if (choice == 2 && Hamper.size() != 0)
                    {

                        for (int i = 1; i < Hamper.size()+1; i++)
                        {
                            cout << i << "." << Hamper.at(i-1)->getDescription() << endl;
                        }
                    }
                    else if (choice == 3 && Toolbox.size() != 0)
                    {
                        for (int i = 1; i < Toolbox.size()+1; i++)
                        {
                            cout << i << "." << Toolbox.at(i-1)->getDescription() << endl;
                        }
                    }

                    else
                    {
                        cout << "Object is empty!" << endl;
                        return;
                    }

                    cin >> take;
                    if (choice==1)
                    take = inputCheck(Coffin.size(), take);
                    else if (choice==2)
                        take = inputCheck(Hamper.size(), take);
                    else
                        take = inputCheck(Toolbox.size(), take);

                    take = take - 1;

                    if (choice == 1)
                    {
                        if (take != 100 && take < Coffin.size() && take >= 0)
                        {
                            Take(Coffin.at(take), player);
                            Coffin.erase(Coffin.begin() + take);
                        }
                    }
                    else if (choice == 2)
                    {
                        if (take != 100 && take < Hamper.size() && take >= 0)
                        {
                            Take(Hamper.at(take), player);
                            Hamper.erase(Hamper.begin() + take);
                        }
                    }
                    else

                    {
                        if (take != 100 && take < Toolbox.size() && take >= 0)
                        {
                            Take(Toolbox.at(take), player);
                            Toolbox.erase(Toolbox.begin() + take);
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
                else if (Z == 'c' && Toolbox.size() == 4)
                {
                    cout << "\nToolbox is full\n";
                }
                else if (Z == 'o' && Hamper.size() == 4)
                {
                    cout << "\nHamper is full\n";
                }
                else if (Z == 'p' && Coffin.size() == 4)
                {
                    cout << "\nCoffin is full\n";
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

            if (attemptkey->getKey() == 100) // 100 = water key; might have to change later
            {
                cout << "\nThe door has been opened!\n";
                doors.at(1) = true; // open door
                attemptkey->makeInAccessable();
                closetprompt(p);
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
        cout << "\nWhich door would you like to investigate:\n1.StartRoom Door\n2.ClosetB Door\n";

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
            cout << "Pretend this is a thought provoking riddle :D! (water key needed if closet)";// need riddle if closet
            cout << "\nThe door is locked. Attempt to open it?\n1.Yes\n2.No\n";
            cin >> choiceB;

            if (user->numberofAccessibleKeys()>0){

                Attempt2open(choiceB, user);
            }
            else {
                cout<<"\nYou have no keys\n";
            }
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

        if (X == 'o' && Hamper.size() <= 4)
        {
            Hamper.push_back(d.at(index));
        }
        else if (X == 'p' && Coffin.size() <= 4)
        {
            Coffin.push_back(d.at(index));
        }
        else if (X == 'c' && Toolbox.size() <= 4)
            Toolbox.push_back(d.at(index));

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
    //Closet Function vv

    void closetprompt(Player *player)
    {
        int choice;
        int XXX;
        int take;


        cout << "Dining Room closet has :\n";

        for (int i=0;i<closet.size();i++)
        {
            cout<<closet.at(i)->getDescription()<<endl;
        }

        cout << "\nSelect an action:\n";
        cout << "1.Insert items\n";
        cout << "2.Extract items\n";
        cout << "3.Close closet\n";
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
                    cout <<"Closet" << " has:\n";

                    if (!closet.empty())
                    {
                        for (int i=1;i<closet.size()+1;i++)
                        {
                            cout<<i<<"."<<closet.at(i-1)->getDescription()<<endl;
                        }
                    }
                    else
                    {
                        cout << "Closet is empty!" << endl;
                        return;
                    }

                    cin >> take;

                    take = inputCheck(closet.size(), take);

                    take = take-1;

                    Take(closet.at(take), player);

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
                else if (closet.size() == 4)
                {
                    cout<<"\nCloset is full\n";
                }

                else

                    InputPrompt(player, 'W');
            }

            cout << "\nSelect an action:\n";
            cout << "1.Insert items\n";
            cout << "2.Extract items\n";
            cout << "3.Close chest\n";
            cin >> XXX;
            XXX = inputCheck(3, XXX);

        }

    }
};

#endif
