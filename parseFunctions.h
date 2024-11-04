#ifndef PARSE_FUNCTION_H
#define PARSE_FUNCTION_H



int parseLine(char currentLine[], string *container);
int parseFileLoadRules(FILE *file_ptr, int *sizeFactsInit, string *factsInit, int *sizeFactsGoal, string *factsGoal, char currentLine[], string container[], struct data *RulesTab, string tabFact[]);

#endif