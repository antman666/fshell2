#ifndef FSHELL_MEMORY_H_
#define FSHELL_MEMORY_H_

#include <string.h>

static inline unsigned int count_for_strlcpy(char *point)
{
  return (sizeof(char)*strlen(point)+sizeof(char));
}

#endif /*FSHELL_MEMORY_H_*/
