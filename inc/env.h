#ifndef ENV_H
#define ENV_H
char **copy_envp(char **envp);
char **modify_envp(char **old_envp, char *env);
#endif
