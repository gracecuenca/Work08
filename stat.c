#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <math.h>

void convert(long int num, char* new){
  //to store the floating point
  char fl[256];
  
  if (new == "B"){
    //printf("%ld %s", num, new);
    sprintf(fl, "%f", (float) num / 1);
  }

  long int divisor;
  if (new == "KB"){
    divisor = 1024;
    sprintf(fl, "%f", (float) num / divisor);
  }
  
  if(new == "MB"){
    divisor = (1024 * 1024);
    sprintf(fl, "%f", (float) num / divisor);
  }
  
  if (new == "GB"){
    divisor = (1024 * 1024 * 1024);
    sprintf(fl, "%f", (float) num / divisor);
  }

  printf("%s \t%s\n", fl, new);
}

char binaryperm(long int num, int i){
  if(i == 0)
    if(num)
      return 'x';
  if(i == 1)
    if(num)
      return 'w';
  if(i == 2)
    if(num)
      return 'r';
  return '-';
}

char* octalbinary(int num){
  char perm[3];
  char *permission = malloc(3);
  long remainder, base = 1, binary = 0;
  while (num > 0){
    remainder = num % 2;
    binary = binary + remainder * base;
    num = num / 2;
    base = base * 10;
  }
  //printf("\t%ld\n", binary);
  int i;
  //get permissions of each binary
  for (i = 0; i < 3; i++){
    //printf("%ld\n", binary % 2);
    perm[2 - i] = binaryperm(binary %2, i);
    binary /= 2;
  }
  //printf("%s\n", perm);
  //copy to return pointer
  strcpy(permission, perm);
  return permission;
}

void fp(int num){
  if(num == 0)
    return;
  char perm[3][3];
  char* permission;
  
  //gets last 3 digits, so permissions in octal
  //printf("%d\n", num);
  num %= (int)pow(8, 3);
  //printf("%o\n", num);
  //printf("%d\n", num);
  
  //throw each octal num to become binary
  //int i;
  //for (i = 0; i < 3; i++){
    //printf("%o\n", num % 8);
    char* temp = octalbinary(num % 8);
    //printf("\n\they there: %s\n", temp);
    //SOMETHING WEIRD IS HAPPENING HERE
    //strcpy(perm[i], temp);
    num /= 8;
    fp(num);
    printf("%s", temp);
    //}
}

//work
int main(){
  struct stat sb;
  stat("stat.c", &sb);
  printf("Size of File: %ld\n", sb.st_size);
  printf("Permissions of the File: %o\n", sb.st_mode);
  printf("%s\n", ctime(&sb.st_atime));

  printf("\nFile Size with Conversions (to six decimal places):\n");
  convert(sb.st_size, "B");
  convert(sb.st_size, "KB");
  convert(sb.st_size, "MB");
  convert(sb.st_size, "GB");
  
  printf("File Permissions:\n");
  fp(sb.st_mode);
  printf("\n\n\nThat's all!\n");
}
