#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>

//work

int main(){
  struct stat sb;
  stat("stat.c", &sb);
  printf("size of file: %lld\n", sb.st_size);
  printf("permissions of the file: %o\n", sb.st_mode);
  printf("%s\n", ctime(&sb.st_atime));

  printf("File Permissions:\n");
  


}
