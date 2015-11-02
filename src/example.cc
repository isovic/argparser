/// This will only get compiled if -DTEST_SEQ_LIB_ is passed to the compiler.
/// Otherwise, the test file will be skipped, not causing compile time errors for the program including this library.
#ifdef TEST_EXAMPLE_

//============================================================================
// Name        : example.cc
// Author      : Ivan Sovic
// Version     : 1.0
// Created on  : Sep 21, 2014
// Copyright   : License: MIT
// Description : Test for the argument parsing library.
//============================================================================

#include <stdio.h>
#include "argparser.h"

int main(int argv, char* argc[]) {

  ArgumentParser argparser;

  std::string infile;
  int64_t num_threads = 0;
  std::string reads_path1;
  std::string reads_path2;
  std::string tool_name;

  argparser.AddArgument(&infile, VALUE_TYPE_STRING, "o", "open", "", "Long description of the parameter. If too long, it will automatically be wrapped to 120 characters line width.", 0, "Basic options");
  argparser.AddArgument(NULL, VALUE_TYPE_NONE, "a", "", "", "Test for only a short argument. This argument requires no value (a switch argument).", 0, "Basic options");
  argparser.AddArgument(&num_threads, VALUE_TYPE_INT64, "", "threads", "-1", "Test for only a long argument.", 0, "Basic options");
  /// The following line will cause a runtime error.
  // argparser.AddArgument(NULL, VALUE_TYPE_NONE, "", "", "", "Test for specifying no arguments.", 0, "Basic options");
  argparser.AddArgument(NULL, VALUE_TYPE_NONE, "s", "start", "", "Starts something important.", 0, "Control options");
  argparser.AddArgument(&reads_path1, VALUE_TYPE_STRING, "", "reads1", "reads.fasta", "Path to the file with read sequences.", -2, "Input/Output");
  argparser.AddArgument(&reads_path2, VALUE_TYPE_STRING, "", "reads2", "reads2.fasta", "Path to the file with read sequences.", -1, "Input/Output");
  argparser.AddArgument(&tool_name, VALUE_TYPE_STRING, "", "tool", "index", "Specifies a tool to use. Can be 'index' or 'align'.", 1, "Tools");

  argparser.ProcessArguments(argv, argc);
  // printf ("%s\n", argparser.VerboseUsage().c_str());

  printf ("Checking the values of parameters auto assigned during processing:\n");
  printf ("num_threads = %ld\n", num_threads);
  printf ("reads_path1 = '%s'\n", reads_path1.c_str());
  printf ("reads_path2 = '%s'\n", reads_path2.c_str());
  printf ("tool = '%s'\n", tool_name.c_str());
  printf ("\n");

  printf ("Retrieving the value of parameter 'threads':\n");
  printf ("threads = %s\n", argparser.GetArgument("threads")->value.c_str());
  printf ("\n");

  printf ("Retrieving the value of parameter 'threads' using GetValue function:\n");
  int64_t num_threads1 = 0;
  argparser.GetValue("threads", &num_threads1);
  printf ("num_threads = %ld\n", num_threads1);
  printf ("\n");

  printf ("The entire list of registered arguments and their values:\n");
  printf ("%s\n", argparser.VerboseArguments().c_str());
  printf ("\n");

	return 0;
}

#endif
