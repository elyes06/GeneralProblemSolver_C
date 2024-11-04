#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"
#include "functions.h"


int findRuleToApply(string tabFact[], int size_TabFact, struct data ActionsTab[], int nbActions, int IR)
{
	int occurenceMatched = 0;
	for(int i=IR;i<nbActions && !occurenceMatched;i++)
	{	

		int occurenceCounter=0;
		for(int j=0;j<ActionsTab[i].nb_preconds;j++)
		{
			for(int k=0;k<size_TabFact;k++)
			{
				if(strcmp(ActionsTab[i].preconds[j],tabFact[k])==0)
				{
					occurenceCounter++;
					break;	
				}
			}
			if(occurenceCounter==ActionsTab[i].nb_preconds)
			{
				occurenceMatched = 1;
				break;
			}
		}
		if(occurenceMatched == 1)
		{
			return i;
		}
	}
	return -1;
}

void deletePreconds(string *tabFact_TMP, int *size_TabFact_TMP, struct data ActionsTab[], int appliableAction)
{
	
	//efface les case's 
	for(int nb=0; nb<ActionsTab[appliableAction].nb_toDelete ;nb++)
    {  
        for(int i=0;i<*size_TabFact_TMP;i++)
        {
            if(strcmp(ActionsTab[appliableAction].toDelete[nb],tabFact_TMP[i]) == 0)
            {
                strcpy(tabFact_TMP[i],"");
				break;  
            }
        }
    } 
	// implement new algo two pointer tech
	int spadeDeamon, skorpios; // deux pointeurs recherché par lfbi 

	spadeDeamon = 0;
	skorpios = 0;

			int i = 0;
			while(i < *size_TabFact_TMP){
				
				while(strcmp(tabFact_TMP[i], "") != 0){
					i++;
					skorpios = i;
				}

				if(spadeDeamon == 0){
					spadeDeamon = skorpios;
				}

				if(skorpios == *size_TabFact_TMP - ActionsTab[appliableAction].nb_toDelete){
					break;
				}


				while(strcmp(tabFact_TMP[spadeDeamon], "") == 0){
					
					spadeDeamon++;
				}

				strcpy(tabFact_TMP[skorpios], tabFact_TMP[spadeDeamon]);
				strcpy(tabFact_TMP[spadeDeamon], "");
				
			}

		(*size_TabFact_TMP) -= ActionsTab[appliableAction].nb_toDelete;

}
void addPreconds(string *tabFact_TMP, int *size_TabFact_TMP,struct data ActionsTab[],int appliableAction)
{
	
	int addExist = 0;
	int offset = ActionsTab[appliableAction].nb_toAdd;
	
	//solution deux trouver equation 

		for(int i =0; i< ActionsTab[appliableAction].nb_toAdd ; i++){

		for(int j = 0 ; j < *size_TabFact_TMP; j++){


			if(strcmp(ActionsTab[appliableAction].toAdd[i], tabFact_TMP[j]) == 0){
				addExist = 1;
				break;
			}
		}
			
		if(addExist){
			offset--;
			break;
		}


		for(int j = 0; j < *size_TabFact_TMP + offset; j++){
			
			if(strcmp(tabFact_TMP[j], "") == 0){
				strcpy(tabFact_TMP[j],  ActionsTab[appliableAction].toAdd[i]);
				break;

			}

		}
	
	}

	*size_TabFact_TMP += offset;

}	


int checkGoal(struct state **stateTab,int currentStateIndex, string factsGoal[], int sizeFactsGoal)
{
	int occurenceMatched = 0;
    int occurenceCounter=0;
		for(int k=0;k< sizeFactsGoal;k++)
		{
			
			for(int j=0;j<stateTab[currentStateIndex]->size_TabFact;j++)
			{
				if(strcmp(stateTab[currentStateIndex]->tabFacts[j],factsGoal[k])==0)
				{
					occurenceCounter++;
					break;	
				}
			}
			if(occurenceCounter==sizeFactsGoal)
			{
				printf("\n ! ! CONGRATULATION ! !  \n");
				occurenceMatched = 1;
				break;
			}
		}
	
    return occurenceMatched;
}







int applyRule(struct state **stateTab, struct data ActionsTab[], int *currentStateIndex, int appliableAction)
{
	
	string tabFact_TMP[50];
	int tabFact_TMP_SIZE = stateTab[*currentStateIndex]->size_TabFact;
	int ruleAlreadyExists=0;


	for(int i=0;i< stateTab[*currentStateIndex]->size_TabFact;i++)
	{	
		strcpy(tabFact_TMP[i],stateTab[*currentStateIndex]->tabFacts[i]);
	}
		
	deletePreconds(tabFact_TMP,&tabFact_TMP_SIZE,ActionsTab,appliableAction);
	addPreconds(tabFact_TMP,&tabFact_TMP_SIZE,ActionsTab,appliableAction);
	//prevent looping action
	for(int i=0; i<=*currentStateIndex; i++)
	{
		int occurenceCounter=0;
	
		for(int j=0; j<stateTab[i]->size_TabFact; j++)
		{
			for(int k=0; k<tabFact_TMP_SIZE; k++)
			{
				if(strcmp(stateTab[i]->tabFacts[j],tabFact_TMP[k]) == 0)
				{
					occurenceCounter++;
					break;
				}
			}		
		}
		if(occurenceCounter==tabFact_TMP_SIZE)
		{
			ruleAlreadyExists = 1;
			break;
		}
	}
	
	if(ruleAlreadyExists == 0)
	{
		*(currentStateIndex) = *(currentStateIndex)+1 ;

		printf(" We apply action: %d", appliableAction);
		stateTab = (struct state **) (realloc(stateTab, ((*(currentStateIndex) + 1) * sizeof(struct state *))));
		stateTab[*currentStateIndex] = (struct state *) (calloc(1,sizeof(struct state)));

		stateTab[*currentStateIndex]->size_TabFact = tabFact_TMP_SIZE;
		stateTab[*currentStateIndex]->indexAction = appliableAction;

		for(int i=0;i<stateTab[*currentStateIndex]->size_TabFact;i++)
		{
			strcpy(stateTab[*currentStateIndex]->tabFacts[i],tabFact_TMP[i]);
		}
		return 1;
	}
	else
	{
		printf("\n ********************************************* \n");
		printf(" ---Rule already exists---");
		printf("\n ********************************************* \n");
		return 0;
	}
}