/*
By: Mathias Jørgensen
Yahtzee
Challenge exercise - week 5
This program takes in a game of yahtzee and computes the best possible score for
the round.
The Algorithm is not correct though. However pretty good.

*/

#include "yahtzee.h"

#include <stdio.h>

void scan_input(Round *a) {
  for (int i = 0; i < THROWS; i++) {
    for (int j = 0; j < DICE; j++) {
      scanf("%d", &a->throws[i].dice_value[j]);
    }
  }
}

int main() {
  Round runde;
  scan_input(&runde);
  best_score_algo2(&runde);
  score_round(&runde);

  print_round(runde);

  debugge_runde(runde);

  return 0;
}
