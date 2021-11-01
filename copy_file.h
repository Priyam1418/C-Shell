void copy_file(char s[],char d[],char **args){
	int src_fd, dest_fd, err_dest, err_src;
	unsigned long int src_size = file_size(s); //file_size function will return the size of file
	unsigned char buffer[src_size];

	src_fd = open(s, O_RDONLY); //source file descriptor
	dest_fd = open(d, O_CREAT | O_WRONLY,S_IRUSR | S_IWUSR); //destination file descripter

	err_src = read(src_fd, buffer, src_size);
	if (err_src == -1) {
			printf("Error reading file '%s'.\n",args[1]);
	}
	err_dest = write(dest_fd, buffer, src_size);
	if (err_dest == -1){
			printf("Error writing to file.\n");
	}

	close(src_fd);
	close(dest_fd);
}
