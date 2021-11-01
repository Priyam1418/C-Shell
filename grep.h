int comet_grep(char **args){
  if(args_cnt==2 && strcmp(args[1],"--help")==0){
    printf("\ngrep:\n");
    printf("\t-print lines matching a given pattern(without inverted commas)\n");
    printf("\t-Usage: grep Pattern [FILE...]\n");
    return 1;
  }
  
  if(args_cnt==2){ //User Input case
      printf(BLUE"Enter the String to be searched in:\n"WHITE);
    // while (1) {   //uncomment this loop if we want to take input till EXIT_SUCCESS is reached.

      //Defining Variable and pointers
      size_t line_len = 0;
      char* line =NULL; //Pointer for user input
      int byt;
      byt = getline(&line, &line_len, stdin); //User Input

      if(byt==-1 && !feof(stdin)){
        printf("%s\n",strerror(errno)); //error
      }
      else{
        if (strstr(line,args[1])!=NULL){  //Match Found
          printf(MAG"Match Found" WHITE);
          printf(BLUE": "WHITE);
          printf("%s\n",line);
        }
        else{
          printf(RED"No match found.\n"WHITE);
        }
      }
      free(line); //deallocating the memory of line pointer.
    // }

    return 1; //returning 1 to continue the main loop of comet.
  }
  if(args_cnt<3){ //invalid syntax
    printf("\nUsage: grep Pattern [FILE...]\n");
    printf("Missing few arguments, minimum 3 required.\n\n");
    return 1;
  }
  else{

    //Defining Pointers and variables
    FILE* fp;
    size_t line_len = 0;
    char* line =NULL;
    int byt;
    int i=2;
    while(i<args_cnt){ //loop for each file argument

      if(access(args[i],F_OK)==0){ //Path exists

        if(dir_file(args[i])==0){ //is a file.
          fp = fopen(args[i],"r");
          byt = getline(&line, &line_len, fp); //reading line.
          if (byt==-1 && !feof(fp)){ //end of file
              break;
          }
          int linenum = 1; //for line number

          while (byt >= 0){ //loop runs till end of file
            if (strstr(line,args[1])!=NULL){ //Checks if our input pattern exists in line.
              printf(MAG"%s" WHITE, args[i]);
              printf(BLUE":"WHITE);
              printf(GREEN"%d",linenum );
              printf(BLUE":"WHITE);
              printf("%s",line);
            }
            byt = getline(&line, &line_len, fp);
            if (byt==-1 && !feof(fp)){ //end of file
                break;
            }
            linenum++;
          }
          fclose(fp);
        }
        else{ //is a directory
          printf("grep: '%s': Is a directory\n", args[i]);
        }

      }
      else{
        printf("grep: '%s': %s\n", args[i],strerror(errno)); //path not found error
      }
      printf("\n");
      i++;
    }
  }
  return 1;
}
