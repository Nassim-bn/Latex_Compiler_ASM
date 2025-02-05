# Nom du Projet : Compilateur Latex

## Auteur

Ce projet a été réalisé par Nassim BENCHIKH

## À quoi sert ce programme ?
Ce programme est conçu pour compiler et exécuter des algorithmes écrits en LaTeX. Il vise à faciliter l'analyse syntaxique et lexicale des algorithmes LaTeX, en utilisant Flex et Bison pour générer un code assembleur capable d'exécuter l'algorithme.

## Ce qui fonctionne par rapport à la dernière version

Depuis la dernière version, les améliorations suivantes ont été apportées :
-  Fichiers Bison mieux structurés.
-  Gestion des booléens et des paramètres multiples en entrée.
-  Pas d'erreurs de compilation et exécution correcte sur n'importe quel algorithme incluant l'addition, la soustraction, la division, la multiplication, l'incrémentation et la décrémentation.
- Pas de fuites de ressources lors des allocations (vérifié avec Valgrind).



## Ce qui manque et les causes

Malgré les progrès réalisés, il reste encore quelques fonctionnalités et améliorations à implémenter :
- **Difficultés à gérer les algorithmes récursifs** : Les algorithmes récursifs posent des problèmes de gestion des appels récursifs.
- **Gestion des boucles** : Les boucles causent des erreurs de bus, rendant leur utilisation problématique.
- **Instructions conditionnelles (if)** : Les instructions conditionnelles `if` causent également des erreurs de bus.

Les principales raisons pour lesquelles ces fonctionnalités manquent sont [fournir les causes principales].

## Comment exécuter le programme

Pour exécuter ce programme, suivez les étapes ci-dessous :


1. **compiler a l'aide du makefile** :
    ```bash
    make
    ```
2. **Exeuter et generer le fichier assembleur** :
    ```bash
    ./latex < [fichier de test] > latex.asm 
    ```
3. **Gener le code intermediare asipro et rediriger en sortie d'erreurs** :
    ```bash
    asipro latex.asm latex 2> latex.log
    ```
4. **Afficher le resultat avec sipro** :
    ```bash
    sipro latex
    ```

## Fichiers de test
Le projet inclut également des fichiers de test pour vérifier les différentes fonctionnalités du programme. Le projet ne gérant malheureusement pas les boucles et les conditions, 3 fichiers de test ont été inclus pour couvrir les opérations suivantes : opérations arithmétiques, booléens, incrémentation et décrémentation. 
