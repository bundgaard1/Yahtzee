#pragma once

#include <stdbool.h>
#include <stdio.h>

#define THROWS 13
#define DICE 5
#define VALUES 6

// Define a Throw, that has 5 dice values, a score, which depends of the
// categorie og the Throw
typedef struct Throw {
  int dice_value[DICE];
  int score;
  int categorie;
} Throw;

// Define a Round as 13 throws, with a total score a bonus, and an array witch
// keeps track of which categorie belongs to which throw.
typedef struct Round {
  int score;
  Throw throws[THROWS];
  int bonus;
  int throw_categorie[THROWS];
} Round;

int of_a_kind(Throw t, int value) {
  int n = 0;
  for (int i = 0; i < DICE; i++) {
    if (t.dice_value[i] == value) {
      n++;
    }
  }
  return n;
}

bool is_short_sequence(Throw t, int start) {
  bool bol = true;
  for (int i = 0; i < 4; i++) {
    bool curr = false;
    for (int j = 0; j < DICE; j++) {
      if (t.dice_value[j] == i + start) {
        curr = true;
      }
    }
    if (!curr) {
      bol = false;
    }
  }

  if (bol) {
    return true;
  } else {
    return false;
  }
}

bool is_long_sequence(Throw t, int start) {
  bool bol = true;
  for (int i = 0; i < 5; i++) {
    bool curr = false;
    for (int j = 0; j < DICE; j++) {
      if (t.dice_value[j] == i + start) {
        curr = true;
      }
    }
    if (!curr) {
      bol = false;
    }
  }

  if (bol) {
    return true;
  } else {
    return false;
  }
}

// takes a pointer to a throw and a categorie, and scores the throw depending on
// the categorie. sets the t->score to the score
void score_throw(Throw* t, int cat) {
  int score = 0;

  // All categories
  switch (cat) {
    // ones
    case 0:
      for (int i = 0; i < DICE; i++) {
        if (t->dice_value[i] == 1) {
          score += 1;
        }
      }
      break;
    // twos
    case 1:
      for (int i = 0; i < DICE; i++) {
        if (t->dice_value[i] == 2) {
          score += 2;
        }
      }
      break;
    // threes
    case 2:
      for (int i = 0; i < DICE; i++) {
        if (t->dice_value[i] == 3) {
          score += 3;
        }
      }
      break;

    // fours
    case 3:
      for (int i = 0; i < DICE; i++) {
        if (t->dice_value[i] == 4) {
          score += 4;
        }
      }
      break;
    // fives
    case 4:
      for (int i = 0; i < DICE; i++) {
        if (t->dice_value[i] == 5) {
          score += 5;
        }
      }
      break;
    // sixes
    case 5:
      for (int i = 0; i < DICE; i++) {
        if (t->dice_value[i] == 6) {
          score += 6;
        }
      }
      break;
    // chance
    case 6:
      for (int i = 0; i < DICE; i++) {
        score += t->dice_value[i];
      }
      break;
    // three of a kind
    case 7:
      for (int i = 1; i <= VALUES; i++) {
        if (of_a_kind(*t, i) >= 3) {
          for (int i = 0; i < DICE; i++) {
            score += t->dice_value[i];
          }
        }
      }
      break;
    // four of a kind
    case 8:
      for (int i = 1; i <= VALUES; i++) {
        if (of_a_kind(*t, i) >= 4) {
          for (int i = 0; i < DICE; i++) {
            score += t->dice_value[i];
          }
        }
      }
      break;
    // five of a kind
    case 9:
      for (int i = 1; i <= VALUES; i++) {
        if (of_a_kind(*t, i) >= 5) {
          for (int i = 0; i < DICE; i++) {
            score = 50;
          }
        }
      }
      break;
    // short straight
    case 10:
      for (int i = 1; i < 4; i++) {
        if (is_short_sequence(*t, i)) {
          score = 25;
        }
      }

      break;
    // long straight
    case 11:
      for (int i = 1; i < 3; i++) {
        if (is_long_sequence(*t, i)) {
          score = 35;
        }
      }
      break;
    // full house
    case 12:
      for (int i = 1; i <= VALUES; i++) {
        if (of_a_kind(*t, i) == 3) {
          for (int j = 1; j <= VALUES; j++) {
            if (j == i) {
              continue;
            } else if (of_a_kind(*t, j) == 2) {
              score = 40;
            }
          }
        }
      }

      break;

    // Default, 0 =< cat =< 12
    default:
      // Categorie not found
      break;
  }

  t->score = score;
}

// Return the score of a throw
int score_of_throw(Throw t, int cat) {
  score_throw(&t, cat);
  return t.score;
}

// Takes a pointer to a round, and scores it, only if every throw has a
// categorie Also calculate bonus, sets r->score to the score.
void score_round(Round* r) {
  int totalScore = 0;
  // Add to score for each dice
  for (int i = 0; i < THROWS; i++) {
    score_throw(&r->throws[i], r->throws[i].categorie);
    totalScore += r->throws[i].score;
    r->throw_categorie[r->throws[i].categorie] = i;
  }

  r->bonus = 0;
  int firstSix = 0;
  // check if bonus is >= 63
  for (int i = 0; i < 6; i++) {
    int throwforcat = r->throw_categorie[i];
    firstSix += r->throws[throwforcat].score;
  }
  if (firstSix >= 63) {
    r->bonus = 35;
  }
  r->score = totalScore + r->bonus;
}

// Prints the "output line of integers"
void print_round(Round r) {
  for (int i = 0; i < THROWS; i++) {
    int throwForCat = r.throw_categorie[i];
    printf("%d ", r.throws[throwForCat].score);
  }
  printf("%d ", r.bonus);
  printf("%d \n", r.score);
}

// Return the categorie that gets the biggest score for the throw. used in
// best_score
int best_score_throw(Throw* t, bool catsUsed[THROWS]) {
  int biggestCat;
  int biggestCatScore;
  // Set biggestCat to the first false in catsUsed
  for (int i = 0; i < THROWS; i++) {
    if (catsUsed[i] == false) {
      biggestCat = i;
      biggestCatScore = score_of_throw(*t, i);
    }
  }
  for (int i = 0; i < THROWS; i++) {
    if (catsUsed[i]) {
      continue;
    }
    int catScore = score_of_throw(*t, i);
    if (catScore > biggestCatScore) {
      biggestCat = i;
      biggestCatScore = catScore;
    }
  }
  t->categorie = biggestCat;
  return biggestCat;
}

// The heart of the program
// sets every throw to the "best" categorie, every categorie should be used
// without doublicates.
void best_score_algo1(Round* r) {
  bool catsUsed[THROWS];
  for (int i = 0; i < THROWS; i++) {
    catsUsed[i] = false;
  }

  for (int i = 0; i < THROWS; i++) {
    Throw currThrow = r->throws[i];
    int bestCat = best_score_throw(&currThrow, catsUsed);
    catsUsed[bestCat] = true;
    r->throws[i].categorie = bestCat;
  }
}

int best_throw_cat(Round* r, int cat, bool throwsUsed[]) {
  int bestThrow;
  int bestThrowScore;
  // Set biggestCat to the first false in catsUsed
  for (int i = 0; i < THROWS; i++) {
    if (throwsUsed[i] == false) {
      bestThrow = i;
      bestThrowScore = score_of_throw(r->throws[i], i);
      break;
    }
  }
  for (int i = 0; i < THROWS; i++) {
    if (throwsUsed[i]) {
      continue;
    }
    int throwScore = score_of_throw(r->throws[i], cat);
    if (throwScore > bestThrowScore) {
      bestThrow = i;
      bestThrowScore = throwScore;
    }
  }
  r->throws[bestThrow].categorie = cat;
  return bestThrow;
}

// This algoritm goes through the categories one by one, and finds the best
// scoring throw for the categorie.
void best_score_algo2(Round* r) {
  bool throwUsed[THROWS];
  for (int i = 0; i < THROWS; i++) {
    throwUsed[i] = false;
  }

  int categoriePrio[THROWS] = {9, 12, 11, 10, 5, 8, 7, 4, 3, 6, 2, 1, 0};

  for (int i = 0; i < THROWS; i++) {
    int currCat = categoriePrio[i];
    int bestThrow = best_throw_cat(r, currCat, throwUsed);
    throwUsed[bestThrow] = true;
    r->throws[bestThrow].categorie = currCat;
  }
}

// prints all throws of the round For better view of the round.
void debugge_runde(Round r) {
  printf("\n");
  for (int i = 0; i < THROWS; i++) {
    printf("Throw: %2d ", i);
    printf("Dice: ");
    for (int j = 0; j < DICE; j++) {
      printf("%d ", r.throws[i].dice_value[j]);
    }
    printf("Cat: %2d ", r.throws[i].categorie);
    printf("Score: %2d\n", r.throws[i].score);
  }
  printf("Round score: %d \n", r.score);
  printf("Cat array: ");
  for (int i = 0; i < THROWS; i++) {
    printf("%d:%d, ", i, r.throw_categorie[i]);
  }
}