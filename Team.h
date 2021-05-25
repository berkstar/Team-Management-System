
#ifndef HW3B_TEAM_H
#define HW3B_TEAM_H
#include <string>
#include "Player.h"
using namespace std;
class Team{
private:
    string name;
    string color;
    int year;
    struct Node {
        Player player;
        Node* next;
    };
    Node* head;

    int playerCount;



public:
    Node* findPlayer( const string playerName ) const;
    void addPlayer(const string pName, const string pPosition);
    void removePlayer( const string pName);

    Team(string name, string color,int year);

    Team();
    ~Team(); // Deconstructor
    Team( const Team& other); // Copy Constructor
    Team& operator= (const Team &right); // assignment Operator
    string getName();
    void setName(string name);
    void displayAllPlayers() const;
    string getColor() const;
    void setColor(string color);
    int getYear() const;
    void setYear( int Year);

};
#endif //HW3B_TEAM_H
