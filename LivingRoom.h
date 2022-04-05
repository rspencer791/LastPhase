#ifndef LivingR
#define LivingR
#include "Player.h"
#include "Room.h"
class LivingRoom : public Room
{
private:
    vector<Item *> Couch;
    vector<Item *> Bookshelf;
    vector<Item *> Table;
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
    LivingRoom(Player *player)
    {

        initKeys(player);

        initDoors();

        thisRoom = "LivingRoom";

        initObjects();

        hasLeft = false;
    }

    void outputRoomName()
    {
        cout << "\nYou are in the Living Room.\nYou see a Couch, an Bookshelf, and a Table.\n";
    }

    void initObjects()
    {
        gameObject Couch("Couch");

        actualObjectDescriptions.push_back(Couch);

        gameObject Bookshelf("Bookshelf");

        actualObjectDescriptions.push_back(Bookshelf);

        gameObject Table("Table");

        actualObjectDescriptions.push_back(Table);
    }

    void initKeys(Player *ptr)
    { // Couch

        BST *temp = ptr->getInventory();
        Item *itemA = ptr->dummyptr;

        Couch.push_back(temp->searchAndReturnNodePointer(79, itemA));

        Couch.push_back(temp->searchAndReturnNodePointer(87, itemA));

        Couch.push_back(temp->searchAndReturnNodePointer(86, itemA));

        // Bookshelf

        Bookshelf.push_back(temp->searchAndReturnNodePointer(200, itemA));

        Bookshelf.push_back(temp->searchAndReturnNodePointer(210, itemA));

        Bookshelf.push_back(temp->searchAndReturnNodePointer(230, itemA));

        // Table

        Table.push_back(temp->searchAndReturnNodePointer(240, itemA));

        Table.push_back(temp->searchAndReturnNodePointer(250, itemA));

        Table.push_back(temp->searchAndReturnNodePointer(260, itemA));

        // closet

        closet.push_back(temp->searchAndReturnNodePointer(120, itemA));
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
            for (int i = 0; i < Couch.size(); i++)
            {
                cout << Couch.at(i)->getDescription();
                cout << endl;
            }
            Z = 'p';
        }
        else if (choice == 2)
        {
            for (int i = 0; i < Bookshelf.size(); i++)
            {
                cout << Bookshelf.at(i)->getDescription();
                cout << endl;
            }

            Z = 'o';
        }
        else
        {
            for (int i = 0; i < Table.size(); i++)
            {
                cout << Table.at(i)->getDescription();
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

                    if (choice == 1 && Couch.size() != 0)
                    {
                        for (int i = 1; i < Couch.size()+1; i++)
                        {
                            cout << i << "." << Couch.at(i-1)->getDescription() << endl;
                        }
                    }
                    else if (choice == 2 && Bookshelf.size() != 0)
                    {

                        for (int i = 1; i < Bookshelf.size()+1; i++)
                        {
                            cout << i << "." << Bookshelf.at(i-1)->getDescription() << endl;
                        }
                    }
                    else if (choice == 3 && Table.size() != 0)
                    {
                        for (int i = 1; i < Table.size()+1; i++)
                        {
                            cout << i << "." << Table.at(i-1)->getDescription() << endl;
                        }
                    }

                    else
                    {
                        cout << "Object is empty!" << endl;
                        return;
                    }

                    cin >> take;

                    if (choice==1)
                    take = inputCheck(Couch.size(), take);
                    else if (choice==2)
                        take = inputCheck(Bookshelf.size(), take);
                    else
                        take = inputCheck(Table.size(), take);

                    take = take - 1;

                    if (choice == 1)
                    {
                        if (take != 100 && take < Couch.size() && take >= 0)
                        {
                            Take(Couch.at(take), player);
                            Couch.erase(Couch.begin() + take);
                        }
                    }
                    else if (choice == 2)
                    {
                        if (take != 100 && take < Bookshelf.size() && take >= 0)
                        {
                            Take(Bookshelf.at(take), player);
                            Bookshelf.erase(Bookshelf.begin() + take);
                        }
                    }
                    else

                    {
                        if (take != 100 && take < Table.size() && take >= 0)
                        {
                            Take(Table.at(take), player);
                            Table.erase(Table.begin() + take);
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
                else if (Z == 'c' && Table.size() == 4)
                {
                    cout << "\nTable is full\n";
                }
                else if (Z == 'o' && Bookshelf.size() == 4)
                {
                    cout << "\nBookshelf is full\n";
                }
                else if (Z == 'p' && Couch.size() == 4)
                {
                    cout << "\nCouch is full\n";
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

            if (attemptkey->getKey() == 67)
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
        cout << "\nWhich door would you like to investigate:\n1.Start Room Door\n2.Closet C Door\n";

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
            cout << "\nWithout life, I still grow.\nWithout lungs, yet I still need air.\n";
            cout << "\nThe door is locked. Attempt to open it?\n1.Yes\n2.No\n";
            cin >> choiceB;

            if (user->numberofAccessibleKeys()>0){
                Attempt2open(choiceB, user);}
            else
            {
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

        if (X == 'o' && Bookshelf.size() <= 4)
        {
            Bookshelf.push_back(d.at(index));
        }
        else if (X == 'p' && Couch.size() <= 4)
        {
            Couch.push_back(d.at(index));
        }
        else if (X == 'c' && Table.size() <= 4)
            Table.push_back(d.at(index));
        else if (X=='W' && closet.size()<=4)
            closet.push_back(d.at(index));

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

            void closetprompt(Player *player)
    {
        int choice;
        int XXX;
        int take;


        cout << "Kitchen closet has :\n";

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
                    cout <<"Kitchen" << " has:\n";

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
