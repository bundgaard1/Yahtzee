# Yahtzee
A program takes in a round of yahtzee and computes the greatest possible score.

This program was made for a challenge exercise in the course: Programming for Computer Engineering.

--------------------------------------------------
The Algorithm:
I have implemented 2 algorithms to solve the problem

Algo 1: Starts with the first throw, find which category gives the greatest return, and the use this catgory for the throw. The category is then used and cant be used by an other throw. This algorithm is very bad.

Algo 2: A prioritized list of the categories is made. This way the most important categories are calculated first. Each categorie is assigned to the throw which gives the best score for the categorie. This algorithm is better than the first, but does not calculate the best possible score.

---------------------------------------------------
