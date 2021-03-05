#include "Player.h"

Player::Player(const string name, const string position) {
	pName = name;
	pPosition = position;
}

Player::Player() {
	pName = "";
	pPosition = "";
}

Player::~Player() {}

void Player::operator=(const Player& right) {
	pName = right.pName;
	pPosition = right.pPosition;
}

string Player::getPlayerName() {
	return pName;
}

string Player::getPosition() {
	return pPosition;
}