#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>

int return_size(char * file_name){
  struct stat sb;
  if(errno){
    printf("%s\n", strerror(errno));
  }
  printf("size of file: %lld\n", sb.st_size);
  return 0;
}

int return_mode(char * file_name){
  struct stat sb;
  if(errno){
    printf("%s\n", strerror(errno));
  }
  printf("permissions of the file: %o\n", sb.st_mode);
  return 0;
}

char * return_time(char * file_name){
  struct stat sb;
  if(errno){
    printf("%s\n", strerror(errno));
  }
  printf("%s\n", ctime(&sb.st_atime));
  return ctime(&sb.st_atime);
}

int main(){
  return_size("stat.c");
  return_mode("stat.c");
  return_time("stat.c");
  return 0;

  char mystring[200];

  printf("printing out the size for human eyes\n");
  sprintf(mystring, "%s", return_time("stat.c"));

  
}
