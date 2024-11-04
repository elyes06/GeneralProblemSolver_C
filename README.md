# General Problem Solver

Ce projet implémente un programme de raisonnement automatique permettant de résoudre divers problèmes en appliquant des règles sur un état initial pour atteindre un but spécifique. Ce solveur général est conçu pour explorer et appliquer des actions de manière systématique afin de trouver une solution, si elle existe.

## Objectif du projet

L'objectif de ce projet est de créer un programme capable de :
- Lire et analyser un fichier de règles et d'états initiaux/finals.
- Appliquer les règles et effectuer un raisonnement automatique pour atteindre l'état cible.
- Effectuer des retours en arrière (backtracking) si nécessaire pour explorer d'autres options lorsque le but ne peut pas être atteint directement.

## Fonctionnalités

- Chargement des règles depuis un fichier texte (ex: `monkey.txt`).
- Application des règles pour transformer l'état actuel vers un état objectif.
- Vérification de la réussite en comparant l'état courant à l'état cible.
- Retour en arrière (backtracking) pour tenter d'autres chemins si un blocage est rencontré.

## Structure du projet

- **`structures.h`** : Définit les structures de données utilisées pour les états, les règles et autres informations nécessaires.
- **`parseFunctions.h`** : Contient les fonctions pour parser les règles et les faits depuis un fichier.
- **`functions.h`** : Inclut les fonctions pour appliquer les règles, vérifier l'état final et gérer les opérations de backtracking.

## Utilisation

### Prérequis

Ce projet est écrit en C. Assurez-vous d'avoir un compilateur C installé (comme GCC) pour pouvoir exécuter le programme.

### Compilation

Compilez le projet en utilisant la commande suivante :
```bash
gcc main.c -o general_problem_solver
