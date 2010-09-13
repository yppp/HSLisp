%{
#include "hslisp.h"
#include "HSLP.h"
%}

%union{
  VALUE value;
}
%token ATOM
%type <value> ATOM symbolexp slist dotpair
%%
toplevel
:
| toplevel symbolexp  {
  Interpreter *inter = get_current_interpreter();
  inter->sexp_list = chain(inter->symbolexp_list, $2);
}
;

slist
: symbolexp
| slist symbolexp { $$ = HLI_chain($1, $2);}
;

dotpair
: '(' slist '.' symbolexp ')' { $$ = HLI_create_cons($2, $4);}
| '[' slist '.' symbolexp ']' { $$ = HLI_create_cons($2, $4);}
;

symbolexp
: ATOM
| dotpair
| '(' slist ')' { $$ = HLI_create_cons((VALUE)$2, create_atom(NIL,NULL));}
| '[' slist ']' { $$ = HLI_create_cons((VALUE)$2, create_atom(NIL,NULL));}
| '(' ')' { $$ = create_atom(NIL, NULL);}
| '[' ']' { $$ = create_atom(NIL, NULL);}
;
%%
