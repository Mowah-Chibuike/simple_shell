#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "structs.h"
#include <signal.h>
extern char **environ;

/*-----------------add_list_node.c-------------------------*/
list_t *add_list_node(list_t **head, char *str, arg_t *args);
env_t *add_env_node(env_t **head, char *var, char *val, arg_t *args);
void print_list(alias_t *h);
coms_t *add_coms_node(coms_t **head, char **commands, char *op, arg_t *args);
alias_t *add_alias_node(alias_t **head, char *alias, char **val, char *str);

/********* alias.c *********/
void check_for_alias(arg_t *args);
int handle_alias(arg_t *args);

/********* _atoi.c *********/
int check_string(char *str);
int _atoi(char *str);

/*********** builtins.c ********/
int shell_exit(arg_t *args);
int print_env(arg_t *args);
int set_env(arg_t *args);
int un_set_env(arg_t *args);
int change_dir(arg_t *args);

/********* builtins_helpers.c *******/
int get_args_num(arg_t *args);
int check_args(arg_t *args, int n);
env_t *check_env(arg_t *args, char *variable);
void re_init_env(arg_t *args);
char *get_env_variable(arg_t *args, char *var);
void set_pwd(arg_t *args, char *oldpwd);
void check_for_variables(arg_t *args);

/*********** comments.c ********/
void check_comments(arg_t *args);

/*********** _dprintf.c ********/
int _dprintf(int fd, const char *format, ...);
char *_realoc(char *old, int size, char new);

/************ exec.c **********/
pid_t execute_command(arg_t *args);
int execute(arg_t *args);

/********** free.c *************/
void free_strings_array(char **array);
void free_env_node(env_t **node);
void free_all(arg_t *args);
void free_coms(coms_t *head);
void free_double(coms_t *list, char **array);
void free_alias(alias_t *head);

/*********** _getline.c *********/
ssize_t _getline(char **lineptr, int fd);

/*-------init.c------*/
arg_t *shell_init(void);

/******* integer_operations.c ******/
int _pow(int x, int y);

/*---------path.c---------------*/
char *search_path(arg_t *arguments);

/*--------------------realloc.c----------------*/
char **_realloc(char **old, int size, char *str);
char *_strcat(char *str1, char *str2);

/*********strings.h**********/
int _strlen(const char *str);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char **copy_string_array(char **main);
char **concat_strings_array(char **arr1, char **arr2, int n);

/************ tokenize.c *********/
char **get_args(char *command_line);
char **extract_commands(char **commands, int *index);
coms_t *get_commands(arg_t *args, char **commands);
char **get_alias_val(char *str);

#endif /* MAIN_H */
