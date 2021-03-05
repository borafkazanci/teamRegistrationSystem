#include "CompleteReg.h"

bool teamDesCheck = false;
CompleteReg::CompleteReg() {
	head = NULL;
	teamCount = 0;
	teamDesCheck = false;
}

CompleteReg::CompleteReg(const CompleteReg& systemToCopy) {
	teamCount = systemToCopy.teamCount;

	if (systemToCopy.head == NULL) {
		head = NULL;
	}
	else {
		head = new Node;
		head->t = systemToCopy.head->t;
		Node* newPtr = head;
		for (Node* ptr = systemToCopy.head->next; ptr != NULL; ptr = ptr->next) {
			newPtr->next = new Node;
			newPtr = newPtr->next;
			newPtr->t = ptr->t;
		}
		newPtr->next = NULL;
	}
}

CompleteReg::~CompleteReg() {
	while (teamCount > 0) {
		teamDesCheck = true;
		removeTeam(head->t.getName());
	}
}

CompleteReg& CompleteReg::operator=(const CompleteReg& right) {
	if (&right != this) {
		teamCount = right.teamCount;
		head = NULL;

		if (teamCount > 0) {
			Node* cur = right.head;
			Node* tempPtr = new Node;

			tempPtr->t = cur->t;
			tempPtr->next = NULL;
			head = tempPtr;
			cur = cur->next;
			
			Node* newPtr = head;
			for (cur; cur != NULL; cur = cur->next) {
				tempPtr = new Node;
				tempPtr->t = cur->t;
				newPtr->next = tempPtr;
				newPtr = newPtr->next;
			}
			newPtr->next = NULL;
			return *this;
		}
	}
	return *this;
}

Team& CompleteReg::operator[](const int index) {
	if (index > teamCount) {
		cout << "Index is wrong! It should be less than team number!" << endl;
	}
	else if (index == 0) {
		cout << head << endl;
		return head->t;
	}
	else {
		Node* cur = head;
		for (int i = 0; i < index; i++)
			cur = cur->next;
		cout << cur << endl;
		return cur->t;
	}
}

void CompleteReg::addTeam(const string tName, const string tColor, const int tyear) {
	if (tyear < 1800 || tyear > 2020) {
		cout << "Team year must be between years 1800 and 2020." << endl;
		cout << endl;
		return;
	}

	Team team = Team(tName, tColor, tyear);

	if (teamCount > 0) {
		if (findTeam(tName) != NULL) {
			cout << "There is a team with the same name!" << endl;
			return;
		}
		Node* cur = head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new Node;
		cur = cur->next;
		cur->t = team;
		cur->next = NULL;
	}
	else {
		head = new Node;
		head->t = team;
		head->next = NULL;
	}
	cout << "Team " << tName << " has been added!" << endl;
	teamCount++;
}

void CompleteReg::removeTeam(string teamName) {
	if (teamName == "") {
		cout << "Please enter a valid name!" << endl;
		return;
	}
	else if (findTeam(teamName) == NULL) {
		cout << "Team " << teamName << " is not in the list!" << endl;
		return;
	}
	else if (teamCount < 1) {
		cout << "There is no team in the list!" << endl;
		return;
	}
	else {
		Node* cur = head;
		string nameGiven = teamName, nameFound = cur->t.getName();
		for (int i = 0; i < nameGiven.length(); i++)
			nameGiven[i] = tolower(nameGiven[i]);

		for (int i = 0; i < nameFound.length(); i++)
			nameFound[i] = tolower(nameFound[i]);

		if (nameGiven == nameFound) {
			Node* newPtr = cur;
			head = head->next;
			delete newPtr;
			teamCount--;
			if (teamDesCheck == false) {
				cout << "Team " << teamName << " has been deleted!" << endl;
			}
			return;
		}
		else {
			for (cur; cur->next != NULL; cur = cur->next) {
				nameFound = cur->next->t.getName();
				for (int i = 0; i < nameFound.length(); i++)
					nameFound[i] = tolower(nameFound[i]);

				if (nameGiven == nameFound) {
					Node* prev = cur->next;
					cur->next = cur->next->next;
					delete prev;
					teamCount--;
					cout << "Team " << teamName << " has been deleted!" << endl;
					return;
				}
			}
			return;
		}
	}
}

void CompleteReg::displayAllTeams() const {
	cout << endl;
	if (teamCount < 1)
		cout << "--EMPTY--" << endl;
	else {
		Node* cur = head;
		cout << cur->t.getName() << ", " << cur->t.getColor() << ", " << cur->t.getYear() << endl;
		cur->t.displayPlayersInTeam();
		while (cur->next != NULL) {
			cur = cur->next;
			cout << cur->t.getName() << ", " << cur->t.getColor() << ", " << cur->t.getYear() << endl;
			cur->t.displayPlayersInTeam();
		}
	}
	cout << endl;
}

void CompleteReg::addPlayer(const string tName, const string pName, const string pPosition) {
	Node* teamNode = findTeam(tName);

	if (teamNode == NULL)
		cout << "Team " << tName << " is not in the list! Player " << pName << " cannot be added!" << endl;
	else if (teamNode->t.isPlayerExist(pName))
		cout << "Player " << pName << " is already in the " << tName << " !" << endl;
	else
		teamNode->t.addPlayerToTeam(pName, pPosition);
}

void CompleteReg::removePlayer(const string teamName, const string playerName) {
	Node* teamNode = findTeam(teamName);

	if (teamNode == NULL)
		cout << "Team " << teamName << " is not in the list! Player " << playerName << " cannot be deleted!" << endl;
	else if (teamNode->t.isPlayerExist(playerName) == false)
		cout << "There is no player named " << playerName << " in the " << teamName << " !" << endl;
	else 
		teamNode->t.removePlayerFromTeam(playerName);
}

void CompleteReg::displayTeam(const string teamName) const {
	cout << endl;
	Node* teamNode = findTeam(teamName);
	
	if (teamCount < 1 || teamNode == NULL)
		cout << "--EMPTY--" << endl;
	else {
		cout << teamName << ", " << teamNode->t.getColor() << ", " << teamNode->t.getYear() << endl;
		if (teamNode->t.getPlayerCount() < 1)
			cout << "--EMPTY--" << endl;
		else
			teamNode->t.displayPlayersInTeam();
	}
	cout << endl;
}

void CompleteReg::displayPlayer(const string playerName) const {
	cout << endl;
	cout << playerName << endl;

	if (teamCount < 1) 
		cout << "--EMPTY--" << endl;
	else {
		bool empty = true;
		for (Node* cur = head; cur != NULL; cur = cur->next) {
			if (cur->t.isPlayerExist(playerName)) {
				cout << cur->t.getPlayerPosition(playerName) << ", " << cur->t.getName() << ", " 
					<< cur->t.getColor() << ", " << cur->t.getYear() << endl;
				empty = false;
			}
		}
		if (empty)
			cout << "--EMPTY--" << endl;
	}
	cout << endl;
}

CompleteReg::Node* CompleteReg::findTeam(string teamName) const {
	string nameGiven = teamName;
	for (int i = 0; i < nameGiven.length(); i++)
		nameGiven[i] = tolower(nameGiven[i]);

	for (Node* cur = head; cur != NULL; cur = cur->next) {
		string nameFound = cur->t.getName();
		for (int i = 0; i < nameFound.length(); i++)
			nameFound[i] = tolower(nameFound[i]);

		if (nameGiven == nameFound)
			return cur;
	}
	return NULL;
}