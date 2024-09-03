#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "array.h"

cmd_t array_chain_parse(char *input,cmd_t array_chain)
{
  array_chain = (cmd_t)malloc(sizeof(struct cmd_or_pipe_chain));
  cmd_t current = array_chain;
  char *tmp_str = NULL;
  tmp_str = strtok(input,"&&");
  if(tmp_str != NULL) {
    char *new = (char*)malloc(sizeof(char)*strlen(tmp_str));
    strcpy(new,tmp_str);
    current->sentence = new;
    while(1) {
      tmp_str = strtok(NULL,"&&");
      if(tmp_str != NULL) {
	current->next = (cmd_t)malloc(sizeof(struct cmd_or_pipe_chain));
	current = current->next;
	char *new2 = (char*)malloc(sizeof(char)*strlen(tmp_str));
	strcpy(new2,tmp_str);
	current->sentence = new2;
	current->next = NULL;
      } else break;
    }
    return array_chain;
  } else return NULL;
}

pipe_t array_pipe_parse(char *input,pipe_t pipe_chain)
{
  pipe_chain = (pipe_t)malloc(sizeof(struct cmd_or_pipe_chain));
  pipe_t current = pipe_chain;
  char *tmp_str = NULL;
  tmp_str = strtok(input,"|");
  if(tmp_str != NULL) {
    char *new = (char*)malloc(sizeof(char)*strlen(tmp_str));
    strcpy(new,tmp_str);
    current->sentence = new;
    while(1) {
      tmp_str = strtok(NULL,"|");
      if(tmp_str != NULL) {
	current->next = (pipe_t)malloc(sizeof(struct cmd_or_pipe_chain));
	current = current->next;
	char *new2 = (char*)malloc(sizeof(char)*strlen(tmp_str));
	strcpy(new2,tmp_str);
	current->sentence = new2;
	current->next = NULL;
      } else break;
    }
    return pipe_chain;
  } else return NULL;
}
