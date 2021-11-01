int comet_ls(char **args){

  if(args_cnt==1){ //handling the case when user gives "ls" as input.
    char var[10] = ".";
    args_cnt++;
    args[1] = var;
  }

  if(args_cnt==2 && strcmp(args[1],"--help")==0){ //for help
    printf("\nls:\n");
    printf("\t-list directory contents\n");
    printf("\t-Usage: ls [Directory]...\n");
    return 1;
  }

  int i = 1;
  while (i<args_cnt) {// loop for every input path

    struct dirent *entries; // Pointer for directory entry

    int flag = dir_file(args[i]);  //0==FILE , 1==DIRECTORY , -1==ERROR

    if(flag==1 && access(args[i],F_OK)==0){//DIRECTORY: Need to check access
      printf(RED "%s:\n" RESET, args[i]);
      printf("---> ");

      DIR *dir = opendir(args[i]);//DIR pointer for directory
      char temp[1024]; //temporary variable storing the path of every entry and change as i changes.

      while ((entries = readdir(dir)) != NULL){

        if(strncmp(entries->d_name,".",1) || strncmp(entries->d_name,"..",1) ){
          strcpy(temp,args[i]);
          strcat(temp,"/");
          strcat(temp,entries->d_name);
          if(dir_file(temp)==1){ //is a directory
            printf( GREEN"%s" RESET, entries->d_name);
            printf("  ");
          }
          else{  //is a file
            printf(WHITE"%s" RESET, entries->d_name);
            printf("  ");
          }
          strcpy(temp,".");
        }
      }
      closedir(dir);
      printf("\n");

    }
    else{
      printf("ls:'%s', is not a directory\n",args[i]); //Print the error.
    }
    i++;
  }

  return 1; //returning 1 to continue the main loop of comet.
}
