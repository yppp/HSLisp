#ifndef _HSLISP_H_
#define _HSLISP_H_

typedef unsigned long VALUE;

struct HVALUE;
struct Real;
struct Procedure;
struct Cell;
struct Strage;
struct HBasic;

typedef HVALUE HLI_NativeFunctionProc();
struct HVALUE 
{
  union
  {
    struct Free
    {
      unsigned long flags;
      struct HVALUE *next;
    }free;
    struct HBasic basic;
    struct Integer integer;
    struct Real real;
    struct Procedure procedure;
    struct Cell cell;
  }u;
};

struct HBasic
{
  unsigned long flags;/*下位6bit組み込みオブジェクト(構造体)判断フラグ 7bit目GC用フラグ*/
  VALUE klass;
};

struct Integer
{
  struct HBasic basic;
  int val;
};
struct Real
{
  struct HBasic basic;
  double val;
};

struct Procedure
{
  struct HBasic basic;
  enum type
    {
      HSLISP_FUNCTION = 0,
      NATIVE_FUNCTION,
      NATIVE_FUNCTION_PLUS1
    };
  union
  {
    struct HLI_f
    {
      struct HVALUE *parameter;
      struct HVALUE *block;
    } hli_f;
    struct Native_f
    {
      struct HLI_NativeFunctionProc proc;
    } native_f;
  }u;
};

struct Cell
{
  struct HBasic basic;
  struct HVALUE car;
  struct HVALUE cdr;
};

struct Interpreter
{
  struct Strage interpreter_strage;
  struct Strage execute_strage;
};

struct Strage
{
  struct HVALUE **heaps;
  struct HVALUE *freelist;
  int heap_used;
  int heap_length;
};
#endif /*_HSLISP_H_*/
