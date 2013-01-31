#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define unlikely(x)     __builtin_expect((x),0)
#define min(x,y)	(x<y?x:y)

ssize_t read(int fildes, void *buf, size_t nbyte) {
  struct stat statbuf;
  ssize_t r;

  fstat(fildes, &statbuf);

  if (unlikely(S_ISDIR(statbuf.st_mode))) {
    DIR *fdir;
    struct dirent *dent;
    ssize_t bytes;

    fdir = fdopendir(fildes);
    if (!fdir){
      perror("failed to fdopendir()");
      return -1; 
    }

    memset(buf, 0, nbyte);
    bytes=0;
    do {
      size_t sbytes;

      if ((dent = readdir(fdir)) != NULL){
        if (dent->d_name[0]=='.' &&
           (dent->d_name[1]=='.' || dent->d_name[1]=='\0'))
          continue;

        sbytes = strlen(dent->d_name);
        if (bytes + sbytes > nbyte)
          break;
	else
          bytes += sbytes;

        sprintf(buf, "%s %s", (char*)buf, dent->d_name);
      }
    } while (dent != NULL);

    r = min(bytes, nbyte);
  } else {
    r = __read(fildes, buf, nbyte);
  }

  return r;
}

