//============================================================================
// Name        : argumentparser.cc
// Author      : Ivan Sovic
// Version     : 1.0
// Created on  : Sep 21, 2014
// Copyright   : License: MIT
// Description : Test for an argument parsing library.
//============================================================================

#include <stdio.h>
#include "cmdparser.h"

int main(int argv, char* argc[]) {

  ArgumentParser argparser;

  argparser.AddArgument("o", "open", VALUE_TYPE_STRING, "", "Opens the specified file.", 0, "Basic options", "Long description of the parameter. Currently not functional. Can be omitted.");
  argparser.AddArgument("a", "", VALUE_TYPE_NONE, "", "Test for only a short argument.", 0, "Basic options", "Long description of the parameter. Currently not functional.");
  argparser.AddArgument("", "threads", VALUE_TYPE_INT, "-1", "Test for only a long argument.", 0, "Basic options", "Long description of the parameter. Currently not functional.");
//  argparser.AddArgument("", "", "", "Test for specifying no arguments.", 0, "Long description of the parameter. Currently not functional.");
  argparser.AddArgument("s", "start", VALUE_TYPE_NONE, "", "Starts something important.", 0, "Control options", "Long description of the parameter. Currently not functional.");
  argparser.AddArgument("", "reads1", VALUE_TYPE_STRING, "reads.fasta", "Path to the file with read sequences.", -2, "Input/Output");
  argparser.AddArgument("", "reads2", VALUE_TYPE_STRING, "reads2.fasta", "Path to the file with read sequences.", -1, "Input/Output");

  argparser.ProcessArguments(argv, argc);

  printf ("%s", argparser.VerboseArgumentsByGroup().c_str());

  printf ("\n");

  printf ("Results of parsing the command line:\n");
  argparser.VerboseArguments(stdout);

  printf ("\n");
  printf ("Retrieving the value of parameter 'threads':\n");
  printf ("threads = %s\n", argparser.GetArgument("threads")->value.c_str());
  printf ("\n");

  // TODO: Need better validation of positional arguments.

	return 0;
}
