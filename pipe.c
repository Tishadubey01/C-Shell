#include "allheaders.h"
typedef long long ll;
int piping(char *cmd)
{
    char **piped_element = parse_line(cmd, "|");
    if (piped_element != NULL)
    {
        //do not return
    }else{
        return -1;
    }
    int fd;
    int p_arr[2];
    pid_t forkReturn;
    int chk=0;
    ll p_index = -1;
    while (piped_element[++p_index] != NULL)
        {
            pipe(p_arr);
            forkReturn = fork();
            if (forkReturn <= -1)
            {
                perror("PIPING FORK");
            }
            else if (forkReturn > 0)
            {
                wait(NULL);
                close(p_arr[1]);
                ll x=p_arr[0];
                fd = x;
            }
            else
            {
                dup2(fd, 0);
                if (piped_element[p_index + 1] != NULL)
                {
                    dup2(p_arr[1], 1);
                }
                close(p_arr[0]);
                Execute(piped_element[p_index]);
                chk=1;
                exit(2);
            }
        }
    
}