#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "parseFunctions.h"
#include "functions.h"


int main()
{
    FILE *file_ptr = fopen("monkey.txt","r");
    int sizeFactsInit, sizeFactsGoal;
    string factsInit[20], factsGoal[20];
    char currentLine[80];
    string container[80];
    struct data ActionsTab[20];
    int currentStateIndex = 0;

    struct state **stateTab = (struct state**) (malloc(sizeof(struct state *)));
    stateTab[0] = (struct state*) (calloc(1,sizeof(struct state)));

      
    

    int nbActions = parseFileLoadRules(file_ptr,&sizeFactsInit, factsInit,&sizeFactsGoal,factsGoal,currentLine,container,ActionsTab,stateTab[0]->tabFacts);
    stateTab[currentStateIndex]->size_TabFact = sizeFactsInit;
    stateTab[currentStateIndex]->indexAction = -1;

   
    int appliableAction;

    
    printf("\n ********************************************* \n");
    for(int i=0;i<stateTab[currentStateIndex]->size_TabFact;i++)
    {
        printf(" Start state:---------- %s\n", stateTab[currentStateIndex]->tabFacts[i]);
    }
    printf("\n ********************************************* \n");
    

    int applySuccess = 0;
    int possible = 1;
    int IR = 0;
    
    while(possible && !(checkGoal(stateTab,currentStateIndex,factsGoal,sizeFactsGoal)))
    {
        appliableAction = findRuleToApply(stateTab[currentStateIndex]->tabFacts,stateTab[currentStateIndex]->size_TabFact,ActionsTab,nbActions,IR);
        
        if(appliableAction != -1)
        {
            applySuccess = applyRule(stateTab,ActionsTab,&currentStateIndex,appliableAction);

            if(applySuccess == 1)
            {
                printf("\n ********************************************* \n");
                for(int i=0;i< stateTab[currentStateIndex]->size_TabFact;i++)
                { 
       	 	        printf(" Current State Apply Success :---------- %s\n", stateTab[currentStateIndex]->tabFacts[i]);
                }
                printf("\n ********************************************* \n");
                IR = 0;
            }
            else
            {   
                printf("\n ********************************************* \n");
                for(int i=0;i< stateTab[currentStateIndex]->size_TabFact;i++)

                {
       	 	        printf(" Current State when the new state already exists:---------- %s\n", stateTab[currentStateIndex]->tabFacts[i]);
                }
                printf("\n ********************************************* \n");
                IR = appliableAction + 1;
                continue;
            }
        }
        else//backtrack
        {
            if(currentStateIndex != 0)
            {
                IR = stateTab[currentStateIndex]->indexAction+1;
                free(&stateTab[currentStateIndex]);

                currentStateIndex--;
                printf("\n ********************************************* \n");
                for(int i=0;i< stateTab[currentStateIndex]->size_TabFact;i++)
                {
       	 	        printf(" Current State when backtracking  :---------- %s\n", stateTab[currentStateIndex]->tabFacts[i]);
                }
                printf("\n ********************************************* \n");
            }
            else
            {
                possible = 0;
                printf("Impossible.\n");
            }   
        }
    }
                printf("\n ********************************************* \n");
                for(int i=0;i< stateTab[currentStateIndex]->size_TabFact;i++)
                { 
       	 	        printf(" Final State :---------- %s\n", stateTab[currentStateIndex]->tabFacts[i]);
                }
                printf("\n ********************************************* \n");
}
