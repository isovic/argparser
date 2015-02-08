/*
 * cmdparser.cc
 *
 *  Created on: Sep 21, 2014
 *      Author: ivan
 */

#include "cmdparser.h"

ArgumentParser::ArgumentParser() {
}

ArgumentParser::ArgumentParser(int argc, char* argv[]) {
  ProcessArguments(argc, argv);
}

ArgumentParser::~ArgumentParser() {
}

void ArgumentParser::AddArgument(std::string arg_short, std::string arg_long,
                                 std::string default_value,
                                 std::string description_short,
                                 int32_t positional,
                                 std::string argument_group,
                                 std::string description_long) {

  if (arg_short == "" && arg_long == "") {
    fprintf(stderr, "ERROR: Argument's name not initialized!\n");
    fflush(stderr);
    return;
  }

  Argument arg;
  arg.arg_short = arg_short;
  arg.arg_long = arg_long;
  arg.value = default_value;
  arg.default_value = default_value;
  arg.description_short = description_short;
  arg.description_long = description_long;
  arg.positional = positional;
  arg.arg_group = argument_group;
  arg.is_set = false;

  arguments.push_back(arg);
  valid_args_short[arg.arg_short] = (arguments.size() - 1);
  valid_args_long[arg.arg_long] = (arguments.size() - 1);
  valid_args_positional[arg.positional] = (arguments.size() - 1);

  if (valid_args_group.find(arg.arg_group) == valid_args_group.end()) {
    std::vector<int32_t> indices;
    indices.push_back((arguments.size() - 1));
    valid_args_group[arg.arg_group] = indices;
  } else {
    valid_args_group[arg.arg_group].push_back((arguments.size() - 1));
  }
}

void ArgumentParser::ProcessArguments(int argc, char* argv[]) {
  for (int32_t i=1; i<argc; i++) {
    std::string arg = argv[i];
    std::string arg_next = "";

    // Check if for some reason the string is empty.
    if (arg.size() == 0)
      continue;

    // The argument should start with a dash. Otherwise, it can only be positional, or an error.
    if (arg[0] == '-') {
      // If only a dash is given, then something is wrong (or perhaps that was the intention,
      // for instance, to enable pipe processing).
      if (arg.size() == 1) {
        fprintf (stderr, "WARNING: Unspecified parameter '%s'.\n", arg.c_str());

      } else {
        // If the second character is not '-' then the argument is specified by its short name.
        if (arg[1] != '-') {      // Handle the short argument assignment.
          std::string arg_name = arg.substr(1);

          // If the argument cannot be found, report it.
          if (valid_args_short.find(arg_name) == valid_args_short.end()) {
            fprintf (stderr, "WARNING: Unknown parameter '%s'.\n", arg.c_str());

          } else {
            int32_t argument_index = valid_args_short[arg_name];
            arguments[argument_index].count += 1;
            arguments[argument_index].is_set = true;

            if (arguments[argument_index].default_value != "") {      // This argument expects a value.
              if ((i + 1) < argc) {
                arguments[argument_index].value = argv[i + 1];
                i += 1;
              } else {
                fprintf (stderr, "ERROR: Argument '%s' expects a value. Exiting.\n", arg.c_str());
                exit(1);
              }
            }
          }

        } else if (arg[1] == '-') {                  // Handle the long argument assignment.
          if (arg.size() == 2) {
            fprintf (stderr, "WARNING: Unspecified parameter '%s'.\n", arg.c_str());
          } else {
            std::string arg_name = arg.substr(2);

            // If the argument cannot be found, report it.
            if (valid_args_long.find(arg_name) == valid_args_long.end()) {
              fprintf (stderr, "WARNING: Unknown parameter '%s'.\n", arg.c_str());

            } else {
              int32_t argument_index = valid_args_long[arg_name];
              arguments[argument_index].count += 1;
              arguments[argument_index].is_set = true;

              if (arguments[argument_index].default_value != "") {      // This argument expects a value.
                if ((i + 1) < argc) {
                  arguments[argument_index].value = argv[i + 1];
                  i += 1;
                } else {
                  fprintf (stderr, "ERROR: Argument '%s' expects a value. Exiting.\n", arg.c_str());
                  exit(1);
                }
              }
            }
          }
        }
      }
    } else {      // In this case, the argument can either be positional, or misspelled.
      int32_t position = i - argc;

      if (valid_args_positional.find(position) != valid_args_positional.end()) {
        arguments[valid_args_positional[position]].value = arg;
      } else {
        fprintf (stderr, "ERROR: Unknown parameter value: %s. Exiting.\n", arg.c_str());
        exit(1);
      }
    }
  }
}

void ArgumentParser::VerboseArgumentsByGroup(FILE* fp) {
  std::map<std::string, std::vector<int32_t>>::iterator it;
  const int32_t description_starting_char = 25;

  for (it = valid_args_group.begin(); it != valid_args_group.end(); it++) {
    fprintf(fp, "%s:\n", it->first.c_str());
    for (uint32_t i = 0; i < it->second.size(); i++) {
      std::stringstream ss;
      int32_t num_chars = 0;

      ss << "  ";
      num_chars += 2;

      if (arguments[it->second.at(i)].positional >= 0) {
        if (arguments[it->second.at(i)].arg_short != "") {
          ss << "-" << arguments[it->second.at(i)].arg_short;
          num_chars += 2;
        } else {
          ss << "  ";
          num_chars += 2;
        }

        if (arguments[it->second.at(i)].arg_short != "" && arguments[it->second.at(i)].arg_long != "") {
          ss << ", ";
          num_chars += 2;
        } else {
          ss << "  ";
          num_chars += 2;
        }

        if (arguments[it->second.at(i)].arg_long != "") {
          ss << "--" << arguments[it->second.at(i)].arg_long;
          num_chars += 2 + arguments[it->second.at(i)].arg_long.size();
        }

      } else {
        std::string arg_name = arguments[it->second.at(i)].arg_long;
        if (arg_name == "")
          arg_name = arguments[it->second.at(i)].arg_short;

        ss << arg_name;
        num_chars += 2 + arg_name.size();
      }



      if (arguments[it->second.at(i)].description_short != "") {
        int32_t num_empty_chars =  (((description_starting_char - num_chars) > 0)?(description_starting_char - num_chars):1);
        std::string empty_chars(num_empty_chars, ' ');
        ss << empty_chars;
        ss << arguments[it->second.at(i)].description_short;
      }
      if (arguments[it->second.at(i)].default_value != "") {
        ss << " [" << arguments[it->second.at(i)].default_value << "]";
      }


      if (arguments[it->second.at(i)].arg_short != "" || arguments[it->second.at(i)].arg_long != "") {
        fprintf (fp, "%s\n", ss.str().c_str());
      }
    }

    fprintf (fp, "\n");
  }

  fflush(fp);
}

void ArgumentParser::VerboseArguments(FILE *fp) {
  for (int32_t i=0; i<arguments.size(); i++) {
    fprintf (fp, "'-%s'\t'--%s'\tvalue = '%s'\tdefault = '%s'\tpositional = %d\tcount = %d\n", arguments[i].arg_short.c_str(), arguments[i].arg_long.c_str(), arguments[i].value.c_str(), arguments[i].default_value.c_str(), arguments[i].positional, arguments[i].count);

//    std::string  = "";
//    std::string  = "";
//    std::string  = "";
//    std::string  = "";
//    std::string description_short = "";
//    std::string description_long = "";
//    std::string arg_group = "";
//    int32_t  = 0;
//    int32_t count = 0;
//    bool is_set = false;
  }
}
