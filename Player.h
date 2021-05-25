

#include <string>
#ifndef HW3B_PLAYER_H
#define HW3B_PLAYER_H
using namespace std;
class Player{

    string name;
    string position;

public:
    Player();
    Player(string name,string position);
    const string getName() const;
    void setName(string name);
    const string getPosition() const;
    void setPosition( string position);

};


#endif //HW3B_PLAYER_H
