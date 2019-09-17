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
		GoalDictionary(string name) : g_root(new Goal(name)) {};
		Goal* findGoal(string name);
		Goal* getRoot() { return g_root; }
		void insertGoal(string parent, Goal* newGoal);
		unordered_map<string, Goal*> getMap() { return goalMap; }
	private:
		Goal* g_root;
		unordered_map<string, Goal*> goalMap;
};

Goal* GoalDictionary::findGoal(string name) {
	return goalMap[name];
}

void GoalDictionary::insertGoal(string parent, Goal* newGoal) {
	Goal* parentGoal = this->findGoal(parent);
	parentGoal->getChildren().push_back(newGoal);
	goalMap.insert({ newGoal->getName(), newGoal });
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

struct StatInd { // UNDONE
	string statName;
	int statNum;
};

class StatList : private StatInd {
public:
	StatList();
	void statChange(string name, int increment, bool deincrease);
	int* getStatNums() { return justStatNums; }
	unordered_map<string, StatInd*>* getStatMap() { return &statMap; }

private:
	int justStatNums[reqNum];
	unordered_map<string, StatInd*> statMap;
};

StatList::StatList() {
	srand(time(0));
	int tempNum;
	for (int i = 0; i < reqNum; i++)
	{
		StatInd* tempStat = new StatInd();

		tempNum = rand() % 100;
		while (tempNum < 10 || tempNum > 75)
			tempNum = rand() % 100;

		justStatNums[i] = tempNum;
		tempStat->statNum = tempNum;

		switch (i)
		{
			case 0:
				tempStat->statName = "Athletics";
				statMap.insert({ "Athletics", tempStat });
				break;
			case 1:
				tempStat->statName = "Interpersonality";
				statMap.insert({ "Interpersonality", tempStat });
				break;
			case 2:
				tempStat->statName = "Creativity";
				statMap.insert({ "Creativity", tempStat });
				break;
			case 3:
				tempStat->statName = "Logic";
				statMap.insert({ "Logic", tempStat });
				break;
			case 4:
				tempStat->statName = "Affluence";
				statMap.insert({ "Affluence", tempStat });
		}
	}
}

void StatList::statChange(string name, int increment, bool deincrease)
{
	StatInd* tempStat = statMap[name];
	if (deincrease == 0)
		tempStat += increment;
	else
		tempStat -= increment;
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

class TimeCycle {
	public:
		TimeCycle() : cycleCounter(0) {};
		void CycleIncrement() { (cycleCounter != 7) ? cycleCounter += 1 : cycleCounter = 0; }
	private:
		int cycleCounter;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Task {
	public:
		void setName(string name) { taskName = name; }
		void setAmountUsed(int amount) { amountUsed = amount; }
		int getAmountUsed() { return amountUsed; }
		string getName() { return taskName; }
	private:
		string taskName;
		int amountUsed;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TasksInDay : public Task {
	public:
		TasksInDay() : taskCounter(12) {};
		vector<Task*>* getProbabilities() { return &changeProbabilities; }
		void performTask(Task* newTask);
	private:
		vector<Task*> changeProbabilities;
		int taskCounter;
};

void TasksInDay::performTask(Task* newTask) {
	if (taskCounter != 0 && !((taskCounter - getAmountUsed()) < 0))
	{
		taskCounter -= getAmountUsed();
		changeProbabilities.push_back(newTask);
	}
	else
	{
		if (taskCounter == 0)
			cout << "You do not have any more time to devote today. Please move on to the next day." << endl;
		else
			cout << "You do not have enough time to devote to that task! You only have " << taskCounter << " amounts left." << endl;
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
		void calculateTasks();
	private:
		GoalDictionary* g_goalDictionary;
		Character* g_character;
		TasksInDay* g_tasks;
		TimeCycle* g_timeCycle;
};

Game::Game(string name) {
	g_goalDictionary = new GoalDictionary("Goal Dictionary");
	g_character = new Character(name);
}

void Game::calculateTasks() {
	while (g_tasks->getProbabilities.begin() != g_tasks->getProbabilities.end()) {
		Task* tempTask = g_tasks->getProbabilities.back();
		float tempProbability = (tempTask->getAmountUsed() / 12);
		int successNum = rand() % 11;
		if (tempProbability != 0)
		{
			if (tempProbability > successNum)
			{
				int statChange = tempProbability;
				statChange %= 4;
				this->getCharacter()->getStats()->statChange(g_tasks->getName(), statChange, 0);
			}
		}
		g_tasks->getProbabilities.pop_back();
	}
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
	newGame->getCharacter()->getStats()->statChange("Creativity", reqNum, 0);
	newGame->getCharacter()->getGoals()->insertGoal("Character Dictionary", unachievableGoal);
	assert(!newGame->getCharacter()->checkStats("unachievableGoal"));
}