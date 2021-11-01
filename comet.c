#include <stdio.h>  //INPUT-OUTPUT
#include <ctype.h>  //Testing characters
#include <stdlib.h>
#include <fcntl.h> //file operations(open, create, etc..)
#include <string.h>  //String Functions
#include <unistd.h> //Null Pointer, POSIX
#include <sys/wait.h> //WAIT
#include <dirent.h>  //DIRECTORY
#include <sys/types.h>
#include <sys/stat.h>  //File attributes.
#include <errno.h>   //Error handling
#include <libgen.h>  //For Basename
#include "headers.h" //header file contaning other headers

char *comet_cmd[] = {  //array pointer contaning names of commands
  "cd", //1
  "help", //2
  "exit", //3
	"pwd", //4
	"mkdir", //5
  "ls", //6
  "cp", //7
  "cat", //8
  "clear", //9
  "mv", //10
  "rm",  //11
  "grep",  //12
  "chmod"  //13
};

int dec_func(int i, char **args){  //function for deciding and calling the function as per command
	int f; //return flag
	switch(i){
		case 1: f = comet_cd(args);
						break;
		case 2: f = comet_help(args);
						break;
		case 3: f = comet_exit(args); //only case when f will be  zero
						break;
		case 4: f = comet_pwd(args);
						break;
		case 5: f = comet_mkdir(args);
						break;
    case 6: f = comet_ls(args);
            break;
    case 7: f = comet_cp(args);
            break;
    case 8: f = comet_cat(args);
            break;
    case 9: f = comet_clear(args);
            break;
    case 10: f = comet_mv(args);
            break;
    case 11: f = comet_rm(args);
            break;
    case 12: f = comet_grep(args);
            break;
    case 13: f = comet_chmod(args);
              break;
		default:// It will never reach here!!!!!!
						printf("\n'%s' is not recognized as an internal or external command, operable program or batch file.\n\n",args[0]);
						f = 1;
						break;
	}
	return f;
}

int comet_inbuilt(char **args){ //function when cmd is to called from inbuilt binary executables
  pid_t pid; //process id
  int status;
  pid = fork();//creating child process(forking)
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      printf("comet: '%s', command not found\n", args[0]);
    }
    exit(EXIT_FAILURE);
  }
  else if (pid < 0) {
    // Error forking
    printf("comet: '%s', command not found\n", args[0]);
  }
  else {
    // Parent process
    waitpid(pid, &status,WUNTRACED); //check the status->report->return status
  }

  return 1;
}

int comet_background(char **args){ //for running process in background
  pid_t pid; //process id
  int status;
  pid = fork(); //creating a child process
  if (pid == 0) {
    // Child process
    setpgid(0,0);
    int i=0;
    int len = sizeof(comet_cmd)/sizeof(char *);
    for (i = 0; i < len; i++) {
      if(!strcmp(args[0], comet_cmd[i])){ //input command is matches with on of the implement command
  			return dec_func(i+1,args); //calling function to decide which command is called.
      }
    }
    return comet_inbuilt(args);//Not matches with implemented commands-> Inbuilt Command
  }
  else if (pid < 0) {
    // Error forking
    printf("comet: '%s', command not found\n", args[0]);
  }
  else {
    // Parent process
    printf("%d\n",pid);
    waitpid(pid, &status,WNOHANG); //return immediately
  }

  return 1;
}

int comet_exec(char **args){ //executing the command
  if(args[0]==NULL){
    printf("\nTry 'help' command to know about other commands!\n");
    return 1;
  }
  if(strcmp(args[args_cnt-1],"&")==0){ //command to be run in background
    args[args_cnt-1] = NULL; //removing '&' from args
    args_cnt--; 
    return comet_background(args); //calling function for running command in background
  }
  //Not in background
  int i=0;
  int len = sizeof(comet_cmd)/sizeof(char *); //number of implemented commands
  for (i = 0; i < len; i++) {
    if(!strcmp(args[0], comet_cmd[i])){ //input command is matches with on of the implement command
			return dec_func(i+1,args); //calling function to decide which command is called.
    }
  }
  return comet_inbuilt(args); //Not matches with implemented commands-> Inbuilt Command
}

#define comet_arg_bufsize 128 //buffer size of each argument in input command
char **comet_splitcmd(char *cmd){ //splitting the command by <whitespace>

  int arg_size = comet_arg_bufsize;//initializing argument size
  char **args = malloc(sizeof(char)*arg_size); //pointer for argument with initial memory size->cmd_size
  char *arg; //local string pointer for each argument
  int index=0;

  arg = strtok(cmd," ");
  while(arg !=NULL){
    args[index] = arg;
    index++;
    // If we have exceeded the buffer size of args, reallocate.
    if(index>=arg_size){
      arg_size += comet_arg_bufsize;
      args = realloc(args,sizeof(char) * arg_size);
    }
    arg = strtok(NULL," ");
  }
  args_cnt = index;
  args[index]=NULL;
  return args; //returning the pointer for array storing arguments
}

#define comet_cmd_bufsize 1024 //buffer size of input command
char *comet_readcmd(){//reading the command

  int cmd_size = comet_cmd_bufsize; //initializing command size
  char *cmd = malloc(sizeof(char) * cmd_size); //pointer for input command with initial memory size->cmd_size
  int index = 0; //position counter
  int c;

  while (1) {
    // Read a character
    c = getchar();
    if (c == EOF) { //End Of File
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      cmd[index] = '\0';
      return cmd; //returning the pointer for string storing command
    } else {
      cmd[index] = c;
    }
    index++;

    // If we have exceeded the buffer size of cmd, reallocate.
    if (index >= cmd_size) {
      cmd_size += comet_cmd_bufsize;
      cmd = realloc(cmd,sizeof(char) * cmd_size);
    }
  }
  return cmd;  //returning the pointer for string storing command
}

void comet_loop(void){ //loop which will be active till exit is called
  char *cmd; //pointer for input
  int flag = 1;

  while(flag){
    char pth[1024]; //storing path of current working directory
    getcwd(pth, sizeof(pth));
    printf(BLUE"priyam@Comet" WHITE);
    printf(":");
    printf(YELLOW "~%s" WHITE, pth);
    printf("$ ");
    cmd = comet_readcmd(); //calling function for reading the command
    args = comet_splitcmd(cmd); //calling function for splitting the command
    flag = comet_exec(args); //calling function for executing the command

    free(cmd);
    free(args);
  }

}

int main(){
  //call for main loop
  comet_loop();
  return EXIT_SUCCESS;
}
