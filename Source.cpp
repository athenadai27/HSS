#include <iostream>
#include <string>
#include <cassert>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <unordered_map> 
using namespace std;

class StatList;
class Goals;
class GoalsList;

class Goals {
public:
	Goals(int* reqs, string name) : g_name(name) { memcpy(reqs, g_requirements, sizeof(reqs)); };
	int* getReqs() { return g_requirements; }
	string getName() { return g_name; }
	void setHash(int i) { hashNum = i; }

	Goals* g_next;
private:
	string g_name;
	int g_requirements[5] = { 0 };
	int hashNum;
};

class GoalsList {
	public:
		GoalsList() : g_Num(0) {};
		void insertGoal(Goals* newGoal);
		Goals* getHead() { return g_head; }
	private:
		int g_Num;
		Goals* g_head;
};

void GoalsList::insertGoal(Goals* newGoal) {
	if (g_Num = 0)
		g_head = new Goals(newGoal->getReqs(), newGoal->getName());
	else
		g_head->g_next = new Goals(newGoal->getReqs(), newGoal->getName());
	g_Num++;
	newGoal->setHash(g_Num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StatList {
	public:
		StatList();
		void printOut();
		void statChange(string name, int increment, int deincrease);
	private:
		struct StatInd {
			string statName;
			StatInd* stat_next;
			int statNum ;
		};

		StatInd* stat_head;
};

StatList::StatList() {
	srand(time(0));
	stat_head = new StatInd();
	StatInd* stat_temp = stat_head;
	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
			case 0:
				stat_temp->statName = "Athletics";
				break;
			case 1:
				stat_temp->statName = "Interpersonality";
				break;
			case 2:
				stat_temp->statName = "Creativity";
				break;
			case 3:
				stat_temp->statName = "Logic";
				break;
			case 4:
				stat_temp->statName = "Affluence";
		}

		stat_temp->statNum = rand() % 100;
		while (stat_temp->statNum < 10 || stat_temp->statNum > 75)
			stat_temp->statNum = rand() % 100;

		if (i < 4)
		{
			stat_temp->stat_next = new StatInd();
			stat_temp = stat_temp->stat_next;
		}
		stat_temp->stat_next = NULL;
	}
}

void StatList::statChange(string name, int increment, int deincrease)
{
	StatInd* stat_temp = stat_head;
	for (int i = 0; i < 5; i++)
	{
		if (stat_temp->statName != name)
		{
			stat_temp = stat_temp->stat_next;
		}
		else
		{
			if (deincrease == 0)
				stat_temp->statNum += increment;
			else
				stat_temp->statNum -= increment;
			return;
		}
	}
}

void StatList::printOut() {
	StatInd* stat_temp = stat_head;
	while (stat_temp != NULL)
	{
		cout << stat_temp->statNum << endl;
		stat_temp = stat_temp->stat_next;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Character {
public:
	//Name
	Character(string c)
	{
		c_name = c;
	};
	// RNG stats
	// Goals
	bool checkGoals(int reqs[5]);

private:
	string c_name;
	StatList* c_stats;
	GoalsList* c_goals;
	unordered_map<int, Goals*> goalMap;
};

bool Character::checkGoals(int reqs[5])
{
	for (int i = 0; i < 5; i++)
	{
		if (reqs[i] < c_goals->getHead()->getReqs()[i])
			return false;
	}

	return true;
}

int main() {
	StatList x = StatList();
	x.printOut();
	x.statChange("Creativity", 5, 0);
	x.printOut();
}

