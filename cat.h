int comet_cat(char **args){
  if(args_cnt==2 && strcmp(args[1],"--help")==0){
    printf("\ncat:\n");
    printf("\t-concatenate files and print on the standard output\n");
    printf("\t-Usage: cat [FILES]...\n");
    return 1;
  }

  if(args_cnt<2){  //Invalid syntax
    printf("\nUsage: cat [FILES]...\n");
		printf("            ^^^^^ argument missing!\n\n");
    return 1;
  }
  else{
    int i=1;

    while (args[i]!=NULL) {  //Run the loop till we reach the end

      //check if we have access to the file or not.
      if(access(args[i],F_OK)==-1){   //Path not found
        printf("cat: '%s': No such File or Directory\n",args[i]);
      }
      else if (access(args[i],F_OK)==0){  //Exists
        int flag = dir_file(args[i]);

        if(flag==1){ //It is a directory.
          printf("cat: '%s': Is a Directory\n",args[i]);
        }
        else if(flag==0){ //It is a regular file
          FILE *fptr;
          char c;
          fptr = fopen(args[i],"r");
        	// Read contents from file
        	c = fgetc(fptr);
        	while (c != EOF)
        	{
        		printf ("%c", c);
        		c = fgetc(fptr);
        	}

        	fclose(fptr);
        }
        else{  //Not supported.
            printf("\ncat: '%s': File type is not supported.\n\n",args[i]);
        }
      }
      i++;
    }
  }
	return 1;
}
