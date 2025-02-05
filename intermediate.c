#include "intermediate.h"
#include <stdio.h>
#include "func.h"

// Creer la liste intermediaire
void create_intermediate_list(intermediate_list *l) {
  printf("\tconst ax,debut\n");
  printf("\tjmp ax\n");
  printf(":nl\n");
  printf("@string \"\\n\"\n");
  printf(":msgErrDiv0\n");
  printf("@string \"Erreur division par 0\\n\"\n");
  printf(":errDiv0\n");
  printf("\tconst ax,msgErrDiv0\n");
  printf("\tcallprintfs ax\n");
  printf("\tend\n");
  printf(":msgErrOverflow\n");
  printf("@string \"Erreur dépassement de capacité\\n\"\n");
  printf(":errOverflow\n");
  printf("\tconst ax,msgErrOverflow\n");
  printf("\tcallprintfs ax\n");
  printf("\tend\n");
  while (l != NULL) {
    switch (l->com) {
      case ADD_COM:
        add_asm();
        break;
      case SUB_COM:
        sub_asm();
        break;
      case MUL_COM:
        mult_asm();
        break;
      case DIV_COM:
        div_asm();
        break;
      case AND_COM:
        and_asm();
        break;
      case OR_COM:
        or_asm();
        break;
      case NOT_COM:
        not_asm();
        break;
      case SET_COM:
        affectation(l->name, l->function);
        break;
      case INCR_COM:
        incr(l->name, l->function);
        break;
      case DECR_COM:
        decr(l->name, l->function);
        break;
      case ID_COM:
        get_param(l->name, l->function);
        break;
      case NUM_COM:
        printf("\tconst ax,%d\n", (atoi(l->name)));
        printf("\tpush ax\n");
        break;
      case IF_COM:
        break;
      case EMPTY_COM:
        break;
      case FUNC_COM:
        printf(":%s\n", l->function->func_name);
        load_function_stack(l->function);
        break;
      case CALL_COM:
        printf(":debut\n");
        printf("\tconst bp,pile\n");
        printf("\tconst sp,pile\n");
        printf("\tconst ax,2\n");
        printf("\tsub sp,ax\n");
        // Valeur de retour
        printf("\tconst ax,0\n");
        printf("\tpush ax\n");
        break;
      case CALLED_COM:
        load_local_var_stack(l->function);
        printf("\tconst ax,%s\n", l->function->func_name);
        printf("\tcall ax\n");
        for (int i = 0;
            i < l->function->nb_local_var + l->function->nb_global_var; i++) {
          printf("\tpop ax\n");
        }
        printf("\tcp ax,sp\n");
        printf("\tcallprintfd ax\n");
        printf("\tconst ax,nl\n");
        printf("\tcallprintfs ax\n");
        printf("\tend\n");
        printf(":pile\n");
        printf("@int 0\n");
        break;
      case RETURN_COM:
        return_from_func(l->function);
        break;
      case ARG_COM:
      default:
        break;
    }
    l = l->next;
  }
}

// Detruire la liste intermediaire en libérant toutes les ressources
void clear_list(intermediate_list *l) {
  intermediate_list *p = l;
  while (p != NULL) {
    intermediate_list *q = p;
    p = p->next;
    if (q->type == ARG) {
      free(q->name);
    }
    free(p);
  }
}

// Ajouter un element a la liste intermediaire
void add_intermediate_list(intermediate_list **head, commande c, arg type,
    char *arg, function_symbol *f) {
  intermediate_list *p = malloc(sizeof(*p));
  if (p == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  p->type = type;
  if (type == COM) {
    p->name = NULL;
  } else {
    p->name = strdup(arg);
  }
  p->com = c;
  p->function = f;
  p->next = NULL;
  if (*head == NULL) {
    *head = p;
  } else {
    intermediate_list *q = *head;
    while (q->next != NULL) {
      q = q->next;
    }
    q->next = p;
  }
}
