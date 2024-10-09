#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtin.h"
#include "alias.h"
#include "base.h"
#include "memory.h"

short exec_builtin_cmd(char **array, const short FLAG, alias_t head, const char *username,const char *cd_history)
{
  if(FLAG == LIST_CMD_BUILTIN) {
     if(!strcmp(array[1],"alias")) {
      alias_t current = head;
      if(current == NULL)
	return -1;
      unsigned short i = 0;
      while(1) {
	if(current->alias_name != NULL) {
	  printf("%s => %s\n",current->alias_name,current->alias_command);
	  i += 1;
	}
	if(current->next != NULL)
	  current = current->next;
	else {
	  printf("Total: %d\n",i);
	  break;
	}
      }
    } else printf("fshell : %s : Invalid parameter\n",array[1]);
  } else if(FLAG == CD_CMD_BUILTIN) {
    if(array[1] == NULL) {
      if(!strcmp(username,"root"))
	;
    }
    else if(!strncmp(array[1],"~",strlen("~")*sizeof(char))) {
      if(!strcmp(username,"root")) {
	char *tmp_dir = (char*)calloc(strlen(array[1])-strlen("~")+strlen("/root"), sizeof(char));
	strlcpy(tmp_dir, "/root", count_for_strlcpy("/root"));
	strcat(tmp_dir, array[1]+strlen("~")*sizeof(char));
	chdir(tmp_dir);
	free(tmp_dir);
      } else {
	char *tmp_dir = (char*)calloc(strlen(array[1])-strlen("~")+strlen(username)+strlen("/home/"),sizeof(char));
	strlcpy(tmp_dir, "/home/", count_for_strlcpy("/home/"));
	strcat(tmp_dir, username);
	strcat(tmp_dir, array[1]+strlen("~")*sizeof(char));
	chdir(tmp_dir);
	free(tmp_dir);
      }
    } else if(!strcmp(array[1],"....")) {
      chdir(cd_history);
      cd_history = getcurrentdir();
    } 
  } else if(FLAG == ALIAS_CMD_BUILTIN)
    upload_alias_node(head, array[1], array[2]);
  else if(FLAG == UNALIAS_CMD_BUILTIN)
    remove_alias_node(head, array[1]);
  else if(FLAG == SET_ENV_CMD_BUILTIN) {
    char *tmp_env = (char*)calloc(strlen(array[1])+strlen(array[2])+strlen("="),sizeof(char));
    strlcpy(tmp_env,array[1],count_for_strlcpy(array[1]));
    strcat(tmp_env,"=");
    strcat(tmp_env,array[2]);
    putenv(tmp_env);
  } else if(FLAG == UNSET_ENV_CMD_BUILTIN)
    unsetenv(array[1]);
    else if(FLAG == PRINT_CMD_BUILTIN) {
      char *tmp_put = getenv(array[1]),*tmp_put2 = getalias_command(head, array[1]);
      if(tmp_put != NULL)
	printf("env : %s => %s\n",array[1],tmp_put);
      else printf("env : %s : Invalid environment variable\n",array[1]);
      if(tmp_put2 != NULL)
	printf("alias : %s => %s\n",array[1],tmp_put2);
      else printf("alias : %s : Invalid alias variable\n",array[1]);
    }
  return 0;
}