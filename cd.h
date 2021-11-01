int comet_cd(char **args){
  if(args_cnt==2 && strcmp(args[1],"--help")==0){
    printf("\ncd:\n");
    printf("\t-change current working directory\n");
    printf("\t-Usage: cd [DIR_NAME]\n");
    return 1;
  }
  int flag;

	if(args_cnt==1){ //Invalid Syntax
		printf("\nUsage: cd [DIR_NAME]\n");
		printf("           ^^^^^^^^ argument missing!\n");
    return 1;
	}
	else{
		flag = chdir(args[1]);  // 0== Success in changing Current working directory, -1==Error

		if(flag==-1){
			printf("\ncd: '%s', %s\n\n",args[1],strerror(errno)); //Print the specific error
		}
	}

	return 1;
}
