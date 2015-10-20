# argparser - A C++ library for parsing command line arguments.

An easy to use argument parsing library, with all the features you will ever probably need.  

Features:  
- short and long argument names  
- automatic assignment of argument values to given variables  
- non-parameter arguments (switch), and arguments requiring parameter input  
- (also, counting the occurence of a specific parameter, good for verbose level)  
- positional arguments (at the beginning or the end of the command line)  
- argument groups  
- argument descriptions  
- automatic usage generation, line wrapped to 120 characters  

Program usage is automatically printed out in case no arguments are specified, or if an argument is misused.  

## Installation
Simply copy the `argparser.cc` and `argparser.h` files into your project and `#include <argparser.h>`.  
To run an example from this repo, type:  
```
make  
./argumentparser --threads 8  
```

## Usage  
An example usage code snippet.  
```
ArgumentParser argparser;  
int32_t num_threads = 0;  
argparser.AddArgument(&num_threads, VALUE_TYPE_INT32, "t", "threads", "-1", "Number of threads to use.", 0, "Basic options");  
printf ("num_threads = %d\n", num_threads);  
```

A more comprehensive example can be found in `example.cc`.  
Additionally, the code contains verbose descriptions to detail the usage.  