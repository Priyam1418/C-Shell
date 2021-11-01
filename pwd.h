int comet_pwd(char **args){
	if(args_cnt==2 && strcmp(args[1],"--help")==0){
    printf("\npwd:\n");
    printf("\t-print name of current working directory\n");
    printf("\t-Usage: pwd\n");
    return 1;
  }
	if(args_cnt>1){//Invalid Syntax
		printf("pwd:\n");
    printf("\t-print name of current working directory\n");
    printf("\t-Usage: pwd\n");
    return 1;
	}

	char pth[1024]; //var storing the path returned by getcwd
	if(getcwd(pth, sizeof(pth))!=NULL){
		printf("%s\n", pth);
	}
	else{ //home directory
		printf("/\n");
	}
  return 1;
}
