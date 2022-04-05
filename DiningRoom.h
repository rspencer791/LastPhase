#ifndef DININGROOM_H
#define DININGROOM_H
#include "Player.h"
#include "Room.h"

class DiningRoom : public Room
{
private:

    vector<Item *> Hutch;
    vector<Item *> Wine_Rack;
    vector<Item *> Bench;
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
    DiningRoom(Player *player)
    {

        initKeys(player);

        initDoors();

        thisRoom = "Dining Room";

        initObjects();

        hasLeft = false;
    }

    void outputRoomName()
    {
        cout << "\nYou are in the Dining Room.\nYou see a Hutch, a Wine Rack, and a Bench.\n";
    }

    void initObjects()
    {
        gameObject Hutch("Hutch");

        actualObjectDescriptions.push_back(Hutch);

        gameObject Wine_Rack("Wine Rack");

        actualObjectDescriptions.push_back(Wine_Rack);

        gameObject Bench("Bench");

        actualObjectDescriptions.push_back(Bench);
    }

    void initKeys(Player *ptr)
    { // Hutch

        BST *temp = ptr->getInventory();
        Item *itemA = ptr->dummyptr;

        Hutch.push_back(temp->searchAndReturnNodePointer(270, itemA));

        Hutch.push_back(temp->searchAndReturnNodePointer(280, itemA));

        Hutch.push_back(temp->searchAndReturnNodePointer(290, itemA));

        // Wine Rack

        Wine_Rack.push_back(temp->searchAndReturnNodePointer(300, itemA));

        Wine_Rack.push_back(temp->searchAndReturnNodePointer(310, itemA));

        Wine_Rack.push_back(temp->searchAndReturnNodePointer(320, itemA));

        // Bench

        Bench.push_back(temp->searchAndReturnNodePointer(330, itemA));

        Bench.push_back(temp->searchAndReturnNodePointer(340, itemA));

        Bench.push_back(temp->searchAndReturnNodePointer(350, itemA));

        //closet

        closet.push_back(temp->searchAndReturnNodePointer(110, itemA));
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
            for (int i = 0; i < Hutch.size(); i++)
            {
                cout << Hutch.at(i)->getDescription();
                cout << endl;
            }
            Z = 'p';
        }
        else if (choice == 2)
        {
            for (int i = 0; i < Wine_Rack.size(); i++)
            {
                cout << Wine_Rack.at(i)->getDescription();
                cout << endl;
            }

            Z = 'o';
        }
        else
        {
            for (int i = 0; i < Bench.size(); i++)
            {
                cout << Bench.at(i)->getDescription();
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

                    if (choice == 1 && Hutch.size() != 0)
                    {
                        for (int i = 1; i < Hutch.size()+1; i++)
                        {
                            cout << i << "." << Hutch.at(i-1)->getDescription() << endl;
                        }
                    }
                    else if (choice == 2 && Wine_Rack.size() != 0)
                    {

                        for (int i = 1; i < Wine_Rack.size()+1; i++)
                        {
                            cout << i << "." << Wine_Rack.at(i-1)->getDescription() << endl;
                        }
                    }
                    else if (choice == 3 && Bench.size() != 0)
                    {
                        for (int i = 1; i < Bench.size()+1; i++)
                        {
                            cout << i << "." << Bench.at(i-1)->getDescription() << endl;
                        }
                    }

                    else
                    {
                        cout << "Object is empty!" << endl;
                        return;
                    }

                    cin >> take;

                    if (choice==1)
                    take = inputCheck(Hutch.size(), take);
                    else if (choice==2)
                        take = inputCheck(Wine_Rack.size(), take);
                    else
                        take = inputCheck(Bench.size(), take);

                    take = take - 1;

                    if (choice == 1)
                    {
                        if (take != 100 && take < Hutch.size() && take >= 0)
                        {
                            Take(Hutch.at(take), player);
                            Hutch.erase(Hutch.begin() + take);
                        }
                    }
                    else if (choice == 2)
                    {
                        if (take != 100 && take < Wine_Rack.size() && take >= 0)
                        {
                            Take(Wine_Rack.at(take), player);
                            Wine_Rack.erase(Wine_Rack.begin() + take);
                        }
                    }
                    else

                    {
                        if (take != 100 && take < Bench.size() && take >= 0)
                        {
                            Take(Bench.at(take), player);
                            Bench.erase(Bench.begin() + take);
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
                else if (Z == 'c' && Bench.size() == 4)
                {
                    cout << "\nBench is full\n";
                }
                else if (Z == 'o' && Wine_Rack.size() == 4)
                {
                    cout << "\nWine_Rack is full\n";
                }
                else if (Z == 'p' && Hutch.size() == 4)
                {
                    cout << "\nHutch is full\n";
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

            if (attemptkey->getKey() == 47)
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
        cout << "\nWhich door would you like to investigate:\n1.Start Room Door\n2.ClosetC Door\n";

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
        {   cout << "\nI speak without a mouth.\n";
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

        if (X == 'o' && Wine_Rack.size() <= 4)
        {
            Wine_Rack.push_back(d.at(index));
        }
        else if (X == 'p' && Hutch.size() <= 4)
        {
            Hutch.push_back(d.at(index));
        }
        else if (X == 'c' && Bench.size() <= 4)
            Bench.push_back(d.at(index));
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

#endif // DiningRoom_H
