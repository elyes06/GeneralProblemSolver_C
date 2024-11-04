#ifndef STRUCTURES_H
#define STRUCTURES_H



typedef char string[100];

struct data
{
    string nameAction;
    string preconds[10];
    string toAdd[10];
    string toDelete[10];
    int nb_preconds;
    int nb_toAdd;
    int nb_toDelete;
};

struct state{
    int indexAction;
    int size_TabFact;
    string tabFacts[50];
};

#endif