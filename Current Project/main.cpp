#include "BST.h"
#include "GameEngine.h"
int main()
{
    Player *user = new Player();

    GameEngine mainEngine(user);

    mainEngine.start(user);

    delete user;

    return 0;
}
