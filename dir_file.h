int dir_file(char *path){ //decides whether path is directory of file
  struct stat file_stat;
  stat(path, &file_stat);

  if(S_ISDIR(file_stat.st_mode)){ //Is a directory
    return 1;
  }
  if(S_ISREG(file_stat.st_mode)){ //Is a regular file
    return 0;
  }
  return -1; //Other type
}
