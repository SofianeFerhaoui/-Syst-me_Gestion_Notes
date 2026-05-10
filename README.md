# Système de Gestion de Notes Étudiantes en C

Projet personnel développé en langage C dans le cadre de ma Licence 1 Informatique (parcours MATHS-INFO) à l'Université de Picardie Jules Verne.

## Description

Ce programme permet à un professeur de gérer les dossiers de ses étudiants via un menu interactif en terminal. Les données sont lues depuis un fichier texte, et plusieurs algorithmes de tri et de recherche ont été implémentés en langage C.

## Fonctionnalités

- Afficher tous les étudiants
- Calculer la moyenne de la classe
- Trouver le meilleur et le moins bon étudiant
- Rechercher un étudiant par nom (recherche séquentielle)
- Trier par moyenne décroissante (tri par insertion)
- Trier alphabétiquement et recherche dichotomique
- Menu interactif

## Notions algorithmiques couvertes

- Structures de données : struct et tableaux statiques
- Lecture et écriture de fichiers avec fscanf et fopen
- Tri par insertion croissant et décroissant
- Recherche séquentielle
- Recherche dichotomique sur tableau trié
- Menu interactif avec boucle do-while

## Format du fichier de données

Chaque ligne représente un étudiant :
NOM PRENOM NOTE_MATHS NOTE_ALGO NOTE_BDD

Exemple :
Ahmed Benali 17.0 16.5 19.0
Yanis Hessas 15.5 12.0 18.0
Marie Dupont 10.0 14.5 9.5
Lea Martin 8.0 11.0 13.5

## Compilation et exécution

gcc program.c -o programme
./programme

## Au

FERHAOUI Sofiane
Licence 1 Informatique — parcours MATHS-INFO
Université de Picardie Jules Verne, Amiens
2025 – 2026
