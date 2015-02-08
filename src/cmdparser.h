/*
 * cmdparser.h
 *
 *  Created on: Sep 21, 2014
 *      Author: ivan
 */

#ifndef CMDPARSER_H_
#define CMDPARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>

struct Argument {
  std::string arg_short = "";
  std::string arg_long = "";
  std::string value = "";
  std::string default_value = "";
  std::string description_short = "";
  std::string description_long = "";
  std::string arg_group = "";
  int32_t positional = 0;
  int32_t count = 0;
  bool is_set = false;
};

class ArgumentParser {
 public:
  ArgumentParser();
  ArgumentParser(int argc, char* argv[]);
  ~ArgumentParser();

  void AddArgument(std::string arg_short, std::string arg_long,
                   std::string default_value, std::string description_short, int32_t positional=0, std::string argument_group="unknown",
                   std::string description_long=""
                   );
  void ProcessArguments(int argc, char* argv[]);
  void VerboseArgumentsByGroup(FILE *fp);
  void VerboseArguments(FILE *fp);

  std::map<std::string, int32_t> valid_args_short;
  std::map<std::string, int32_t> valid_args_long;
  std::map<std::string, std::vector<int32_t>> valid_args_group;
  std::map<int32_t, int32_t> valid_args_positional;
  std::vector<Argument> arguments;
};

//void ProcessArguments(int argc, char* argv[]);

#endif /* CMDPARSER_H_ */
