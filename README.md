# HSS
HSS Game Prot

Overall Plan:
Student has a list of 5 stats and a list of x Goals (will change over time as goals are met or not met). One will complete tasks that increase certain stats, to better complete certain goals.

Student Class:
- Has a list of 5 stats that can be increased or decreased
- Has a list of goals that can be added to or removed
- Has a hashmap of goals for easier finding

StatList Class:
- Contains a list of the students' stats

GoalsList Class:
- Contains a list of goals

Goals Class:
- One single goal
- Has a series of stat requirements that must be met
- Has a hash number for easier finding

TO IMPLEMENT:
- Overall goal tree (list of all goals)
- Win clause (what makes the player win?)

QUESTIONS:
- Is the current setup the most optimal?
    - Can/should the Goals class be a subclass/struct of GoalsList (much like how StatList was written)?
- Currently, the list of all goals, hashmap, etc. Will all be taken care of by main(). Is this optimal?
    - Should another function take care of it? Should another class?
