void remove_dir(char path[]){ //function to remove the directory recursively.

  struct dirent *entries; //Pointer for directory entry
  DIR* dir = opendir(path);
  while ((entries = readdir(dir)) != NULL){ //loop till we reach null in directory

    char temp[1024]; //temporary variable storing the path to remove it from folder.
    strcpy(temp,path);
    strcat(temp,"/");

    if(strncmp(entries->d_name,".",1) || strncmp(entries->d_name,"..",1) ){  //entries->d_name = name of each entry in folder has these structure.
      strcat(temp,entries->d_name);
      if(dir_file(temp)==1){// if directory then again a recursive call
        remove_dir(temp);
      }
      else{ //if file then remove it.
        remove(temp);
      }
    }
  }
  closedir(dir);
  remove(path); //delete the parent directory(args[i]) which is empty
}


int comet_rm(char **args){
  if(args_cnt==2 && strcmp(args[1],"--help")==0){
    printf("\nrm:\n");
    printf("\t-remove files or directories, use '-r' for removing directory recursively\n");
    printf("\t-Usage: rm [FILES]... | rm -r [DIRECTORY]...\n");
    return 1;
  }

  int r = 0; //flag used for checking if -r is given as option.

  if(args[1]!=NULL && strcmp(args[1],"-r")==0){
    r = 1; //recursive call is given
  }

  if(args_cnt<2+r){ //Invalid syntax
    printf("\nUsage: rm [FILES]... | rm -r [DIRECTORY]...\n");
		printf("\tMissing few arguments!\n\n");
    return 1;
  }
  else{
    int i=1+r; //counter for file

    while(i<args_cnt){ //loop for each argument given

      if(access(args[i],F_OK)==0){ //Path found.
        int f = dir_file(args[i]); // 0==File, 1==Directory
        if(f==0){ //File
          remove(args[i]);
        }
        else{
          if(r==0){ //no recursive call then directory will be omitted
            printf("rm: omitting directory '%s', '-r' option required.\n",args[i]);
          }
          else{ //recursive call, hence directory will be removed.
            remove_dir(args[i]);
          }
        }
      }
      else{  //Not found.
        printf("rm: '%s': %s\n", args[i],strerror(errno));
      }
      i++; //Increase counter
    }
  }
  return 1;
}
