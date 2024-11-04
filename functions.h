#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int findRuleToApply(string tabFact[], int size_TabFact, struct data Rule[], int nbActions, int IR);
void deletePreconds(string *tabFact_TMP, int *size_TabFact_TMP, struct data ActionsTab[], int appliableAction);
void addPreconds(string *tabFact_TMP, int *size_TabFact,struct data ActionsTab[],int appliableAction);
int applyRule(struct state **stateTab, struct data ActionsTab[], int *currentStateIndex, int appliableAction);
int checkGoal(struct state **stateTab,int currentStateIndex, string factsGoal[], int sizeFactsGoal);

#endif