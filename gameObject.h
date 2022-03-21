#ifndef GO
#define GO
#include <string>

using std::string;

class gameObject
{
private:
    string description;

public:
    gameObject(string x)
    {
        description = x;
    }

    string getDescription()
    {
        return description;
    }

    
};

#endif