#ifndef __PLAYER_H
#define __PLAYER_H

#include <iostream>
#include <string>
using namespace std;

class Player {
public:
	Player(const string name, const string position);
	Player();
	~Player();
	void operator=(const Player& right);
	string getPlayerName();
	string getPosition();
private:
	string pName;
	string pPosition;
};
#endif
