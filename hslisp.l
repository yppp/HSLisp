%{
#include "hslisp.h"
#include "y.tab.h"
%}
%start COMMENT
%%

<INITIAL>[ |\t|\n]+      ;
<INITIAL>"\("|"\)"|"\."|"\["|"\]"  return yytext[0];

<INITIAL>[A-za-z_][A-Za-z_0-9]*  { 
  yylval.hvalue = HLI_create_atom(SYMBOL, yytext);
  return ATOM; }

<INITIAL>[1-9][0-9]* {
  int i;
  sscanf(yytext, "%d", i);
  yylval.value = HLI_create_atom(FIXNUM, i);
  return ATOM;
}

<INITIAL>"0" {
  yylval.value = HLI_create_atom(FIXNUM, 0);
  return ATOM;
}

<INITIAL>[0-9]+\.[0-9]+ {
  double i;
  sscanf(yytext, "%lf", i);
  yylval.hvalie = HLI_create_atom(REAL, i);
  return ATOM;
}

<INITIAL>";" BEGIN COMMENT;
<COMMENT>. ;
<COMMENT>"\n" BIGIN INITIAL;
%%
