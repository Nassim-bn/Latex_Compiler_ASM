%{
#include "func.h"
#include "latex.tab.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
%}

%option noyywrap

%%
"{"|"}"|"("|")"|","                                         {return yytext[0];}
"\\begin{algo}"                                             {return BEGIN_ALGO;}
"\\end{algo}"                                               {return END;}
"\\SET"                                                     {return SET;}
"\\IF"                                                      {return IF;}
"\\FI"                                                      {return FI;}
"\\ELSE"                                                    {return ELSE;}
"\\DOFORI"                                                  {return DOFORI;}
"\\OD"                                                      {return OD;}
"\\INCR"                                                    {return INCR;}
"\\DECR"                                                    {return DECR;}
"\\CALL"                                                    {return CALL;}
"\\RETURN"                                                  {return RETURN;}

"+"|"-"|"*"|"/"                                             {return yytext[0];}
"!="                                                        {return DIFF;}
"&&"                                                        {return AND;}
"=="                                                        {return EQ;}
"||"                                                        {return OR;}
"!"                                                         {return NOT;}

"true"                                                      {return TRUE;}
"false"                                                     {return FALSE;}

[0-9]+                                                      {yylval.entier=atoi(yytext);return NUM;}
[a-zA-Z]+                                                   {yylval.id=strdup(yytext);return ID;}
[[:blank:]]+                                                {;}

.                                                           {printf("Erreur,%s non reconnu\n",yytext);}
\n                                                          {;}
%%
