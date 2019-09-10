#include <iostream>
#include <string>
#include <assert.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <unordered_map> 
using namespace std;

class StatList;
class Goal;
class GoalsList;

const int goldNum = 5;

class Goal {
	public:
		Goal(int* reqs, string name) : g_name(name) { for (int i = 0; i < goldNum; i++) { g_requirements[i] = reqs[i]; } };
		int* getReqs() { return g_requirements; }
		string getName() { return g_name; }
		void setHash(int i) { hashNum = i; }

		Goal* g_right;
		Goal* g_left;
	private:
		string g_name;
		int g_requirements[goldNum];
		int hashNum;
};

class GoalsList {
	public:
		GoalsList() : g_Num(0) {};
		void insertGoal(Goal* newGoal);
		Goal* getHead() { return g_head; }
		int getGoalNum() { return g_Num; }
		void printOut() { 
			cout << endl;
			cout << g_Num << endl;
			cout << g_head->getName() << endl;
			for (int i = 0; i < goldNum; i++)
				cout << g_head->getReqs()[i] << endl;

		}
	private:
		int g_Num;
		Goal* g_head;
};

void GoalsList::insertGoal(Goal* newGoal) {
	if (g_Num == 0)
		g_head = new Goal(newGoal->getReqs(), newGoal->getName());
	else
	{
		g_head->g_right = new Goal(newGoal->getReqs(), newGoal->getName());
		g_head->g_right->g_left = g_head;
	}
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
		void statChange(string name, int increment, bool deincrease);
		int* getStatNums() { return justStatNums; }
		
	private:
		struct StatInd {
			string statName;
			StatInd* stat_next;
			int statNum ;
		};

		StatInd* stat_head;
		int justStatNums[goldNum];
};

StatList::StatList() {
	srand(time(0));
	stat_head = new StatInd();
	StatInd* stat_temp = stat_head;
	for (int i = 0; i < goldNum; i++)
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

		justStatNums[i] = stat_temp->statNum;

		if (i < 4)
		{
			stat_temp->stat_next = new StatInd();
			stat_temp = stat_temp->stat_next;
		}
		stat_temp->stat_next = NULL;
	}
}

void StatList::statChange(string name, int increment, bool deincrease)
{
	StatInd* stat_temp = stat_head;
	for (int i = 0; i < goldNum; i++)
	{
		if (stat_temp->statName != name)
		{
			stat_temp = stat_temp->stat_next;
		}
		else
		{
			if (deincrease)
				stat_temp->statNum -= increment;
			else
				stat_temp->statNum += increment;
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
		Character(string c) : c_name(c) { c_stats = new StatList(); c_goals = new GoalsList(); };
		bool checkStats(string goalName);
		StatList* getStats() { return c_stats; }
		GoalsList* getGoals() { return c_goals; }

	private:
		string c_name;
		StatList* c_stats;
		GoalsList* c_goals;
		unordered_map<int, Goal*> goalMap;
};

bool Character::checkStats(string goalName)
{
	Goal* temp = c_goals->getHead();
	while (temp != NULL)
	{
		if (goalName != temp->getName())
			temp = temp->g_right;
		else
			break;
	}

	if (temp->getName() != goalName)
		return false;

	for (int i = 0; i < goldNum; i++)
	{
		if (getStats()->getStatNums()[i] < temp->getReqs()[i])
			return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GoalDictionary {
	public:
		GoalDictionary();
		void printOut();
	private:
		GoalsList* GoalDicList[goldNum];
};

GoalDictionary::GoalDictionary() {
	string goalNames[goldNum] = { "Go to College", "Enlist in Military", "Go to Vocational School", "Become Manager of Restaurant", "Volunteer" };
	int goalStats[5*goldNum] = { 30, 50, 90, 80, 60, 90, 70, 40, 40, 40, 45, 70, 70, 70, 50, 35, 90, 65, 40, 40, 40, 90, 70, 50, 70 };
	int* tempGoalStats = goalStats;
	int goalPlacement = 0;
	for (int i = 0; i < goldNum; i++)
	{
		GoalDicList[i] = new GoalsList;
		GoalDicList[i]->insertGoal(new Goal(tempGoalStats, goalNames[i]));
		goalPlacement += goldNum;
		tempGoalStats = &goalStats[goalPlacement];
	}
}

void GoalDictionary::printOut() {
	for (int i = 0; i < goldNum; i++)
	{
		GoalDicList[i]->printOut();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Game {
	public:
		Game(string name);
		GoalDictionary* getDictionary() { return g_goalDictionary; }
		Character* getCharacter() { return g_character; }
	private:
		GoalDictionary* g_goalDictionary;
		Character* g_character;
};

Game::Game(string name) {
	g_goalDictionary = new GoalDictionary();
	g_character = new Character(name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

	int unachievableGoalStats[goldNum] = { 100, 100, 100, 100, 100 };
	string goalName = "unachievableGoal";
	Goal* unachievableGoal = new Goal(unachievableGoalStats, goalName);

	string name = "Athena";
	Game* newGame = new Game(name);
	newGame->getCharacter()->getStats()->printOut();
	newGame->getCharacter()->getStats()->statChange("Creativity", goldNum, 0);
	newGame->getCharacter()->getGoals()->insertGoal(unachievableGoal);
	newGame->getCharacter()->getGoals()->printOut();
	assert(!newGame->getCharacter()->checkStats("unachievableGoal"));
	newGame->getDictionary()->printOut();
}

