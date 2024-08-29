#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
//    char *input;
//    char *user;
    char *pwd = (char *)malloc(FILENAME_MAX);
//    char *session_manager;
//    char *computer;
//    char *temp_pwd;
//    int len;
//    int i;

//    user = getenv("USER");
    getcwd(pwd, FILENAME_MAX);
//    session_manager = getenv("SESSION_MANAGER");
//    temp_pwd = strstr(pwd, user);
//    free(pwd);
/*    pwd = (char *)malloc(sizeof(char) * (strlen(temp_pwd) - strlen(user) + 1));
    len = strlen(user);
    i = 0;
    while (temp_pwd[len])
        pwd[i++] = temp_pwd[len++];
    pwd[i] = '\0';*/
    printf("%s\n", pwd);
}
