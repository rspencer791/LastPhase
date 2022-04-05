#ifndef START_NODE
#define START_NODE
#include "Room.h"
#include <list>
class StartNode : public Room
{
private:
    vector<Item *> keys;
    std::list<Item *> statue;
    string riddle;                               // contains riddle, each room will have a different riddle
    string riddleB;
    string riddleC;
    string riddleD;

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
    StartNode(Player *player)
    {

        hasLeft = false;

        initKeys(player);

        initDoors();

        initObjects();

        thisRoom = "start";

        riddle = "\nSo many keys, and none of them open doors.\n";
        riddleB = "\nThe person who builds me, doesn't want me,\nthe person who buys me doesn't use me,\nand the person that uses me doesn't know they've got me\n";
        riddleC = "\nYou bury me when I am alive and dig me up when I die.\n";
        riddleD = "\nI don't have eyes, but once I did see. \nOnce I had thoughts but now I'm white and empty.\n";
    }

    void outputRoomName()
    {
        cout << "\nYou are in the start room.\n";
        cout << "\nYou see a chest on a table in the center and four doors.\nYou see an object hanging on the wall, covered with a sheet\n";
        cout<< "\nYou see a statue in the corner\n";
    }

    void initObjects()
    {
        gameObject chest("Chest");

        actualObjectDescriptions.push_back(chest);
    }

    // NOTE:NEVER DELETE THESE KEYS
    void initKeys(Player *ptr) // remember, player holds all keys, regardless of whether or not they are accessible to him/her
    {
        BST *temp = ptr->getInventory();
        Item *itemA = ptr->dummyptr;

        keys.push_back(temp->searchAndReturnNodePointer(10, itemA)); // search for key number and push back the item with that key

        keys.push_back(temp->searchAndReturnNodePointer(20, itemA));

        keys.push_back(temp->searchAndReturnNodePointer(30, itemA));

        keys.push_back(temp->searchAndReturnNodePointer(40, itemA));
    }

    void investigate(Player *player)
    {
        int XXX;
        int choice;
        int take;
        int i = 0;
        cout << "\nWhich would you like to do?\n";

        cin >> choice;



        choice = inputCheck(3, choice);

        if (choice == 3)
        {
            statueOptions(player);
            return;
        }

        if (choice ==2)
        {
            exit(0);
        }

        cout << endl
             << actualObjectDescriptions.at(0).getDescription() << " has: \n";

        while (i < keys.size())
        {

            cout << keys.at(i)->getDescription() << endl;
            i++;
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

            if (XXX == 2)
            {
                if (!player->inventoryFull() && keys.size()!=0)
                {
                    cout << "\nWhich item would you like to take:\n";
                    int i = 1;
                    while (i-1 < keys.size())
                    {

                        cout << i << "." << keys.at(i-1)->getDescription() << endl;
                        i++;
                    }

                    cin >> take;

                    take = inputCheck(keys.size(), take);

                    take = take - 1;


                    if (take < keys.size() && !player->inventoryFull())
                    {

                        Take(keys.at(take), player);
                        keys.erase(keys.begin() + take);
                    }
                    else if (take < keys.size() && !player->inventoryFull())
                    {
                        cout << "\nInventory is Full!\n";
                    }
                }
                else if (player->inventoryFull())

                    cout << "\nStorage is full!\n";
                else
                {
                    cout<<"\nThe chest is empty\n";
                    return;
                }
            }
            if (XXX == 1)
            {

                int numAccessable = player->numberofAccessibleKeys();

                if (numAccessable == 0)
                {
                    cout << "\nInventory is empty!\n";
                }
                else if (keys.size() == 4)
                {
                    cout << "\nChest is full!\n";
                }
                else
                    InputPrompt(player, 'Z');
            }

            cout << "\nSelect an action:\n";
            cout << "1.Insert items\n";
            cout << "2.Extract items\n";
            cout << "3.Close chest\n";
            cin >> XXX;

            XXX = inputCheck(3, XXX);

        }
    }

    void Take(Item *key, Player *player) // put from object ->player inventory
    {

        key->makeAccessable();

        cout << "\nYou have taken the object!\n";

        updateAndDisplayInventory(player);
    }

    void Attempt2open(int choice, Player *u)
    {

        Item *attemptkey = pickKey(u);

        if (attemptkey != nullptr)
        {

            if (choice == 0 && !doors.at(0))
            {

                if (attemptkey->getKey() == 30) // piano key opens the kitchen
                {
                    cout << "\nThe door has been opened!\n";
                    doors.at(0) = true;         // open door
                    room_ID_of_destination = 0; // kitchen is north
                    u->Moved();
                    hasLeft = true;

                    attemptkey->makeInAccessable();

                    for (int i = 0; i < keys.size(); i++)
                    {
                        if (keys.at(i)->getKey() == 30)
                            keys.erase(keys.begin() + i); // take away key from chest
                    }

                    return;
                }
                else
                {
                    cout << "\nThat is the wrong Key!\n";
                    return;
                }
            }

            if (choice == 0 && doors.at(0))
            {
                cout << "\nThe door has been opened!\n";
                room_ID_of_destination = 0; // kitchen is north
                u->Moved();
                hasLeft = true;

                return;
            }

            if (choice == 1 && doors.at(1))
            {
                cout << "\nThe door has been opened!\n";
                room_ID_of_destination = 666; // kitchen is north
                u->Moved();
                hasLeft = true;
                return;
            }

            if (choice == 1 && !doors.at(1) )
            {

                if (attemptkey->getKey() == 40) // coffin key opens the basement
                {
                    cout << "\nThe door has been opened!\n";
                    doors.at(1) = true;         // open door
                    room_ID_of_destination = 666; // kitchen is north
                    u->Moved();
                    hasLeft = true;

                    attemptkey->makeInAccessable();

                    for (int i = 0; i < keys.size(); i++)
                    {
                        if (keys.at(i)->getKey() == 40)
                            keys.erase(keys.begin() + i); // take away key from chest
                    }

                    return;
                }
                else
                {
                    cout << "\nThat is the wrong Key!\n";
                    return;
                }
            }

            if ( choice == 2 && doors.at(2) )
                        {
                            cout << "\nThe door has been opened!\n";
                            room_ID_of_destination = 777; // ID of Living Room
                            u->Moved();
                            hasLeft = true;
                            return;
                        }

            if (choice == 2 && !doors.at(2) )
                        {
                            if (attemptkey->getKey() == 10) // Plant key opens the Living Room
                            {
                                cout << "\nThe door has been opened!\n";
                                doors.at(2) = true;         // open door
                                room_ID_of_destination = 777; // ID for Living Room ; East Door
                                u->Moved();
                                hasLeft = true;

                                attemptkey->makeInAccessable();

                                for (int i = 0; i < keys.size(); i++)
                                {
                                    if (keys.at(i)->getKey() == 10)
                                        keys.erase(keys.begin() + i); // take away key from chest
                                }

                                return;
                            }
                            else
                            {
                                cout << "\nThat is the wrong Key!\n";
                                return;
                            }
                        }

                    if ( choice == 3 && doors.at(3) )
                        {
                            cout << "\nThe door has been opened!\n";
                            room_ID_of_destination = 321; // ID of Living Room
                            u->Moved();
                            hasLeft = true;
                            return;
                        }

                    if (choice == 3 && !doors.at(3) )
                        {
                            if (attemptkey->getKey() == 20) // Plant key opens the Living Room
                            {
                                cout << "\nThe door has been opened!\n";
                                doors.at(3) = true;         // open door
                                room_ID_of_destination = 321; // ID for Living Room ; East Door
                                u->Moved();
                                hasLeft = true;

                                attemptkey->makeInAccessable();

                                for (int i = 0; i < keys.size(); i++)
                                {
                                    if (keys.at(i)->getKey() == 20)
                                        keys.erase(keys.begin() + i); // take away key from chest
                                }

                                return;
                            }
                            else
                            {
                                cout << "\nThat is the wrong Key!\n";
                                return;
                            }
                        }


        }
            // TODO: the rest of the doors once they're created
    }
    void initDoors()
    {
        for (int i = 0; i < 4; i++)
        {
            doors.push_back(false); // all doors are closed initially
        }
    }

    void displayDoors(Player *user)
    {
        int choice;
        int choiceB;
        cout << "\nWhich door would you like to investigate:\n1.North Door\n2.South Door\n3.East Door\n4.West door\n";

        cin >> choice;

        choice = inputCheck(4, choice);

        choice = choice - 1;

        if (doors.at(choice) && choice == 0)
        {
            cout << "\nThe door is open and you pass through.\n";
            room_ID_of_destination = 0;
            user->Moved(); // set moved to true
            hasLeft = true;
        }
        else if (!doors.at(choice) && choice == 0)
        {
            cout << riddle;
            cout << "\nThe door is locked. Would you like to attempt to open it?\n1.Yes\n2.No\n";
            cin >> choiceB;

            choiceB = inputCheck(2,choiceB);

            if (choiceB == 1)
                Attempt2open(choice, user);
        }

        else if (doors.at(choice) && choice == 1)
        {
            cout << "\nThe door is open and you pass through.\n";
            room_ID_of_destination = 666;
            user->Moved(); // set moved to true
            hasLeft = true;

        }
        else if (!doors.at(choice) && choice == 1)
        {
            cout << riddleB;
            cout << "\nThe door is locked. Would you like to attempt to open it?\n1.Yes\n2.No\n";
            cin >> choiceB;
            choiceB = inputCheck(2,choiceB);

            if (choiceB == 1)
                Attempt2open(choice, user);

        }


        else if (!doors.at(choice) && choice == 2)
               {
                   cout << riddleC;
                   cout << "\nThe door is locked. Would you like to attempt to open it?\n1.Yes\n2.No\n";
                   cin >> choiceB;
                   choiceB = inputCheck(2,choiceB);

                   if (choiceB == 1)
                       Attempt2open(choice, user);

               }

        else if (doors.at(choice) && choice == 2)
               {
                   cout << "\nThe door is open and you pass through.\n";
                   room_ID_of_destination = 777;
                   user->Moved(); // set moved to true
                   hasLeft = true;
               }
        else if (!doors.at(choice) && choice == 3)
               {
                   cout << riddleD;
                   cout << "\nThe door is locked. Would you like to attempt to open it?\n1.Yes\n2.No\n";
                   cin >> choiceB;
                   choiceB = inputCheck(2,choiceB);

                   if (choiceB == 1)
                       Attempt2open(choice, user);

               }

        else if (doors.at(choice) && choice == 3)
               {
                   cout << "\nThe door is open and you pass through.\n";
                   room_ID_of_destination = 321;
                   user->Moved(); // set moved to true
                   hasLeft = true;
               }
    }
    void InputPrompt(Player *player, char X) // from player->objects
    {

        inputItemsintoGameObjects(player, 'x'); // x is a dummy value
    }

    void inputItemsintoGameObjects(Player *player, char X) // from player->objects
    {


        int x;

        int numA = player->getInventory()->numberOfaccessibleKeys();

        vector<Item *> dummy = player->returnsVectorOfAccessableKeys();

        cout << "\nWhat would you like to place in the object?\n Enter number:\n";
        for (int i = 1; i < numA+1; i++)
        {

            cout << i << "." << dummy.at(i-1)->getDescription() << endl;
        }
        cin >> x;

        x = inputCheck(numA, x);

        x-=1;

            if (X=='S')
            {
                dummy.at(x)->makeInAccessable();
                statue.push_back(dummy.at(x));
                cout << "\nItem is no longer in inventory.\n";
                updateAndDisplayInventory(player);
                return;

            }

        dummy.at(x)->makeInAccessable();

        keys.push_back(dummy.at(x));

        cout << "\nItem is no longer in inventory.\n";

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

            cout<<"2.Covered-hanging object"<<endl;

            cout<<"3.Statue"<<endl;


            investigate(player);
        }
        else
        {
            displayDoors(player);
        }
    }



    void statueOptions(Player *player)
    {
        Item *keyy;
        int choice;
        int x;
        int i=0;
        int w = 1;
        cout << "\nSelect an action:\n";
        cout << "1.Insert items\n";
        cout << "2.Extract items\n";
        cout << "3.Leave statue\n";

        cin>>choice;

        choice = inputCheck(3, choice);

        while (choice!=3)
        {


         if (choice == 2)
        {
            if (statue.size()==0)
                cout<<"\nStatue is empty\n";

            else
            {
                cout<<"Statue has "<<endl;


            for (std::list<Item *> ::iterator it = statue.begin();it!= statue.end();it++)
            {
                i++;
                cout<<i<<"."<<(*it)->getDescription();
            }

            cout<<"\nWhich would you like to take?\n"<<endl;
            cin>>x;

            x = inputCheck(statue.size(), x);

            for (std::list<Item *> ::iterator it = statue.begin();it!= statue.end();it++)
            {
                if (w==i)
                {
                    keyy = (*it);

                    if (!player->inventoryFull())
                    {
                        keyy->makeAccessable();
                        statue.erase(it);
                        updateAndDisplayInventory(player);
                    }
                    else
                    {
                        cout<<"\nPlayer inventory is full!\n";
                        return;
                    }

                }
                w++;
            }


        }

        }
        else
        {

            if (player->numberofAccessibleKeys() == 0)
            {
                cout << "\nInventory is empty!\n";


            }
            else
            {
            inputItemsintoGameObjects(player, 'S');
            }
        }

            cout << "\nSelect an action:\n";
            cout << "1.Insert items\n";
            cout << "2.Extract items\n";
            cout << "3.Leave statue\n";

            cin>>choice;
    }

    }

    void checkIfGameWon()
    {
        int x = 0;

        for (std::list<Item *>::iterator it;it!=statue.end();it++)
        {
            if ( (*it)->getKey() == 120 || (*it)->getKey() == 110 || (*it)->getKey() == 90 || (*it)->getKey() == 121  )
            {
                x++;
            }

        }

        if (x==4)
        {
            cout<<"Game has been won! You've escaped!";
            exit(666);
        }
    }


};

#endif
