int comet_help(char **args){ //Brief information about all implemented commands
  printf("-------------///////////////////------------\n");
  printf("\n        Welcome to the world of Comet\n");
  printf("\nCreated By: Priyam Tongia(18110129)\n");
  printf("\nFollowing are the commands which is modifies in Comet:\n");
  printf("(Note: Try 'command --help' to know about specific command)\n");
  printf("\n1.cat:    -concatenate files and print on the standard output\n          -Usage: cat [FILES]...\n");
  printf("\n2.cd:     -change current working directory\n          -Usage: cd [DIR_NAME]\n");
  printf("\n3.chmod:  -change permissions of a file\n          -Usage: chmod MODE [FILE]\n");
  printf("\n4.clear:  -clear the shell\n          -Usage: clear\n");
  printf("\n5.cp:     -copy files and directory, use '-r' option to copy directory\n          -Usage: cp [Source] [Destination]\n                  cp -r [Source_Directory] [Destination_Directory]\n");
  printf("\n6.exit:   -termination of shell\n          -Usage: exit\n");
  printf("\n7.grep:   -print lines matching a given pattern(without inverted commas)\n          -Usage: grep Pattern [FILE...]\n");
  printf("\n8.ls:     -list directory contents\n          -Usage: ls [Directory]...\n");
  printf("\n9.mkdir:  -make directories\n          -Usage: mkdir [Directory]...\n");
  printf("\n10.mv:    -move(rename) files\n          -Usage: mv [Source] [Destination]\n");
  printf("\n11.pwd:   -print name of current working directory\n          -Usage: pwd\n");
  printf("\n12.rm:    -remove files or directories, use '-r' for removing directory recursively\n          -Usage: rm [FILES]...\n                  rm -r [DIRECTORY]...\n");
  printf("\nNote: BuiltIn commands of LINUX shell are also functional.\n");
  printf("\n-------------///////////////////------------\n");

  return 1;
}
