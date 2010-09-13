#include <stdio.h>
#include "hslisp.h"

/*評価すべき本体はe 第1引数を手続としてapplyに渡し、残りの引数をその手続きの引数としてapplyに渡す、シンボルや数値が入力されたらオブジェクトを返す*/
struct HVALUE eval(Interpreter *inter, HVALUE *e, Cell *env)
{
  struct HVALUE *v;
  if (IS_SYMBOL(e))
    {
      v = assoc(e, env);
      if (v == NULL)
	{
	  fprintf(stderr, "undefined symbol '%s'",SYMBOL_NAME(e));
	  exit(1);
	}
      return v;
    }
  else if (IS_REAL(e) || IS_FIXNUM(e))
    {
      return e;
    }
  else
    {
      return apply(inter, CAR(e), CDR(e), env);      
    }
}

/*手続きをevalに渡してオブジェクト化する、手続きオブジェクトを適用する、C等で書かれたネイティブな手続きか、インタプリタで書かれた手続きか判断して関数の適用の処理をする*/
struct HVALUE apply(Interpreter *inter, HVALUE *func, HVALUE *args, Cell env)
{
  struct HVALUE *proc = eval(inter, func, env);

  switch (proc->type)
    {
    case HSLISP_PROC:
      return apply_hslisp_proc(inter, proc->u.hli_f, args, env);
      break;
    case NATIVE_PROC:
      return apply_native_proc (inter, proc->u.native_f.proc, args, env);
      break;
    default:
      fprintf(stderr, "BUG: unknown function type '%d'", f.type);
      exit(1);
      break;
    }
}

struct HVALUE apply_hslisp_proc(Interpreter *inter, HVALUE *f, HVALUE *args, Cell *env)
{
  struct HVALUE *params;
  struct HVALUE *block;

  params = f.u.HLI_f->paramerter;
  block = f.u.HLI_f->block;
  
  list = eval_list(inter, args, env);
  return eval(inter, block, push_flont(env, pairlis(params, list)));
}

void apply_native_proc(Interpreter *inter, HLI_NativeFunctionProc *f, HVALUE *args, Cell *env)
{
  
}

struct HVALUE eval_list(Interpreter *inter, HVALUE args, Cell env)
{
  HVALUE *arg = args;
  HVALUE *cellchain = NIL;
  int i = 0;
  int chainlen = 0;

  if(IS_ATOM(arg))
    {
      eval(inter, arg, env);
      pop(inter);
      cellchain = GET_VALREG(inter);
    }
  else
    {
      for(; CDR(arg) != NIL; arg = CDR(arg))
	{
	  eval(inter, CAR(arg), env);
	  i++;
	}
    
      chainlen = i;
      for(i = 0; i < chainlen; i++)
	{
	  pop(inter);
	  cellchain = push_flont(cellchain, GET_VALREG(inter));
	}
    }

  return cellchain;
}

struct HVALUE assoc (HVALUE *e, Cell *env)
{
  struct HVALUE *elem;
  for(; CDR(env) != NIL; elem = CDR(env))
    {
      if (e == elem)
	return elem;
    }
}
