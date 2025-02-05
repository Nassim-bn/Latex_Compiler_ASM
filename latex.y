%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "intermediate.h"

char env[256];

intermediate_list *liste_inter;
int nb_of_global_var;
int nb_of_local_var;

function_symbol *f;
function_symbol *function_ptr;

int yylex();
void yyerror(const char* s){
    fprintf(stderr,"yyerror :%s\n",s);
}

%}

%define parse.error verbose


%union{
    int entier;
    char *id;
    type_synth type_s;
}

%type<type_s> EXPR
%token<entier> NUM
%token<id> ID
%token BEGIN_ALGO END SET IF FI ELSE DOFORI OD INCR DECR CALL RETURN;
%token DIFF AND EQ OR NOT TRUE FALSE;

%left EQ DIFF
%left OR
%left AND
%left NOT
%left '+' '-'
%left '/' '*'

%start S

%%

S : DEBUT PARAMETRES BLOC FIN APPEL;

DEBUT : BEGIN_ALGO '{' ID '}'                                                                                               {
                                                                                                                              add_function($3,0,0,&f);
                                                                                                                              function_ptr=search_function($3,f);
                                                                                                                              add_intermediate_list(&liste_inter,FUNC_COM,ARG,$3,function_ptr);
                                                                                                                              nb_of_global_var=0;
                                                                                                                              nb_of_local_var=0;
                                                                                                                            };

FIN : RETURN '{' EXPR '}' END                                                                                              {
                                                                                                                              add_intermediate_list(&liste_inter,RETURN_COM,COM,NULL,function_ptr);
                                                                                                                              };

PARAMETRES : '{' PARAMETRES_LIST '}'                                                                                     {function_ptr->nb_global_var=nb_of_global_var;
                                                                                                                              add_intermediate_list(&liste_inter,EMPTY_COM,COM,NULL,function_ptr);
                                                                                                                              };

PARAMETRES_LIST:
    | ID                                                                                                                    {

                                                                                                                              add_function_id(GLOBALE_VARIABLE,$1,function_ptr->func_name,f);
                                                                                                                              nb_of_global_var++;
                                                                                                                              add_intermediate_list(&liste_inter,ARG_COM,COM,NULL,function_ptr);
                                                                                                                              }
    | PARAMETRES_LIST ',' ID                                                                                               {

                                                                                                                                add_function_id(GLOBALE_VARIABLE,$3,function_ptr->func_name,f);
                                                                                                                                nb_of_global_var++;
                                                                                                                                add_intermediate_list(&liste_inter,ARG_COM,COM,NULL,function_ptr);
                                                                                                                                };

BLOC: INSTR BLOC | ;

EXPR: EXPR '+' EXPR                                                                                                                 {
                                                                                                                                      if($1 == ERR_T || $3 == ERR_T || $1 != $3){
                                                                                                                                          $$ = ERR_T;
                                                                                                                                          } else {
                                                                                                                                              $$=NUM_T;
                                                                                                                                              add_intermediate_list(&liste_inter,ADD_COM,COM,NULL,function_ptr);

                                                                                                                                          }
                                                                                                                                    }
    | EXPR '-' EXPR                                                                                                                  {
                                                                                                                                          if($1 == ERR_T || $3 == ERR_T || $1 != $3){
                                                                                                                                              $$ = ERR_T;
                                                                                                                                          } else {
                                                                                                                                              $$=NUM_T;
                                                                                                                                             add_intermediate_list(&liste_inter,SUB_COM,COM,NULL,function_ptr);
                                                                                                                                          }
                                                                                                                                      }
    | EXPR '*' EXPR                                                                                                                  {
                                                                                                                                          if($1 == ERR_T || $3 == ERR_T || $1 != $3){
                                                                                                                                              $$ = ERR_T;
                                                                                                                                          } else {
                                                                                                                                              $$=NUM_T;
                                                                                                                                              add_intermediate_list(&liste_inter,MUL_COM,COM,NULL,function_ptr);
                                                                                                                                          }
                                                                                                                                      }
    | EXPR '/' EXPR                                                                                                                   {
                                                                                                                                            if($1 == ERR_T || $3 == ERR_T || $1 != $3){
                                                                                                                                                $$ = ERR_T;
                                                                                                                                            } else {
                                                                                                                                                $$=NUM_T;
                                                                                                                                                add_intermediate_list(&liste_inter,DIV_COM,COM,NULL,function_ptr);
                                                                                                                                            }
                                                                                                                                        }
    | EXPR AND EXPR                                                                                                                     {
                                                                                                                                            if($1 == ERR_T || $3 == ERR_T || $1 != $3){
                                                                                                                                                $$ = ERR_T;
                                                                                                                                            } else {
                                                                                                                                                $$=BOOL_T;
                                                                                                                                               add_intermediate_list(&liste_inter,AND_COM,COM,NULL,function_ptr);
                                                                                                                                            }
                                                                                                                                        }
    | EXPR OR EXPR                                                                                                                     {
                                                                                                                                            if($1 == ERR_T || $3 == ERR_T || $1 != $3){
                                                                                                                                                $$ = ERR_T;
                                                                                                                                            } else {
                                                                                                                                                $$=BOOL_T;
                                                                                                                                               add_intermediate_list(&liste_inter,OR_COM,COM,NULL,function_ptr);
                                                                                                                                            }
                                                                                                                                        }
    | EXPR DIFF EXPR                                                                                                                     {
                                                                                                                                            if($1 == ERR_T || $3 == ERR_T || $1 != $3){
                                                                                                                                                $$ = ERR_T;
                                                                                                                                            } else {
                                                                                                                                                $$=BOOL_T;
                                                                                                                                               add_intermediate_list(&liste_inter,DIFF_COM,COM,NULL,function_ptr);
                                                                                                                                            }
                                                                                                                                        }
    | EXPR EQ EXPR                                                                                                                     {
                                                                                                                                            if($1 == ERR_T || $3 == ERR_T || $1 != $3){
                                                                                                                                                $$ = ERR_T;
                                                                                                                                            } else {
                                                                                                                                                $$=BOOL_T;
                                                                                                                                               add_intermediate_list(&liste_inter,EQ_COM,COM,NULL,function_ptr);
                                                                                                                                            }
                                                                                                                                        }
    | NOT EXPR                                                                                                                          {
                                                                                                                                            if(2 == ERR_T){
                                                                                                                                                $$ = ERR_T;
                                                                                                                                            } else {
                                                                                                                                                $$=BOOL_T;
                                                                                                                                               add_intermediate_list(&liste_inter,NOT_COM,COM,NULL,function_ptr);
                                                                                                                                            }
                                                                                                                                        }
    | '(' EXPR ')'                                                                                                                      {$$=$2;}
    | NUM                                                                                                                                 {
                                                                                                                                            $$=NUM_T;
                                                                                                                                            sprintf(env,"%d",$1);
                                                                                                                                            add_intermediate_list(&liste_inter,NUM_COM,ARG,env,function_ptr);
                                                                                                                                            };
    | FALSE                                                                                                                               {printf("\tconst ax,0\n");
                                                                                                                                            printf("\tpush ax\n");
                                                                                                                                            $$=BOOL_T;
                                                                                                                                           }

    | TRUE                                                                                                                                  {printf("\tconst ax,1\n");
                                                                                                                                              printf("\tpush ax\n");
                                                                                                                                              $$=BOOL_T;
                                                                                                                                             }
    | ID                                                                                                                                    {
                                                                                                                                              $$=NUM_T;
                                                                                                                                              if(search_symbol_table($1,function_ptr->table) == NULL){
                                                                                                                                                  fprintf(stderr,"variable %s pas declarée\n",$1);
                                                                                                                                                  exit(EXIT_FAILURE);
                                                                                                                                              }

                                                                                                                                              add_intermediate_list(&liste_inter,ID_COM,ARG,$1,function_ptr);
                                                                                                                                              };

INSTR: SET '{' ID '}' '{' EXPR '}'                                                                                             {
                                                                                                                                  if(search_symbol_table($3,function_ptr->table) ==  NULL){
                                                                                                                                      add_function_id(LOCALE_VARIABLE,$3,function_ptr->func_name
                                                                                                                                      ,function_ptr);
                                                                                                                                      nb_of_local_var++;
                                                                                                                                      function_ptr->nb_local_var++;
                                                                                                                                  }
                                                                                                                                    add_intermediate_list(&liste_inter,SET_COM,ARG,$3,function_ptr);
                                                                                                                                }

    |INCR '{' ID '}'                                                                                                           {
                                                                                                                                    if(search_symbol_table($3,function_ptr->table) ==  NULL){
                                                                                                                                        fprintf(stderr,"variable %s non declarée\n",$3);
                                                                                                                                        exit(EXIT_FAILURE);
                                                                                                                                    }
                                                                                                                                    add_intermediate_list(&liste_inter,INCR_COM,ARG,$3,function_ptr);
                                                                                                                                }
    |DECR '{' ID '}'                                                                                                             {
                                                                                                                                    if(search_symbol_table($3,function_ptr->table) ==  NULL){
                                                                                                                                        fprintf(stderr,"variable %s non declarée\n",$3);
                                                                                                                                        exit(EXIT_FAILURE);
                                                                                                                                    }

                                                                                                                                    add_intermediate_list(&liste_inter,DECR_COM,ARG,$3,function_ptr);
                                                                                                                                }
    |IF '{' EXPR '}' FI                                                                                                         {}
    |DOFORI '{' ID '}' '{' EXPR '}' BLOC OD                                                                                     {};




APPEL : APPEL_FONCTION ARGUMENTS                                                                                                {};

APPEL_FONCTION : CALL '{' ID '}'                                                                                                {
                                                                                                                                              if(search_function($3,f) == NULL){
                                                                                                                                                  fprintf(stderr,"Fonction %s non declarée\n",$3);
                                                                                                                                                  exit(EXIT_FAILURE);
                                                                                                                                              }
                                                                                                                                              nb_of_global_var=0;
                                                                                                                                              function_ptr=search_function($3,f);

                                                                                                                                              add_intermediate_list(&liste_inter,CALL_COM,COM,NULL,function_ptr);
                                                                                                                                };


ARGUMENTS : '{' ar '}'                                                                                                          {
                                                                                                                                              if(nb_of_global_var != function_ptr->nb_global_var){
                                                                                                                                                  fprintf(stderr,"Nombre de parametres incorrect\n");
                                                                                                                                                  exit(EXIT_FAILURE);}
                                                                                                                                              add_intermediate_list(&liste_inter,CALLED_COM,COM,NULL,function_ptr);
                                                                                                                                  };


ar:
    EXPR                                                                                                                                        {
                                                                                                                                                nb_of_global_var++;
                                                                                                                                                }
    | ar ',' EXPR                                                                                                                     {
                                                                                                                                                  nb_of_global_var++;
                                                                                                                                              };

%%


int main(void){
    f=NULL;
    liste_inter=NULL;
    yyparse();
    create_intermediate_list(liste_inter);
    clear_list(liste_inter);
    return 0;
}

