#ifndef GAME_ENGINE
#define GAME_ENGINE
#include "StartNode.h"
#include "Kitchen.h"
#include "Basement.h"
#include "LivingRoom.h"
#include "DiningRoom.h"
#include <queue>
using std::queue;

class GameEngine
{
private:
    queue<Room *> stackOfRooms;
    StartNode *startX;
    Kitchen *kitchen;
    Basement *base;
    LivingRoom *LR;
    DiningRoom *DR;
    bool initalPhaseisOver;

public:
    GameEngine(Player *p)
    {
        startX = new StartNode(p); // remember to delete later

        stackOfRooms.push(startX);

        initalPhaseisOver = false;

        kitchen = new Kitchen(p);

        base = new Basement(p);

        LR = new LivingRoom(p);

        DR = new DiningRoom(p);

    }

    void start(Player *user)
    {

        while (!stackOfRooms.empty())
        {

            while (!stackOfRooms.front()->hasLeftX())
            {
                stackOfRooms.front()->outputRoomName();

                stackOfRooms.front()->Combine(user);
            }

            int ID = stackOfRooms.front()->returnroom_ID_of_destination();

            // start->kitchen(north)
            if (ID == 0 && stackOfRooms.front()->thisRoomX() == "start")
            {

                stackOfRooms.push(kitchen);

                stackOfRooms.pop();
             }
            //-1 is start room
            if (ID == -1 && stackOfRooms.front()->thisRoomX() == "kitchen")
            {

                stackOfRooms.push(startX);

                stackOfRooms.pop();
             }

            if (ID==-1 && stackOfRooms.front()->thisRoomX() == "Basement")
            {
                stackOfRooms.push(startX);
                stackOfRooms.pop();
            }

            if (ID ==  666 && stackOfRooms.front()->thisRoomX() == "start")
            {
                stackOfRooms.push(base);
                stackOfRooms.pop();
            }

            //Living Room vv
            if (ID== -1 && stackOfRooms.front()->thisRoomX() == "LivingRoom")
                {
                    stackOfRooms.push(startX);
                    stackOfRooms.pop();
                }

            if (ID ==  777 && stackOfRooms.front()->thisRoomX() == "start")
                {
                    stackOfRooms.push(LR);
                    stackOfRooms.pop();
                }
            //Dining Room
            if (ID== -1 && stackOfRooms.front()->thisRoomX() == "Dining Room")
                {
                    stackOfRooms.push(startX);
                    stackOfRooms.pop();
                }

            if (ID ==  321 && stackOfRooms.front()->thisRoomX() == "start")
                {
                    stackOfRooms.push(DR);
                    stackOfRooms.pop();
                }


            stackOfRooms.front()->reinithasMoved(user);
            stackOfRooms.front()->ReinithasLeft();
            // push new room
        }
    }

    ~GameEngine()
    {
        delete startX;
        delete kitchen;
    }
};

#endif
