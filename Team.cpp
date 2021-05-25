#include "Team.h"
#include <iostream>

using namespace std;

//Constructor
Team::Team(string name, string color, int year) {
    this->name = name;
    this->color = color;
    this->year = year;
    playerCount = 0;
    head = NULL;
}

/*
 * Assignment operator
 */
Team &Team::operator=(const Team &right) {
    if (&right != this) {

        // Deallocates left side data.
        Node *nextNode;
        while (head != NULL) {
            nextNode = head->next;
            delete head;
            head = nextNode;
        }

        this->name = right.name;
        this->color = right.color;
        this->year = right.year;
        this->playerCount = right.playerCount;

        if (right.head) {

            //First node
            head = new Node;
            head->player = right.head->player;

            Node *curr = head;
            Node *currOther = right.head->next;

            while (currOther) {
                curr->next = new Node;
                curr = curr->next;
                curr->player = currOther->player;
                currOther = currOther->next;
            }
            curr->next = NULL;
        }
    }
    return *this;
}

//Deconstructor
Team::~Team() {

    Node *nextNode;
    while (head != NULL) {
        nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

//Copy Constrcutor.
Team::Team(const Team &other) {

    name = other.name;
    color = other.color;
    year = other.year;
    playerCount = other.playerCount;
    if (other.head == NULL)
        head = NULL;
    else {
        //First node
        head = new Node;
        head->player = other.head->player;

        Node *curr = head;
        Node *currOther = other.head->next;

        while (currOther) {
            curr->next = new Node;
            curr = curr->next;
            curr->player = currOther->player;
            currOther = currOther->next;
        }
        curr->next = NULL;
    }
}

// Removes player from list
void Team::removePlayer(const string pName) {
    Node *found = findPlayer(pName);
    if (found == NULL) {
        cout << "Player " << pName << " does not exist." << endl;
    } else {
        string upCaseName = pName;
//Converts player name to Uppercase
        for (int j = 0; j < pName.size(); ++j) {
            upCaseName[j] = toupper(pName[j]);
        }

        //Stores prev to unlink player from list.

        Node *curr = head;
        Node *prev = NULL;

        for (int i = 1; i < playerCount; ++i) {

            if (curr->next->player.getName().compare(upCaseName) == 0) {
                prev = curr;
                curr = prev->next;
                break;
            } else {

                curr = curr->next;
            }
        }
        if (!prev) { // First one
            curr = head;
            head = head->next;
            delete curr;

        } else {
            prev->next = curr->next;
            delete curr;
        }
        playerCount--;
        cout << "Player " << upCaseName << " has been deleted from team " << name << endl;
    }

}

//Finds player and returns node that it is in.
Team::Node *Team::findPlayer(const string playerName) const {
    if (playerCount < 1) {
        return NULL;
    }
    //Converts name to uppercase.
    string upCaseName = playerName;
    for (int j = 0; j < playerName.size(); ++j) {
        upCaseName[j] = toupper(playerName[j]);
    }

    Node *curr = head;
    for (int i = 1; i <= playerCount; ++i) {
        if (curr->player.getName().compare(upCaseName) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

//Displays all players.
void Team::displayAllPlayers() const {

    if (playerCount) {
        Node *curr = head;
        while (curr) {
            cout << curr->player.getName() << ", " << curr->player.getPosition() << endl;
            curr = curr->next;
        }
    } else {
        cout << "--EMPTY--" << endl;
    }
}

/*
 * Adds player to list
 * Only dealing with same player name;
 */
void Team::addPlayer(const string pName, const string pPosition) {
    if (findPlayer(pName)) {
        cout << "Player " << pName << " already exists in the team " << name << endl;
    } else {
        string upCaseName = pName;

        for (int j = 0; j < pName.size(); ++j) {
            upCaseName[j] = toupper(pName[j]);
        }
        //Creates new player according to info to add list.
        Player newPlayer(upCaseName, pPosition);
        Node *newNode = new Node;
        newNode->player = newPlayer;

        newNode->next = head;
        head = newNode;
        playerCount++;
        cout << "Player " << upCaseName << " has been added to the team " << name << endl;
    }
}

//Constructor.
Team::Team() {
    this->name = "";
    this->color = "";
    this->year = 0;
    playerCount = 0;
    head = NULL;
}

string Team::getName() {
    return name;
}

void Team::setName(string name) {
    this->name = name;
}

string Team::getColor() const {
    return color;
}

void Team::setColor(string color) {
    this->color = color;
}

int Team::getYear() const {
    return year;
}

void Team::setYear(int Year) {
    this->year = year;
}

