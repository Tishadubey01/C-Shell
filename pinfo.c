#include "allheaders.h"
typedef long long ll;
int pinfo_cmd(char **proc_ID)
{
    ll count_args = 0;
    pid_t proc_pid;
    while (proc_ID[count_args] != NULL)
    {
        count_args++;
    }

    

    if (count_args == 3)
    {
        proc_pid = atoi(proc_ID[1]);
    }
    else if (count_args == 2)
    {
        proc_pid = INT_MAIN_PROC_PID;
    }
    else
    {
        printf("Extra Argument");
        printf("\n");
    }

    printf("pid -- %d", proc_pid);
    printf("\n");

    char proc_path[100];

    sprintf(proc_path, "/proc/%d/status", proc_pid);
    char buffer[100];
    FILE *file = fopen(proc_path, "r");
    if (file == NULL)
    {
        perror("Error while accessing file '/proc/pid/status' ");
    }
    else
    {
        for (int line_number = 0;; line_number++)
        {
            if (fgets(buffer, 100, file))
            {
                if (line_number == 2)
                {
                    printf("Process Status -- %s", buffer + 7);
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    sprintf(proc_path, "/proc/%d/statm", proc_pid);
    int infile=0;
    file = fopen(proc_path, "r");
    if (file == NULL)
    {
        perror("Error while accessing file '/proc/pid/statm' ");
    }
    else
    {   int size=100;
        fgets(buffer, size, file);
        char *memory = strtok(buffer, " ");
        infile =1;
        ll mem_val = atoi(memory);
        mem_val *= 4;
        printf("Memory --    %lld KB", mem_val);
        printf("\n");
    }

    sprintf(proc_path, "/proc/%d/exe", proc_pid);
    ll len = readlink(proc_path, buffer, 1000);
    if (len == -1)
    {
        perror("Error while accessing file '/proc/pid/exe' ");
    }
    else
    {
        buffer[len] = '\0';

        int flag = 0;
        int index = 0;
        if (strlen(buffer) < strlen(HOME_DIRECTORY))
        {
            flag = 1;
        }
        else
        {   index=0;
            while (index < strlen(HOME_DIRECTORY))
            {
                if (buffer[index] != HOME_DIRECTORY[index])
                {
                    flag +=1;
                    break;
                }index++;
            }
        }
        if (flag)
        {
            printf("Executable Path --   %s", buffer);
            printf("\n");
        }
        else
        {
            printf("Executable Path --   ~%s", buffer + index);
            printf("\n");
        }
    }
    return 0;
}