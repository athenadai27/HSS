# HSS
HSS Game Prot

CHANGES:
- Made GoalList a public derived class of GoalDictionary
- Replaced Goal class' tree with vectors instead
- Implemented goalMap using set <string name, Goal*>
- Removed "g_num" (number of goals) variable
- Created "DayNightCycle" class
- Created "Game" class

DESCRIPTIONS OF CLASSES:

Student Class:
- Has a list of 5 stats
- Has a list of goals
- Checks to see if certain goals are passed

StatList Class:
- Contains a list of the students' stats
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

Game Class:
- Contains a character class
- Contains a goal dictionary class

TO IMPLEMENT:
- Function to implement a smaller-scale Goal Dictionary
- Function that will semi-randomly generate a character's goals
- Function to "gamify"; accepts user inputs and changes systems/classes accordingly

QUESTIONS:
- Where should I initialise the Goal Dictionary?
- Is this more optimal than trees?
- What actions should be delegated to the Game Class?
