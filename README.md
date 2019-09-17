# HSS
HSS Game Prot

CHANGES:
- Replaced StatList linked list with unordered_map
- Created Task class
- Created TasksInDay class
- Game class now contains a Task* and TaskInDay*, and calculates tasks


DESCRIPTIONS OF CLASSES:

Student Class:
- Has a list of 5 stats
- Has a list of goals
- Checks to see if certain goals are passed

StatList Class:
- Contains an unordered_map of the students' stats
- de/increments the values of the students' goals

Goal Class:
- One single goal
- Has a series of stat requirements that must be met
- Has a string name
- Contains a vector of children goals

GoalsDictionary Class:
- Contains a root goal
- Contains a goal map for easier finding
- Can retrieve the root and specific goals

GoalsList Class:
- Performs just as GoalsDictionary class does, with the addendum of the ability to delete goals

DayNightCycle Class:
- Keeps track of the actions remaining in one unit of time

Task Class:
- Contains a task name and amount of time devoted to task, with functions to edit/retrieve both

TasksInDay Class:
- Contains a task counter to keep track of units of time left
- Contains a vector that holds pointers to tasks
- Stores new tasks with a name and amount of time devoted to it

Game Class:
- Contains a Character object
- Contains a GoalDictionary object
- Contains a TasksInDay object
- Contains a DayCycle object
- Calculates probability of a stat change (currently only does improvements) using modulus and random generation

TO IMPLEMENT:
- Function to implement a smaller-scale Goal Dictionary
- Function that will semi-randomly generate a character's goals
- Fix struct StatInd
- Fix deleteGoal function
- Implement deletion of maps in calculateTasks (or check if necessary)

QUESTIONS:
- Where should I initialise the Goal Dictionary?
- Is this (using vectors and maps) more optimal than trees?
- StatInd doesn't work if put as a struct in StatList (getStatMap() in line 94 fails). Moving it to global feels strange.
