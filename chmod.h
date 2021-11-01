int comet_chmod(char **args){
  if(args_cnt==2 && strcmp(args[1],"--help")==0){
    printf("\nchmod:\n");
    printf("\t-change permissions of a file\n");
    printf("\t-Usage: chmod MODE [FILE]\n");
    return 1;
  }

  if(args_cnt<3){//invalid syntax
    printf("Usage: chmod MODE [FILE]\n");
    printf("\tMissing few arguments!\n");
    return 1;
  }
  else{
    long int mode = strtol(args[1],NULL,8); //converting mode to octal format
    int flag = chmod(args[2],mode); //0==Success , -1==Error
    if(flag!=0){
      printf("chmod: '%s', %s\n",args[2],strerror(errno));
    }
  }
  return 1;
}
