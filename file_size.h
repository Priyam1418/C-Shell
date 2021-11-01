unsigned long int file_size(char *path){
  FILE* fp = fopen(path, "r");
  fseek(fp, 0L, SEEK_END);
  long int size = ftell(fp);
  fclose(fp);
  return size;
}
