int comet_mkdir(char **args){

	if(args_cnt==2 && strcmp(args[1],"--help")==0){
    printf("\nmkdir:\n");
    printf("\t-make directories\n");
    printf("\t-Usage: mkdir [Directory]...\n");
    return 1;
  }

	if(args[1]==NULL){ //invalid syntax
		printf("\nUsage: mkdir [Directory]...\n");
		printf("              ^^^^^^^^^ argument missing!\n\n");
	}
	else{
		int flag;
		int i =1;
		while (i<args_cnt) {//loop for each argument.
			char *dir_name = args[i];
			flag = mkdir(dir_name,0777); //0777:creates directory with full access to everyone.

			// check if directory is created or not
			if(flag==-1){ //-1==ERROR , 0==SUCCESS
				printf("mkdir: ‘%s’: %s\n\n",args[1],strerror(errno) );
			}
			i++;
		}
	}

	return 1;//returning 1 to continue the main loop of comet.
}
