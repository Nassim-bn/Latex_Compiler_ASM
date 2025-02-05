#ifndef INTERMEDIAIRE_H
#define INTERMEDIAIRE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

// ARG : Peut etre une comande mais aussi un argument pour gerer la liste
// intermediair
typedef enum arg {
  COM,
  ARG,
} arg;

// Commandes : Les commandes (instructions) qu'on peut avoir
typedef enum commande {
  AND_COM,
  OR_COM,
  NOT_COM,
  DIFF_COM,
  EQ_COM,
  SET_COM,
  INCR_COM,
  DECR_COM,
  ID_COM,
  NUM_COM,
  EMPTY_COM,
  FUNC_COM,
  CALL_COM,
  CALLED_COM,
  RETURN_COM,
  IF_COM,
  ELSE_COM,
  FI_COM,
  ARG_COM,
  ADD_COM,
  SUB_COM,
  MUL_COM,
  DIV_COM,
} commande;

// Liste intermediaire
typedef struct intermediate_list {
  commande com;
  arg type;
  char *name;
  function_symbol *function;
  struct intermediate_list *next;
} intermediate_list;

//Creer une liste intermediaire vide
void create_intermediate_list(intermediate_list *l);

//Ajout dans la liste intermediaire
void add_intermediate_list(intermediate_list **l, commande c, arg type_arg,
    char *arg, function_symbol *f);

//Vider la file
void clear_list(intermediate_list *l);

#endif
