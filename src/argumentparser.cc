//============================================================================
// Name        : cmdparser.cpp
// Author      : Ivan Sovic
// Version     :
// Copyright   : Copyright Ivan Sovic, 2014. All rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include "cmdparser.h"

int main(int argv, char* argc[]) {

  ArgumentParser argparser;

  argparser.AddArgument("o", "ovo", "", "Ovo je samo jedna proba!", 0, "Glavna grupa", "Ovo je samo jos jedna proba!");
  argparser.AddArgument("a", "", "", "Proba za kratki argument.", 0, "Glavna grupa", "Ovo je samo jos jedna proba!");
  argparser.AddArgument("", "threads", "-1", "Proba za dugi argument.", 0, "Glavna grupa", "Ovo je samo jos jedna proba!");
//  argparser.AddArgument("", "", "", "Proba bez argumenata.", 0, "Ovo je samo jos jedna proba!");
  argparser.AddArgument("s", "start", "", "Proba za drugu grupu.", 0, "Control", "Ovo je samo jos jedna proba!");
  argparser.AddArgument("", "reads", "reads.fasta", "Path to the file with read sequences.", -1, "Input/Output");
  argparser.VerboseArgumentsByGroup(stdout);

  argparser.ProcessArguments(argv, argc);

  printf ("\n");

  argparser.VerboseArguments(stdout);

	return 0;
}
