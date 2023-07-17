%option noyywrap

%{
#include "gramatica_latino.tab.h"
extern YYSTYPE yylval;
int num_linea = 1; 

%}

%%

"+"	                                            return SUMA;
"-"	                                            return RESTA;
"*"	                                            return MULTIPLICACION;
"/"	                                            return DIVISION;

"="	                                            return IGUAL;

">"	                                            return MAYORQUE;
"<"	                                            return MENORQUE;
">="                                            return MAYORIGUALQUE;
"<="                                            return MENORIGUALQUE;
"=="                                            return IGUALQUE;

"&&"                                            return YLOGICO;
"||"                                            return OLOGICO;
"!"                                             return NOLOGICO;

"("	                                            return APERTURAPARENTESIS;
")"	                                            return CIERREPARENTESIS;

"si"                                            return SI;
"osi"                                           return OSI;
"sino"                                          return SINO;

"mientras"                                      return MIENTRAS;
"fin"                                           return FIN;

\/\/.*                                          return COMENTARIO;
\#.*$                                           return COMENTARIO;
\/\*([^\*\/]*)\*\/                              return COMENTARIO;

imprimir|escribir|poner                         return IMPRIMIR;

[0-9]+                                          {yylval.enteroVal = atoi(yytext); return NUMERICO;}
[0-9]+.[0-9]+                                   {yylval.realVal   = atof(yytext); return NUMERICODECIMAL;}
\"([a-zA-Z0-9\s]*)\" 		                    {yylval.stringVal = strdup(yytext); printf(yytext);return CADENA;}
_?[a-zA-Z0-9]+		                            {yylval.stringVal = strdup(yytext); printf(yytext);return IDENTIFICADOR;}
\n		                                        {num_linea++;} //Incrementa el numero de linea para saber en que num_linea se encuentra

%%
