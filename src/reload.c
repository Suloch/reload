#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include<string.h>

void run(char * command)
{
  int val = system(command);
  if(val == 0)
  {
    printf("Program compiled successfully.\nRunning...\n--------------------------------\n");
    system("./output < input");
  }
  else
  {
    printf("\033[31;1;4m Compilation Failed!!!\033[0m\n" );
  }
  printf("\n--------------------------------\nPress Ctrl + C to exit...\n");
}

int main(int argc, char **argv)
{
  if(argc < 2)
  {
    printf("Invalid file name\n");
    return 1;
  }
  printf("Finding %s...\n", argv[1]);
  FILE *fp = fopen(argv[1], "r");
  if(fp == NULL)
  {
    printf("Error : file '%s' not found\n", argv[1]);
    return 2;
  }

  struct stat attrib;
  char time[50], new_time[50];
  char command[100];
  stat(argv[1], &attrib);
  strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&attrib.st_mtime));
  sprintf(command, "gcc -Wall %s -o output", argv[1]);
  run(command);
  while(1)
  {
    stat(argv[1], &attrib);
    strftime(new_time, 50, "%Y-%m-%d %H:%M:%S", localtime(&attrib.st_mtime));
    if(strcmp(time, new_time) != 0)
    {
      strcpy(time, new_time);
      run(command);
    }
  }
  return 0;
}
