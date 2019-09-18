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
		Goal(string name, int* reqs) : g_name(name) { for (int i = 0; i < reqNum; i++) { g_requirements[i] = reqs[i]; } };
		int* getReqs() { return g_requirements; }
		string getName() { return g_name; }
		vector<Goal*>* getChildren() { return &g_children; }
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
		GoalDictionary(string name) : g_root(new Goal(name)) { goalMap.insert({ name, g_root }); };
		Goal* findGoal(string name);
		Goal* getRoot() { return g_root; }
		void insertGoal(string parent, Goal* newGoal);
		unordered_map<string, Goal*> getMap() { return goalMap; }
	private:
		Goal* g_root;
		unordered_map<string, Goal*> goalMap;
};

Goal* GoalDictionary::findGoal(string name) {
	if (goalMap[name] == NULL)
		cout << "Goal not found. Please enter another name." << endl;
	return goalMap[name];
}

void GoalDictionary::insertGoal(string parent, Goal* newGoal) {
	Goal* parentGoal = this->findGoal(parent);
	parentGoal->getChildren()->push_back(newGoal);
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
	vector<Goal*>::iterator runThru = getRoot()->getChildren()->begin(); //UNDONE
	for (int i = 0; i < getRoot()->getChildren()->size(); i++)
	{
		if (runThru[i] == toBeDeleted)
		{
			getRoot()->getChildren()->erase(getRoot()->getChildren()->begin() + i); //CHECK IF i, OR i - 1
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
	for (int i = 0; i < reqNum + 1; i++)
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
				break;
		}
	}

	StatInd* tempStat = new StatInd();
	tempStat->statName = "Sleep";
	tempStat->statNum = reqNum * reqNum;
	statMap.insert({ "Sleep", tempStat });
}

void StatList::statChange(string name, int increment, bool deincrease)
{
	StatInd* tempStat = statMap[name];
	if (deincrease == 0)
		tempStat->statNum += increment;
	else
		tempStat->statNum -= increment;
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

class CycleCounters {
	public:
		CycleCounters() : weekCounter(0), sleepCounter(reqNum * reqNum), taskCounter(12) {};
		void weekIncrement() { (weekCounter != 7) ? weekCounter += 1 : weekCounter = 0; }
		void sleepDecrement() { sleepCounter -= 5; }
		void taskDecrement(int amount) {
			if (taskCounter - amount >= 0)
				taskCounter -= amount;
			else
				cout << "There is not enough time left. You only have " << taskCounter << " units left to alot." << endl;
		}

		bool checkSleep() {
			if (sleepCounter <= reqNum)
			{
				cout << "You're too tired to do anything else. You have to sleep at least " << sleepCounter << " units of time." << endl;
				return false;
			}

			return true;
		}

		bool checkTasks(){
			if (taskCounter == 0)
			{
				cout << "There is no time left to do more things. Time for a new day..." << endl;
				return false;
			}

			return true;
		}

		int getWeekCounter() { return weekCounter; }
		int getSleepCounter() { return sleepCounter; }
		int getTaskCounter() { return taskCounter; }
	private:
		int weekCounter;
		int sleepCounter;
		int taskCounter;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Task {
	public:
		void setTask() {
			cout << "Please enter a task name." << endl;
			cin >> taskName;
			cout << "Please enter how much time you want to spend." << endl;
			cin >> amountUsed;
		}
		int getAmountUsed() { return amountUsed; }
		string getName() { return taskName; }
	private:
		string taskName;
		int amountUsed;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TasksInDay : public Task, public CycleCounters {
	public:
		vector<Task*>* getTaskList() { return &taskList; }
	private:
		vector<Task*> taskList;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Game {
	public:
		Game(string name);
		GoalDictionary* getDictionary() { return g_goalDictionary; }
		Character* getCharacter() { return g_character; }
		void performTasks();
		void calculateTasks();
		void generateDictionary();
	private:
		GoalDictionary* g_goalDictionary;
		Character* g_character;
		TasksInDay* g_tasks;
		CycleCounters* g_cycleCounters;
};

Game::Game(string name) {
	g_goalDictionary = new GoalDictionary("Goal Dictionary");
	g_character = new Character(name);
	generateDictionary();
}

void Game::performTasks() {
	cout << "Currently, it is day " << g_tasks->getWeekCounter() << ". You have " << g_tasks->getTaskCounter() << " left to spend." << endl;
	Task* tempTask = new Task();
	tempTask->setTask();
	if (tempTask->getName() == "Sleep" || g_tasks->checkSleep())
	{
		g_tasks->getTaskList()->push_back(tempTask);
	}

	if (!(g_tasks->checkTasks()))
	{
		calculateTasks();
		g_tasks->weekIncrement();
	}
}

void Game::calculateTasks() {
	while (g_tasks->getTaskList()->begin() != g_tasks->getTaskList()->end()) {
		Task* tempTask = g_tasks->getTaskList()->back();
		if (tempTask->getName() == "Sleep") {
			this->getCharacter()->getStats()->statChange(g_tasks->getName(), g_tasks->getAmountUsed(), 0);
		}
		else {
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
			g_tasks->getTaskList()->pop_back();
		}
	}
}

void Game::generateDictionary() {
	{
		string parentName = "Goal Dictionary";
		string goalName = "Go to College";
		int goalStats[reqNum] = { 30, 50, 90, 80, 60 };

		g_goalDictionary->insertGoal(parentName, new Goal(goalName, goalStats));
	}
	{
		string parentName = "Goal Dictionary";
		string goalName = "Enlist in Military";
		int goalStats[reqNum] = { 90, 70, 40, 40, 40 };

		g_goalDictionary->insertGoal(parentName, new Goal(goalName, goalStats));
	}
	{
		string parentName = "Go to College";
		string goalName = "Go to Vocational School";
		int goalStats[reqNum] = { 45, 70, 70, 70, 50 };
		g_goalDictionary->insertGoal(parentName, new Goal(goalName, goalStats));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

	string name = "Athena";
	Game* newGame = new Game(name);
}