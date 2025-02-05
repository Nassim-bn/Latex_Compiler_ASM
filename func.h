#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern int nb_of_global_var;
extern int nb_of_local_var;

typedef enum {
  NUM_T,
  BOOL_T,
  ERR_T
} type_synth;

typedef enum {
  LOCALE_VARIABLE,
  GLOBALE_VARIABLE
} classe;

typedef struct function_symbol {
  char *func_name;
  int nb_global_var;
  int nb_local_var;
  struct symbol_table *table;
  struct function_symbol *next;
} function_symbol;

typedef struct symbol_table {
  char *sym_name;
  classe classe_t;
  int nb_of_var;
  struct symbol_table *next;
} symbol_table;

/*------------------------------------------------------------------------
 * Opérations assmebleur
 * -------------------------------------------------------------------------*/

//Addition
void add_asm();

//Soustraction
void sub_asm();

//Multiplication
void mult_asm();

//Division
void div_asm();

//Et
void and_asm();

//Ou
void or_asm();

//Not
void not_asm();

//Affectation du sommet de pile a x
void affectation(char *x, function_symbol *f);

//Incrémente x
void incr(char *x, function_symbol *f);

//Décremente x
void decr(char *x, function_symbol *f);

/*------------------------------------------------------------------------
 * Opérations table des symboles
 * -------------------------------------------------------------------------*/

//RETOUR : la nouvelle cellule de sym_tab crée par malloc (la gestion d'erreur
// se fait dans ajouter)

symbol_table *create_symbol();

//RETOUR : la nouvelle cellule de func_tab crée par malloc (la gestion d'erreur
// se fait dans ajouter)

function_symbol *create_function();

//Ajoute en tête de liste la nouvelle cellule qui contient l'identifiant

void add_function_id(classe c, char *name, char *funcName, function_symbol *f);

//Ajoute en tête de liste la nouvelle cellule qui contient la fonction

void add_function(char *name, int nbPar, int nbVar, function_symbol **f);

//Recherche l'identifiant dans la table des symboles

symbol_table *search_symbol_table(char *sName, symbol_table *s);

//Recherche la fonction dans la table des symboles

function_symbol *search_function(char *fName, function_symbol *f);

//Récupère le parametre p dans la pile
void get_param(char *p, function_symbol *f);

//Met le paramètre p dans la pile
void set_param(char *p, function_symbol *f);

//Recupère la position du paramètre sur la pile
int param_location(char *p, function_symbol *f);

//Gerer les variables locales
void load_local_var_stack(function_symbol *f);

//Gerer l'appel de la fonction
void load_function_stack(function_symbol *f);

//Gerer le retour des fonctions
void return_from_func(function_symbol *f);
#endif
