int comet_mv(char **args){

  if(args_cnt==2 && strcmp(args[1],"--help")==0){
    printf("\nmv:\n");
    printf("\t-move(rename) files\n");
    printf("\t-Usage: mv [Source] [Destination]\n");
    return 1;
  }

  if(args_cnt<3){ //invalid syntax
    printf("\nUsage: mv [Source] [Destination]\n");
    printf("Missing few arguments:\tMinimum 3 arguments required, Only %d provided\n\n",args_cnt);
    return 1;
  }
  else{
    char src_path[1024], dest_path[1024]; //temporary path arrays
    strcpy(dest_path,args[args_cnt-1]);

    if(access(dest_path,F_OK)==-1){ //Destination not found-->Only file to file

      if(args_cnt>3){  //Invalid syntax
        printf("\n'%s': No such Directory, Try 'mkdir %s'.\n\n",args[args_cnt-1],args[args_cnt-1] );
        return 1;
      }
      else{
        strcpy(src_path,args[1]);
        int f = dir_file(src_path);
        if(f==0){//0->file

          copy_file(src_path,dest_path,args); //copy source file to destination
          remove(src_path); //remove source file
        }
        else{
          printf("omitting directory '%s'.\n", args[1]);
          return 1;
        }
      }
    }
    else if (access(dest_path,F_OK)==0){ //Desination found  file-->file or file-->directory
      int flag = dir_file(dest_path);
      if(flag==1){ //1-->directory
        int i = 1; //counter for source paths
        while(i<args_cnt-1){

          char s[1024]; //temporary array for updating source path in loop
          char *name = basename(args[i]);
          strcpy(s,args[i]);
          int check = dir_file(s);
          if(check==0 & access(s,F_OK)==0){// src is file and is accessible
            char temp[1024];
            strcpy(temp,dest_path);
            strcat(temp,"/");
            strcat(temp,name); //updated temporary destination path
            copy_file(s,temp,args);
            remove(s);
          }
          else if(access(s,F_OK)==-1){ //source not found
            printf("'%s': No such file found\n",name);
          }
          else{ //source is a directory
            printf("omitting directory '%s'\n", name);
          }
          i++;
        }
        return 1;

      }
      else if(flag==0){ //0-->file
        if(args_cnt>3){ //invalid syntax
          printf("\n'%s': is not a directory.\n\n",args[args_cnt-1]);
          return 1;
        }
        else{
          strcpy(src_path,args[1]);
          int g = dir_file(src_path);
          if(g==0 & access(src_path,F_OK)==0){//src is file and is accessible
            copy_file(src_path,dest_path,args); //copy source to destination
            remove(src_path); //remove source
          }
          else if(access(src_path,F_OK)==-1){ //source not found
            printf("'%s': No such file found\n",basename(src_path));
          }
          else{ //source is a directory
            printf("omitting directory '%s'.\n\n", args[1]);
          }
        }
      }
    }
  }
  return 1;
}
