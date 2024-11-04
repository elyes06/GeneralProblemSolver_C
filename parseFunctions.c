#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "parseFunctions.h"



int parseLine(char currentLine[], string container[])
{
    int i=0, nbWords=0;
  
    while(currentLine[i]!=':') 
    {
        i++;
    }
    i++; 
    int j=i;  
    while(currentLine[i]!='\n' && currentLine[i]!='\0')
    {
        if(currentLine[i]==',')
        {
            strncpy(container[nbWords], &currentLine[j], i-j < 100 ? i-j : 99); 
            container[nbWords][i-j < 100 ? i-j : 99] = '\0';
            nbWords++;
            j=i+1;
        }        
    i++;
    }
  return nbWords;
}



int parseFileLoadRules(FILE *file_ptr, int *sizeFactsInit, string *factsInit, int *sizeFactsGoal, string *factsGoal, char currentLine[], string container[], struct data *ActionsTab, string tabFact[]){
    int nbActions = 0;
    //Premiere partie pour le tableau START    
        fgets(currentLine,80,file_ptr);    
        //*sizeFactsInit = parseLine(currentLine,factsInit);
        *sizeFactsInit = parseLine(currentLine,tabFact);
        for (int i=0; i<*sizeFactsInit; i++)
        {
            printf("starts with : %s\n", tabFact[i]);
        }
    //Premiere partie pour le FINISH    
        fgets(currentLine,80,file_ptr);    
        *sizeFactsGoal = parseLine(currentLine,factsGoal);
        for (int i=0; i<*sizeFactsGoal; i++)
        {
            printf("to finish with: %s\n", factsGoal[i]); 
        }   
    //Deuxième partie     
        while(fgets(currentLine,80,file_ptr)!=NULL)
        {     
            fgets(currentLine,80,file_ptr); 
            // Passer la ligne "****"
            printf("\n");
            string aname[]={""};
            parseLine(currentLine, aname);
            strcpy(ActionsTab[nbActions].nameAction, aname[0]);
            printf("nom de l'action : %s\n", ActionsTab[nbActions].nameAction);
            // Lire les differentes preconds
            fgets(currentLine,80,file_ptr);
            ActionsTab[nbActions].nb_preconds = parseLine(currentLine, ActionsTab[nbActions].preconds);
            for (int i=0; i<ActionsTab[nbActions].nb_preconds; i++)
            {
                printf("preconds : %s\n", ActionsTab[nbActions].preconds[i]);
            }
            // Lire l'element a add
            fgets(currentLine,80,file_ptr);
            ActionsTab[nbActions].nb_toAdd = parseLine(currentLine, ActionsTab[nbActions].toAdd);
            for (int i=0; i<ActionsTab[nbActions].nb_toAdd; i++)
            {
                printf("to add : %s\n", ActionsTab[nbActions].toAdd[i]);
            }
            // Lire l'element a delete
            fgets(currentLine,80,file_ptr);
            ActionsTab[nbActions].nb_toDelete = parseLine(currentLine, ActionsTab[nbActions].toDelete);
            for (int i=0; i<ActionsTab[nbActions].nb_toDelete; i++)
            {
            printf("to delete : %s\n", ActionsTab[nbActions].toDelete[i]);
            }
            nbActions++;
        } 
        return nbActions;       
}
