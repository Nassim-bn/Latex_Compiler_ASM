#include "func.h"

void add_asm() {
  printf("\tpop ax\n");
  printf("\tpop bx\n");
  printf("\tconst cx,errOverflow\n");
  printf("\tadd ax,bx\n");
  printf("\tjmpe cx\n");
  printf("\tpush ax\n");
}

void sub_asm() {
  printf("\tpop bx\n");
  printf("\tpop ax\n");
  printf("\tsub ax,bx\n");
  printf("\tpush ax\n");
}

void mult_asm() {
  printf("\tpop ax\n");
  printf("\tpop bx\n");
  printf("\tconst cx,errOverflow\n");
  printf("\tmul ax,bx\n");
  printf("\tjmpe cx\n");
  printf("\tpush ax\n");
}

void div_asm() {
  printf("\tpop bx\n");
  printf("\tpop ax\n");
  printf("\tconst cx,errDiv0\n");
  printf("\tdiv ax,bx\n");
  printf("\tjmpe cx\n");
  printf("\tpush ax\n");
}

void and_asm() {
  printf("\tpop bx\n");
  printf("\tpop ax\n");
  printf("\tand ax,bx\n");
  printf("\tpush ax\n");
}

void or_asm() {
  printf("\tpop bx\n");
  printf("\tpop ax\n");
  printf("\tor ax,bx\n");
  printf("\tpush ax\n");
}

void not_asm() {
  printf("\tpop bx\n");
  printf("\tnot bx\n");
  printf("\tpush bx\n");
}

void affectation(char *nom, function_symbol *head) {
  printf("\tpop dx\n");
  printf("\tcp bx,bp\n");
  printf("\tconst ax,%d\n", param_location(nom, head));
  printf("\tsub bx,ax\n");
  printf("\tstorew dx,bx\n");
}

void incr(char *nom, function_symbol *head) {
  get_param(nom, head);
  printf("\tconst ax,1\n");
  printf("\tadd dx,ax\n");
  printf("\tstorew dx,bx\n");
}

void decr(char *nom, function_symbol *head) {
  get_param(nom, head);
  printf("\tconst ax,1\n");
  printf("\tsub dx,ax\n");
  printf("\tstorew dx,bx\n");
}

void load_local_var_stack(function_symbol *f) {
  for (int i = 0; i < f->nb_local_var; i++) {
    printf("\tconst ax,0\n");
    printf("\tpush ax\n");
  }
}

void load_function_stack(function_symbol *f) {
  printf("\tpush bp\n");
  printf("\tcp bp,sp\n");
}

/*void test(){
 *  printf("\tpop ax\n");
 *  printf("\tpop bx\n");
 *  printf("\tcmp ax,bx\n");
 * }*/

void add_function_id(classe c, char *name, char *funcName, function_symbol *f) {
  symbol_table *p = malloc(sizeof(*p));
  if (p == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  function_symbol *q = search_function(funcName, f);
  if (q == NULL) {
    fprintf(stderr, "Function %s not found!", funcName);
    exit(EXIT_FAILURE);
  }
  p->sym_name = strdup(name);
  p->classe_t = c;
  p->nb_of_var = (c == GLOBALE_VARIABLE) ? nb_of_global_var : nb_of_local_var;
  p->next = f->table;
  f->table = p;
}

void add_function(char *name, int nbPar, int nbVar, function_symbol **f) {
  function_symbol *q = malloc((sizeof(*q)));
  if (q == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  q->func_name = strdup(name);
  q->nb_global_var = nbPar;
  q->nb_local_var = nbVar;
  q->table = NULL;
  q->next = *f;
  *f = q;
}

symbol_table *search_symbol_table(char *sName, symbol_table *s) {
  while (s != NULL) {
    if (strcmp(s->sym_name, sName) == 0) {
      return s;
    }
    s = s->next;
  }
  return NULL;
}

function_symbol *search_function(char *name, function_symbol *f) {
  while (f != NULL) {
    if (strcmp(f->func_name, name) == 0) {
      return f;
    }
    f = f->next;
  }
  return NULL;
}

void get_param(char *p, function_symbol *s) {
  printf("\tcp bx,bp\n");
  printf("\tconst ax,%d\n", param_location(p, s));
  printf("\tsub bx,ax\n");
  printf("\tloadw dx,bx\n");
  printf("\tpush dx\n");
}

void set_param(char *p, function_symbol *s) {
  printf("\tloadw bx,sp\n");
  printf("\tconst ax,%d\n", param_location(p, s));
}

int param_location(char *p, function_symbol *f) {
  symbol_table *sym = search_symbol_table(p, f->table);
  if (sym == NULL) {
    perror("search_symbol_table");
    exit(EXIT_FAILURE);
  }
  if (sym->classe_t == GLOBALE_VARIABLE) {
    return 2 + 2 * (f->nb_local_var) + 2 * (f->nb_global_var)
      - (sym->nb_of_var) * 2;
  }
  return 2 + 2 * (f->nb_local_var) - (sym->classe_t) * 2;
}

void return_from_func(function_symbol *f) {
  int n = 4 + f->nb_local_var * 2 + f->nb_global_var * 2;
  printf("\tcp bx,bp\n");
  printf("\tpop ax\n");
  printf("\tconst cx,%d\n", n);
  printf("\tsub bx,cx\n");
  printf("\tstorew ax,bx\n");
  printf("\tcp sp,bp\n");
  printf("\tpop bp\n");
  printf("\tret\n");
}
