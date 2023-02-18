#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
  
typedef struct dirent Dirent;
typedef struct stat Stat;

typedef struct {
  char name[256];
  __time_t mtime;
} FileData;

typedef struct {
  bool reversed;
} Opts;

Opts opts;

int comp(const void *elem1, const void *elem2)
{
  FileData a = *((FileData*)elem1);
  FileData b = *((FileData*)elem2);

  if (opts.reversed) {
    FileData c = a;
    a = b;
    b = c;
  }

  if (a.mtime > b.mtime) return 1;
  if (a.mtime < b.mtime) return -1;
  return 0;
}

int main(int argc, char **argv)
{
  for (;;) {
    switch(getopt(argc, argv, "rmac")) {
      case 'r':
        opts.reversed = true;
        continue;
    }

    break;
  }


  size_t length = 0;
  size_t cap = 1;

  FileData *files = malloc(sizeof(FileData) * cap);
  Dirent *dir;
  
  DIR *d = opendir(".");

  if (d) {
    while((dir = readdir(d)) != NULL) {
      char name[256];

      strncpy(name, dir->d_name, 256);

      if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
        continue;
      }

      if (length >= cap) {
        cap *= 2;
        files = realloc(files, sizeof(FileData) * cap);
      }

      Stat attr;
      stat(name, &attr);


      FileData file = { 
        .mtime = attr.st_mtim.tv_sec, 
      };

      strncpy(file.name, name, 256);

      files[length++] = file;
    }

    closedir(d);
  }

  qsort(files, length, sizeof(FileData), comp);

  for (int i = 0; i < length; i++) {
    printf("%s\n", files[i].name);
  }
}
