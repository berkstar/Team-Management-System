
#include "CompleteReg.h"
#include <iostream>

using namespace std;

// Default constructor.

CompleteReg::CompleteReg() {
    teamCount = 0;
    head = NULL;
}

// Deconstruct
CompleteReg::~CompleteReg() {
    Node *nextNode;
    while (head != NULL) {
        nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

//Assignment Operator
CompleteReg &CompleteReg::operator=(const CompleteReg &right) {
    if (&right != this) {

        // Deallocates left side list.
        Node *nextNode;
        while (head != NULL) {
            nextNode = head->next;
            delete head;
            head = nextNode;
        }
        this->teamCount = right.teamCount;

        if (right.head) {

            //First node
            head = new Node;
            head->t = right.head->t;

            Node *curr = head;
            Node *currOther = right.head->next;

            while (currOther) {
                curr->next = new Node;
                curr = curr->next;
                curr->t = currOther->t;
                currOther = currOther->next;
            }
            curr->next = NULL;
        }
    }
    return *this;
}

Team &CompleteReg::operator[](const int index) {
    if (index < 0 || index > teamCount) {
        throw out_of_range("Invalid index.");
    } else {

        Node *cur = head;
        for (int i = 1; i < index; i++) {
            cur = cur->next;
        }
        return cur->t;

    }

}


CompleteReg::CompleteReg(const CompleteReg &other) {

    this->teamCount = other.teamCount;
    if (other.head == NULL)
        head = NULL;
    else {
        //First node
        head = new Node;
        head->t = other.head->t;

        Node *curr = head;
        Node *currOther = other.head->next;

        while (currOther) {
            curr->next = new Node;
            curr = curr->next;
            curr->t = currOther->t;
            currOther = currOther->next;
        }
        curr->next = NULL;
    }

}

void CompleteReg::addTeam(const string tName, const string tColor, const int tYear) {

    if (findTeam(tName)) {
        cout << "Team " << tName << " already exists in list." << endl;
    } else if (tYear < 1800 || tYear > 2020) {
        cout << "Please enter valid year." << endl;
    } else {

        string upCaseName = tName;

        for (int j = 0; j < tName.size(); ++j) {
            upCaseName[j] = toupper(tName[j]);
        }

        Team newTeam(upCaseName, tColor, tYear);
        Node *newNode = new Node;
        newNode->t = newTeam;


        newNode->next = head;
        head = newNode;
        teamCount++;
        cout << "Team " << upCaseName << " has been added to the list." << endl;

    }

}


void CompleteReg::removeTeam(const string teamName) {

    Node *found = findTeam(teamName);
    if (found == NULL) {
        cout << "Team " << teamName << " does not exist." << endl;
    } else {

        string upCaseName = teamName;

        for (int j = 0; j < teamName.size(); ++j) {
            upCaseName[j] = toupper(teamName[j]);
        }


        Node *curr = head;
        Node *prev = NULL;

        for (int i = 1; i < teamCount; ++i) {

            if (curr->next->t.getName().compare(upCaseName) == 0) {
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
        teamCount--;
        cout << "Team " << upCaseName << " has been deleted from list." << endl;
    }


}

void CompleteReg::displayAllTeams() const {

    if (teamCount != 0) {
        Node *cur = head;
        while (cur != NULL) {
            cout << cur->t.getName() << ", " << cur->t.getColor() << ", " << cur->t.getYear() << endl;
            cur = cur->next;
        }
    } else {
        cout << "--EMPTY--" << endl;
    }

}

void CompleteReg::displayPlayer(const string playerName) const {
    Player *found;
    bool hasfound = false;
    cout << "Player " << playerName << endl;
    if (teamCount != 0) {
        Node *cur = head;

        while (cur != NULL) {
            found = &cur->t.findPlayer(playerName)->player;
            if (found) {
                cout << found->getPosition() << ", " << cur->t.getName() << ", " << cur->t.getColor() << ", "
                     << cur->t.getYear() << endl;
                hasfound = true;
            }
            cur = cur->next;
        }

        if (!hasfound) {
            cout << "--EMPTY--" << endl;
        }
    }
}


void CompleteReg::addPlayer(const string tName, const string pName, const string pPosition) {
    Node *found = findTeam(tName);
    if (found == NULL) {
        cout << "Team " << tName << " does not exist." << endl;
    } else {
        found->t.addPlayer(pName, pPosition);
    }
}

void CompleteReg::displayTeam(const string teamName) const {
    Node *found = findTeam(teamName);
    if (found) {
        cout << found->t.getName() << ", " << found->t.getColor() << ", " << found->t.getYear() << endl;
        found->t.displayAllPlayers();
    } else {
        /*
         * Even though team does not exist, it displays just name of team since we don't have any other information
         * about color and year, and  --EMPTY-- for player list.
         *
         */
        cout << teamName << endl;
        cout << "--EMPTY--" << endl;
    }

}


void CompleteReg::removePlayer(const string teamName, const string playerName) {
    Node *teamFound = findTeam(teamName);
    if (teamFound) {
        teamFound->t.removePlayer(playerName);
    } else {
        cout << "Team " << teamName << " does not exist." << endl;
    }
}


/*
 *
 * Finds team
 * Returns previous node in order to not only to be used addTeam but also removeTeam function.
 *
 */
CompleteReg::Node *CompleteReg::findTeam(const string teamName) const {

    if (teamCount < 1)
        return NULL;

    string upCaseName = teamName;

    for (int j = 0; j < teamName.size(); ++j) {
        upCaseName[j] = toupper(teamName[j]);
    }

    Node *curr = head;
    for (int i = 1; i <= teamCount; ++i) {

        if (curr->t.getName().compare(upCaseName) == 0)
            return curr;
        curr = curr->next;

    }
    return NULL;
}

