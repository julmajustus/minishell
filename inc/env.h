#ifndef ENV_H
#define ENV_H
char **copy_env(char **envp);
char **delete_env_line(char **copy, char *str);
char **replace_or_create_env_line(char **copy, char *str);
#endif
