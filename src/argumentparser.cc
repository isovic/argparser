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

  argparser.AddArgument("o", "open", VALUE_TYPE_STRING, "", "Long description of the parameter. If too long, it will automatically be wrapped to 120 characters line width.", 0, "Basic options");
  argparser.AddArgument("a", "", VALUE_TYPE_NONE, "", "Test for only a short argument.", 0, "Basic options");
  argparser.AddArgument("", "threads", VALUE_TYPE_INT, "-1", "Test for only a long argument.", 0, "Basic options");
  argparser.AddArgument("", "", VALUE_TYPE_NONE, "", "Test for specifying no arguments.", 0, "Basic options");
  argparser.AddArgument("s", "start", VALUE_TYPE_NONE, "", "Starts something important.", 0, "Control options");
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

	return 0;
}
