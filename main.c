#include <stdio.h>
#include "HLI.h"
#include "MEM.h"

int main(int argc, char **argv)
{
  HLI_Interpreter *interpreter;

  if (argc == 1)
    {
      fp = stdin;
    }
  else if (argc == 2) 
    {
      fp = fopen(argv[1], "r");

      if (fp == NULL)
	{
	  fprintf(stderr, "%s not found.\n", argv[1]);
	  exit(1);
	}
    }
  else
    {
      fprintf(stderr, "usage:%s filename", argv[0]);
      exit(1);
    }

  interpreter = HLI_create_interpreter();
  HLI_interpret(interpreter);
  HLI_dispose_interpreter(interpreter);

  return 0;
}
