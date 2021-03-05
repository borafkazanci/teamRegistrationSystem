#include "Team.h"

bool playerDesCheck = false;
Team::Team(const string name, const string color, const int year) {
	head = NULL;
	playerCount = 0;
	playerDesCheck = false;
	tName = name;
	tColor = color;
	tYear = year;
}

Team::Team(const Team& tCopy) {
	tName = tCopy.tName;
	tColor = tCopy.tColor;
	tYear = tCopy.tYear;
	playerCount = tCopy.playerCount;

	if (tCopy.head == NULL)
		head = NULL;
	else{
		head = new PlayerNode;
		head->p = tCopy.head->p;
		head->next = NULL;
		PlayerNode* cur = head;
		for (PlayerNode* newPtr = tCopy.head->next; newPtr != NULL; newPtr = newPtr->next) {
			cur->next = new PlayerNode;
			cur = cur->next;
			cur->p = newPtr->p;
		}
		cur->next = NULL;
	}
}

Team::~Team() {
	while (playerCount > 0) {
		playerDesCheck = true;
		removePlayerFromTeam(head->p.getPlayerName());
	}
}

void Team::operator=(const Team& right) {
	if (&right != this) {
		playerCount = right.playerCount;
		tName = right.tName;
		tColor = right.tColor;
		tYear = right.tYear;
		head = NULL;

		if (playerCount > 0) {
			PlayerNode* cur = right.head;
			PlayerNode* tempPtr = new PlayerNode;

			tempPtr->p = cur->p;
			tempPtr->next = NULL;
			head = tempPtr;
			cur = cur->next;
			
			PlayerNode* newPtr = head;
			for (cur; cur != NULL; cur = cur->next) {
				tempPtr = new PlayerNode;
				tempPtr->p = cur->p;
				newPtr->next = tempPtr;
				newPtr = newPtr->next;
			}
			newPtr->next = NULL;
		}
	}
}

string Team::getName() {
	return tName;
}

string Team::getColor() {
	return tColor;
}

int Team::getYear() {
	return tYear;
}

int Team::getPlayerCount() {
	return playerCount;
}

string Team::getPlayerPosition(const string playerName) {
	PlayerNode* newptr = findPlayer(playerName);
	return newptr->p.getPosition();
}

bool Team::isPlayerExist(const string playerName){
	PlayerNode* cntrlNode = findPlayer(playerName);
	if (cntrlNode == NULL)
		return false;
	else
		return true;
}

void Team::addPlayerToTeam(const string playerName, const string playerPosition) {
	Player player = Player(playerName, playerPosition);

	if (playerCount > 0) {
		if (findPlayer(playerName) != NULL) {
			cout << "There is a player with the same name!" << endl;
			return;
		}
		PlayerNode* cur = head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new PlayerNode;
		cur = cur->next;
		cur->p = player;
		cur->next = NULL;
	}
	else {
		head = new PlayerNode;
		head->p = player;
		head->next = NULL;
	}
	cout << "Player " << playerName << " has been added!" << endl;
	playerCount++;
}

void Team::removePlayerFromTeam(const string playerName) {
	if (playerName == "") {
		cout << "Please enter a valid name!" << endl;
		return;
	}
	else if (findPlayer(playerName) == NULL) {
		cout << "Player " << playerName << " is not in the list!" << endl;
		return;
	}
	else if (playerCount < 1) {
		cout << "There is no player in the list!" << endl;
		return;
	}
	else {
		PlayerNode* cur = head;
		string nameGiven = playerName, nameFound = cur->p.getPlayerName();
		for (int i = 0; i < nameGiven.length(); i++)
			nameGiven[i] = tolower(nameGiven[i]);

		for (int i = 0; i < nameFound.length(); i++)
			nameFound[i] = tolower(nameFound[i]);

		if (nameGiven == nameFound) {
			PlayerNode* newPtr = cur;
			head = head->next;
			delete newPtr;
			playerCount--;
			if (playerDesCheck == false) {
				cout << "Player " << playerName << " has been deleted!" << endl;
			}
			return;
		}
		else {
			for (cur; cur->next != NULL; cur = cur->next) {
				nameFound = cur->next->p.getPlayerName();
				for (int i = 0; i < nameFound.length(); i++)
					nameFound[i] = tolower(nameFound[i]);

				if (nameGiven == nameFound) {
					PlayerNode* prev = cur->next;
					cur->next = cur->next->next;
					delete prev;
					playerCount--;
					cout << "Player " << playerName << " has been deleted!" << endl;
					return;
				}
			}
			return;
		}
	}
}

void Team::displayPlayersInTeam() {
	if (playerCount < 1)
		cout << "--EMPTY--" << endl;
	else {
		PlayerNode* cur = head;
		cout << cur->p.getPlayerName() << ", " << cur->p.getPosition() << endl;
		while (cur->next != NULL) {
			cur = cur->next;
			cout << cur->p.getPlayerName() << ", " << cur->p.getPosition() << endl;
		}
	}
	cout << endl;
	return;
}

Team::PlayerNode* Team::findPlayer(string playerName) const {
	string nameGiven = playerName;
	for (int i = 0; i < nameGiven.length(); i++)
		nameGiven[i] = tolower(nameGiven[i]);

	for (PlayerNode* cur = head; cur != NULL; cur = cur->next) {
		string nameFound = cur->p.getPlayerName();
		for (int i = 0; i < nameFound.length(); i++)
			nameFound[i] = tolower(nameFound[i]);

		if (nameGiven == nameFound)
			return cur;
	}
	return NULL;
}