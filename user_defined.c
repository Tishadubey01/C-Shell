#include "allheaders.h"
typedef long long ll;

int overkill_cmd(char **args)
{
    ll h = 0;
    while (args[h++] != NULL)
    {
        // h++;
    }
    if (h != 2)
    {
        write(2, "Error: overkill arguments.", 27);
        return -1;
    }
    int i = count_background_task - 1;
    while (i >= 0)
    {
        pid_t pid = back_jobs[i].pid;
        int ret = kill(pid, SIGKILL);
        if (ret >= 0)
        {
            back_jobs[i].cmd = NULL;
            count_background_task--;
            back_jobs[i].pid = -1;
        }
        else
        {
            perror("Background Kill");
            return -1;
        }
        i--;
    }
}

int sig_cmd(char **args)
{
    ll h = 0;
    while (args[h++] != NULL)
    {
        //h++;
    }
    int error = 0;
    if (h != 4)
    {
        write(2, "Error: sig arguments.", 21);
        error = 1;
        return -1;
    }

    int K_signal = atoi(args[2]);
    int K_num = atoi(args[1]);

    if (K_num > count_background_task)
    {
        write(2, "Error No such job\nRun jobs to see running jobs\n", 49);
        return -1;
    }
    else if (K_num == 0)
    {
        write(2, "Error No such job\nRun jobs to see running jobs\n", 49);
        return -1;
    }
    else if (K_num < 0)
    {
        write(2, "Error No such job\nRun jobs to see running jobs\n", 49);
        return -1;
    }
    int ret = kill(back_jobs[K_num - 1].pid, K_signal);
    int inretif;
    if (ret >= 0)
    {
        inretif++;
        printf("Signal %d was sent to proc %d", K_signal, K_num);
        printf("\n");
    }
    else
    {
        perror("KILL");
    }
}
int jobs_cmd(char **args)
{

    ll h = 0;
    while (args[h++] != NULL)
    {
        //printf("%s    %d\n",args[h],h);
    }
    if (h > 3)
    {   //printf("%d",h);
        write(2, "Error: jobs arguments.", 22);
        return -1;
    }
    //printf("%s\n %s\n ", args[0], args[1]);
    int rflag = 0;
    int flag = 0;
    int sflag = 0;
    if(args[1]!=NULL){
    if (strcmp(args[1], "-r") == 0)
    {
        rflag = 1;
        flag = 1;
    }
    else if (strcmp(args[1], "-s") == 0)
    {
        sflag = 1;
        flag = 1;
    }}
    int i = 0;
    while (i < count_background_task)
    {
        char proc_path[100];
        char buffer[100];
        

        sprintf(proc_path, "/proc/%d/status", back_jobs[i].pid);
        //char* status = (char*)malloc(15);
        char *status = malloc(sizeof(char) * (40));
        FILE *file = fopen(proc_path, "r");
        if (file == NULL)
        {
            perror("Error while accessing file '/proc/pid/status' ");
        }
        else
        {
            ll line_number = 0;
            while (fgets(buffer, 100, file) > 0)
            {
                if (line_number == 2)
                {
                    int add = 10;
                    status = buffer + add;
                    break;
                }
                line_number += 1;
            }
        }
        int length = strlen(status);
        status[length - 1] = '\0';
        length = strlen(status);
        if (flag == 0)
        {
            printf("[%d] %s\b %s [%d]", i + 1, status, back_jobs[i].cmd, back_jobs[i].pid);
            printf("\n");
        }
        else if (flag == 1)
        {
            if ((strcmp(status, "Running") == 0) && rflag == 1)
            {
                printf("[%d] %s\b %s [%d]", i + 1, status, back_jobs[i].cmd, back_jobs[i].pid);
                printf("\n");
            }
            else if((strcmp(status, "Stopped") == 0) && sflag == 1){
                printf("[%d] %s\b %s [%d]", i + 1, status, back_jobs[i].cmd, back_jobs[i].pid);
                printf("\n");
            }
        }

        i++;
    }
}

int bg_cmd(char **args)
{
    ll h = 0;
    while (args[h++] != NULL)
    {
        // h++;
    }
    if (h != 3)
    {
        write(2, "Error: bg arguments.", 20);
        return -1;
    }
    int K_num = atoi(args[1]);

    if (K_num > count_background_task)
    {
        write(2, "Error No such job\nRun jobs to see running jobs\n", 49);
        return -1;
    }
    else if (K_num <= 0)
    {
        write(2, "Error No such job\nRun jobs to see running jobs\n", 49);
        return -1;
    }
    int ret = kill(back_jobs[K_num - 1].pid, SIGCONT);
    int x = 0;
    if (ret >= 0)
    {
        printf("Signal %d was sent to proc %d, now Running", SIGCONT, K_num);
        printf("\n");
    }
    else
    {
        perror("KILL");
    }
}

int fg_cmd(char **args)
{
    ll h = 0;
    while (args[h++] != NULL)
    {
        // h++;
    }
    if (h != 3)
    {
        write(2, "Error: fg arguments.", 20);
        return -1;
    }
    int K_num = atoi(args[1]);

    if (K_num > count_background_task)
    {
        write(2, "Error No such job,Run jobs to see running jobs\n", 49);
        return -1;
    }
    else if (K_num <= 0)
    {
        write(2, "Error No such job,Run jobs to see running jobs\n", 49);
        return -1;
    }
    char *K_cmd = back_jobs[K_num - 1].cmd;
    int K_pid = back_jobs[K_num - 1].pid;
    int i = K_num - 1;
    int infor = 0;
    while (i < count_background_task - 1)
    {
        back_jobs[i].pid = back_jobs[i + 1].pid;
        infor++;
        back_jobs[i].cmd = back_jobs[i + 1].cmd;
        i++;
    } //printf("%d",infor);
    count_background_task -= 1;
    foreground_pid = K_pid;

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    int check = 0;
    tcsetpgrp(0, K_pid);
    int ret = kill(K_pid, SIGCONT);
    if (ret < 0)
    {
        perror("KILL");
        check = -1;
        return -1;
    }

    int stts;
    waitpid(K_pid, &stts, WUNTRACED);
    tcsetpgrp(0, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    check = 1;
    signal(SIGTTOU, SIG_DFL);
    int inifachk = 0;
    if (WIFSTOPPED(stts) > 0)
    {
        back_jobs[count_background_task].cmd = K_cmd;
        inifachk++;
        back_jobs[count_background_task++].pid = K_pid;
    }
    foreground_pid = 0;
}











