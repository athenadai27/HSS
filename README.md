# HSS
HSS Game Prot

CHANGES:
- Implemented overall "Game" function that initialises all others
- Actively established '5' as the "golden number"
- Began implementation of Goal Dictionary; split it into 5 separate binary trees, all handling different categories

DESCRIPTIONS OF CLASSES:

Student Class:
- Has a list of 5 stats that can be increased or decreased
- Has a list of goals that can be added to or removed
- Has a hashmap of goals for easier finding

StatList Class:
- Contains a list of the students' stats

GoalsList Class:
- Contains a list of goals

Goal Class:
- One single goal
- Has a series of stat requirements that must be met
- Has a hash number for easier finding
- Has a previous goal pointer and a next goal pointer

GoalsDictionary Class:
- Contains a pointer to the main character
- Contains a pointer to the goal dictionary

TO IMPLEMENT:
- Complete GoalsDictionary
- Function that will semi-randomly generate a character's goals

QUESTIONS:
- How do I most optimally implement all the information for the tree? How would I neatly initialise all the specific stat numbers, or the names?
- How do I most optimally implement the hash numbers? I find it hard to hash when splitting across five trees (especially as the GoalsList class implements hash numbers on a tree-by-tree basis, as seen in line 50)
