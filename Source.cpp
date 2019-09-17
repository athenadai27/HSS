#include <iostream>
#include <string>
#include <assert.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <unordered_map> 
#include <vector>

using namespace std;

class StatList;
class Goal;
class GoalList;

const int reqNum = 5;

class Goal {
	public:
		Goal(string name) : g_name(name) { g_requirements[reqNum] = { 0 }; }
		Goal(int* reqs, string name) : g_name(name) { for (int i = 0; i < reqNum; i++) { g_requirements[i] = reqs[i]; } };
		int* getReqs() { return g_requirements; }
		string getName() { return g_name; }
		vector<Goal*> getChildren() { return g_children; }
	private:
		string g_name;
		int g_requirements[reqNum];
		vector<Goal*> g_children;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GoalDictionary {
	public:
		GoalDictionary(string name) : g_root(new Goal(name)), g_num(0) {};
		Goal* findGoal(string name);
		Goal* getRoot() { return g_root; }
		void insertGoal(string parent, Goal* newGoal);
		int getGoalNum() { return g_num; }
		unordered_map<string, Goal*> getMap() { return goalMap; }
	private:
		Goal* g_root;
		int g_num;
		unordered_map<string, Goal*> goalMap;
};

Goal* GoalDictionary::findGoal(string name) {
	return goalMap[name];
}

void GoalDictionary::insertGoal(string parent, Goal* newGoal) {
	Goal* parentGoal = this->findGoal(parent);
	parentGoal->getChildren().push_back(newGoal);
	goalMap.insert({ newGoal->getName(), newGoal });
	g_num++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GoalList : public GoalDictionary {
	public:
		GoalList(string name) : GoalDictionary(name) {};
		void deleteGoal(string goalName);
	private:
};

void GoalList::deleteGoal(string goalName) {
	Goal* toBeDeleted = this->findGoal(goalName);
	vector<Goal*>::iterator runThru = getRoot()->getChildren().begin; //UNDONE
	for (int i = 0; i < getRoot()->getChildren().size(); i++)
	{
		if (runThru[i] == toBeDeleted)
		{
			getRoot()->getChildren().erase(getRoot()->getChildren().begin() + i); //CHECK IF i, OR i - 1
		}
	}
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
		int statNum;
	};

	StatInd* stat_head;
	int justStatNums[reqNum];
};

StatList::StatList() {
	srand(time(0));
	stat_head = new StatInd();
	StatInd* stat_temp = stat_head;
	for (int i = 0; i < reqNum; i++)
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
	for (int i = 0; i < reqNum; i++)
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
	Character(string c) : c_name(c) { c_stats = new StatList(); c_goals = new GoalList("Character Goals"); };
	bool checkStats(string goalName);
	StatList* getStats() { return c_stats; }
	GoalList* getGoals() { return c_goals; }

private:
	string c_name;
	StatList* c_stats;
	GoalList* c_goals;
};

bool Character::checkStats(string goalName)
{
	Goal* tempGoal = getGoals()->findGoal(goalName);

	for (int i = 0; i < reqNum; i++)
	{
		if (getStats()->getStatNums()[i] < tempGoal->getReqs()[i])
			return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DayNightCycle {
public:
	DayNightCycle() : cycleCounter(0) {};
	void CycleIncrement() { (cycleCounter != 7) ? cycleCounter += 1 : cycleCounter = 0; }
private:
	int cycleCounter;
};

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
	g_goalDictionary = new GoalDictionary("Goal Dictionary");
	g_character = new Character(name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

	int unachievableGoalStats[reqNum] = { 100, 100, 100, 100, 100 };
	string goalName = "unachievableGoal";
	Goal* unachievableGoal = new Goal(unachievableGoalStats, goalName);

	string name = "Athena";
	Game* newGame = new Game(name);
	newGame->getCharacter()->getStats()->printOut();
	newGame->getCharacter()->getStats()->statChange("Creativity", reqNum, 0);
	newGame->getCharacter()->getGoals()->insertGoal("Character Dictionary", unachievableGoal);
	assert(!newGame->getCharacter()->checkStats("unachievableGoal"));
}