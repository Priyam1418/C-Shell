int comet_cp(char **args){
	if(args_cnt==2 && strcmp(args[1],"--help")==0){
    printf("\ncp:\n");
    printf("\t-copy files and directory, use '-r' option to copy directory\n");
    printf("\t-Usage: cp [Source] [Destination] | cp -r [Source_Directory] [Destination_Directory]\n");
    return 1;
  }
	int r = 0; //flag for recursive call
	if(args[1]!=NULL){
		if(strcmp(args[1],"-r")==0){ //checking for -r option
			r = 1; //flag updated when called
		}
	}

  if(args_cnt<3+r){ //invalid syntax
		printf("\nUsage: cp [Source] [Destination] | cp -r [Source_Directory] [Destination_Directory]\n");
		printf("Missing few arguments:\tMinimum 3 arguments required, Only %d provided\n\n",args_cnt);
    return 1;
  }
  else{
    if(r==0){ //when recursive call is not made.
      char src_path[1024], dest_path[1024];
      strcpy(dest_path,args[args_cnt-1]);//destination path

      if(access(dest_path,F_OK)==-1){ //If destination path is not found
        if(args_cnt>3){
					printf("\n'%s': No such Directory, Try 'mkdir %s'.\n\n",dest_path,dest_path );
					return 1;
        }
        else{
          strcpy(src_path,args[1]);//source path

          int f = dir_file(src_path);
          if(f==0 && access(src_path,F_OK)==0){ //src is a file
						copy_file(src_path,dest_path,args);
          }
					else if(access(src_path,F_OK)!=0){ //if source file is not found
						printf("cp: '%s', %s\n", src_path,strerror(errno));
					}
          else{ //is source is a directory
            printf("omitting directory '%s', '-r' option required!\n", args[1]);
          }
        }
      }
      else if (access(dest_path,F_OK)==0){ //if destination exists
        int flag = dir_file(dest_path); //flag == 1->destination:directory; 0-> destination:file
        if(flag==1){ //Desination:DIRECTORY
          int i = 1; //loop counter for all the source files
          while(i<args_cnt-1){

            char s[1024]; //temporary variable storing source path
						strcpy(s,args[i]);
            char *name = basename(s); //basename strips leading directory and suffix from name.

            int check = dir_file(s);
            if(check==0 && access(s,F_OK)==0){// Case-I : Source: DIRECTORY-NO ; ACCESS-YES
              char temp[1024]; //temporary variable storing destination path of new file
              strcpy(temp,dest_path);
              strcat(temp,"/");
              strcat(temp,name);
							copy_file(s,temp,args);
            }
            else if(access(s,F_OK)==-1){ //Case-II: ACCESS-NO
              printf("cp:'%s': %s\n",name,strerror(errno));
            }
            else{ //Case-III: DIRECTORY-YES ; ACCESS-YES
              printf("cp: omitting directory '%s', '-r' option required!\n", name);
            }
            i++; //Increasing counter
          }
          return 1;

        }
        else if(flag==0){ //Destination:File
          if(args_cnt>3){//invalid syntax
            printf("\n'%s': is not a directory.\n\n",dest_path);
            return 1;
          }
          else{

            strcpy(src_path,args[1]);
            int g = dir_file(src_path);
            if(g==0 && access(src_path,F_OK)==0){ // Case-I : Source: DIRECTORY-NO ; ACCESS-YES
							copy_file(src_path,dest_path,args);
            }
            else if(access(src_path,F_OK)==-1){//Case-II: ACCESS-NO
              printf("cp: '%s': %s\n\n",src_path,strerror(errno));
            }
            else{ //Case-III: DIRECTORY-YES ; ACCESS-YES
              printf("cp: omitting directory '%s', '-r' option required!\n\n", src_path);
            }
          }
        }
      }
    }
    else{
      if(args_cnt!=4){ //Invalid Syntax
        printf("\nUsage: cp -r [Source] [Destination]\n");
  			printf("Given extra arguments:\tExactly 4 arguments required with option '-r', %d are provided\n\n",args_cnt );
      }
      else{
        char src_path[1024], dest_path[1024];
        strcpy(dest_path,args[args_cnt-1]);//Destination
        strcpy(src_path,args[args_cnt-2]);//Source
        int f_src = dir_file(src_path);
        int f_dest = dir_file(dest_path);

        if(access(dest_path,F_OK)==0 && f_dest==1){// Desination ACCESS:YES ; DIRECTORY:YES
          if(access(src_path,F_OK)==0 && f_src==1){// Source ACCESS:YES ;  DIRECTORY:YES

						strcat(dest_path,"/");
            strcat(dest_path,basename(src_path));

            mkdir(dest_path,0777); //Make new directory with the name as source directory

            struct dirent *entries; //Entry pointer for directory
            DIR* dir = opendir(src_path);
            while ((entries = readdir(dir)) != NULL){

              char t_src[1024]; //temporary var storing path of source in the loop
              strcpy(t_src,src_path);
              char t_dest[1024]; //temporary var storing path of destination in the loop
              strcpy(t_dest,dest_path);
              if(strncmp(entries->d_name,".",1) | strncmp(entries->d_name,"..",1) ){
                strcat(t_src,"/");
                strcat(t_src,entries->d_name);
                strcat(t_dest,"/");
                if(dir_file(t_src)==1){ //Entry is a subdirectory which is omitted.
                  printf(GREEN "omitting subdirectory '%s'\n" RESET, entries->d_name);
                }
                else{ //Entry is a file and is copied to destination
									strcat(t_dest,entries->d_name);
									copy_file(t_src,t_dest,args);
                }
              }
            }
            closedir(dir);
          }
					else if(access(src_path,F_OK)!=0){ //Source ACCESS:NO
						printf("cp: '%s', %s\n", args[args_cnt-2],strerror(errno));
					}
          else{ //Source is a File.
            printf("cp: '%s': Try without '-r'.\n",args[args_cnt-2] );
          }
        }
        else if(access(dest_path,F_OK)!=0){// Desination ACCESS:NO
          if(access(src_path,F_OK)==0 && f_src==1){ // Source ACCESS:YES ;  DIRECTORY:YES

						mkdir(dest_path,0777); //make new directory with given destination path

						strcat(dest_path,"/");
						strcat(dest_path,basename(src_path));
            mkdir(dest_path,0777); //make a new directory in the above newly made directory with given source name

	          struct dirent *entries; //Pointer for Source directory entry
	          DIR* dir = opendir(src_path);
	          while ((entries = readdir(dir)) != NULL){
	            char t_src[1024];//temporary var for source path in the loop
	            strcpy(t_src,src_path);
	            char t_dest[1024];//temporary var for destination path in the loop
	            strcpy(t_dest,dest_path);
	            if(strncmp(entries->d_name,".",1) | strncmp(entries->d_name,"..",1) ){
	              strcat(t_src,"/");
	              strcat(t_src,entries->d_name);
	              strcat(t_dest,"/");
	              if(dir_file(t_src)==1){ //subdirectory is omitted
	                printf(GREEN "cp: omitting subdirectory '%s'\n" RESET, entries->d_name);
	              }
	              else{
	                strcat(t_dest,entries->d_name);
									copy_file(t_src,t_dest,args);
	              }

	            }
	          }
	          closedir(dir);
          }
					else if(access(src_path,F_OK)!=0){//Source ACCESS:NO
						printf("cp: '%s', %s\n", args[args_cnt-2],strerror(errno));
					}
          else{ //Source is a file
            printf("cp: '%s': is not a directory. Try without '-r'.\n",args[args_cnt-2] );
          }
        }
				else{ //Destination is a file
					printf("cp: '%s': is not a directory. Try without '-r' or use mkdir %s\n",args[args_cnt-1],args[args_cnt-1] );
				}
      }
    }
  }
  return 1;
}
