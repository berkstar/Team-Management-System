#include "Player.h"


const string Player::getName() const {
    return name;
}

void Player::setName(string name) {
    this->name = name;
}

const string Player::getPosition() const {
    return position;
}

void Player::setPosition(string position) {
    this->position = position;
}

//Default constructor.
Player::Player() {
    name = "";
    position = "";
}
// Constructor.
Player::Player(string name,string position){
    this->name = name;
    this->position = position;

}
