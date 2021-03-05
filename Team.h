#ifndef __TEAM_H
#define __TEAM_H

#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

class Team {
public:
	Team(const string name = "", const string color = "", const int year = 0);
	Team(const Team& tCopy);
	~Team();
	void operator=(const Team& right);
	string getName();
	string getColor();
	int getYear();
	int getPlayerCount();
	string getPlayerPosition(const string playerName);
	void addPlayerToTeam(const string playerName, const string playerPosition);
	void removePlayerFromTeam(const string playerName);
	void displayPlayersInTeam();
	bool isPlayerExist(const string playerName);
private:
	struct PlayerNode {
		Player p;
		PlayerNode* next;
	};
	PlayerNode* head;
	string tName;
	string tColor;
	int tYear;
	int playerCount;
	PlayerNode* findPlayer(string playerName) const;
};
#endif