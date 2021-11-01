//defining colors for aesthetics of comet
#define GREEN "\x1b[1;32m"
#define BLUE "\x1b[1;34m"
#define WHITE "\x1b[1;37m"
#define RED "\x1B[1;31m"
#define YELLOW "\x1B[1;33m"
#define RESET "\x1B[0m"
#define MAG "\x1B[1;35m"
// #define GU "\x1b[1;4;32m"
// #define RB "\x1B[1;31;47m"

int args_cnt; //global variable
char **args; //global variable

//header files of custom functions
#include "dir_file.h"
#include "file_size.h"
#include "copy_file.h"

//including all header files
#include "cat.h"
#include "cd.h"
#include "chmod.h"
#include "clear.h"
#include "cp.h"
#include "exit.h"
#include "grep.h"
#include "help.h"
#include "ls.h"
#include "mkdir.h"
#include "mv.h"
#include "pwd.h"
#include "rm.h"
