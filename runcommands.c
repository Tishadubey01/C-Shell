#include "allheaders.h"
typedef long long ll;

int check_piping(char* cmd)
{
    char *piped_cmd = strstr(cmd, "|");
    return ( (piped_cmd==NULL)?0:1 );
}

int Execute(char* args)
{
        if(check_piping(args))
        {
            piping(args);
            return 0;
        }
        else if(check_redirection(args))
        {
            redirection(args);
            return 0;
        }
        int cmd_size = strlen(args);
        char curr_cmd_copy1[cmd_size+5];
        char curr_cmd_copy2[cmd_size+5];
        if(curr_cmd_copy1 == NULL)
        {
            printf("Memory Allocation error");
            printf("\n");
            return -1;
        }
        if(curr_cmd_copy2==NULL){
            printf("Memory Allocation error");
            printf("\n");
            return -1;
        }
        strcpy(curr_cmd_copy1,args);

        char* actual_cmd = strtok(curr_cmd_copy1," \t");
        strcpy(curr_cmd_copy2,args);
        char** builtin_cmd_array = builtin_cmds();

        int builtin_yn = 0;
        int builtin_ind = -1;
        int background_yn = 0;
        char **parsed_curr_cmd = parse_line(curr_cmd_copy2," \t\r\n");
        if(parsed_curr_cmd == NULL)
        {
            printf("Memory Allocation error");
            printf("\n");
            return -1;
        }
        int cmd_len = -1;
        while(1)
        {if(parsed_curr_cmd[cmd_len+1]!=NULL){
            cmd_len++;}
            else{
                break;
            }
        }
        if(cmd_len >-1)
        {
            if(strcmp("&",parsed_curr_cmd[cmd_len])==0){
            background_yn=1;
            parsed_curr_cmd[cmd_len]=NULL;}
        }
        
        int it=0;
        while(it < total_builtin_count())
        {
            if(strcmp(actual_cmd,builtin_cmd_array[it]) == 0)
            {
                builtin_yn = 1;
                builtin_ind = it;
                it++;
            }else{
                it++;
            }
        }

        int forkReturn = fork();

        if(forkReturn < 0)  
        {
            perror("Fork Error");
        }
        else if(forkReturn == 0) 
        {
            setpgid(0,0);
            if(builtin_yn)
            {
                exit(EXIT_SUCCESS);
            }
            else
            {
                int ret = execvp(parsed_curr_cmd[0],parsed_curr_cmd);
                if(ret==-1)
                {
                    perror("Execvp");
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS); 
                fflush(stdout);
            }
            
        }
        else   
        {
            int child_status;
            if(builtin_yn==1)
            {
                builtin_funcs(builtin_ind,parsed_curr_cmd);
            }

            else if( (background_yn==0) )
            {
                foreground_pid=forkReturn;
                if(waitpid(forkReturn,&child_status,WUNTRACED)==-1)
                {
                    perror("WaitPid");
                }
                int inif=0;
                if(WIFSTOPPED(child_status))
                {
                    back_jobs[count_background_task].pid = foreground_pid;
                    inif++;
                    back_jobs[count_background_task++].cmd = args;
                }
                foreground_pid=0;
            }
            else
            {
                signal(SIGCHLD,child_termination_handler);
                Add_background_proc(forkReturn,args);
            }
        }

    return 0;

}

void execute(char** args)
{
    int i = -1;
    while(args[++i] != NULL)
    {
        Execute(args[i]);
    }
}

void z_handler()
{
    if(foreground_pid>0 && foreground_pid!=getpid())
    {
        int ret = kill(foreground_pid,SIGSTOP);
        if(ret==-1)
        {
            perror("CTRL_Z");
        }
    }
}

void c_handler()
{
    if(foreground_pid>0 && foreground_pid!=getpid())
    {
        int ret = kill(foreground_pid,SIGKILL);
        if(ret==-1)
        {
            perror("CTRL_C");
        }
    }
    else{}
}

void child_termination_handler()
{ 
    int status;
    pid_t pid;
    int b_job=-1;
    
    pid = waitpid(-1, &status, WNOHANG);
    if(pid>0)
    {   int i=0;
        while(i<count_background_task)
        {
            if(back_jobs[i].pid==pid)
            {
                b_job = i;
                break;
            }i++;
        }

        if(b_job!=-1)
        {
            if(WIFEXITED(status))
            {
                if(EXIT_SUCCESS==WEXITSTATUS(status))
                {
                    fprintf(stderr, "\n %s with pid %d exited normally \n", back_jobs[b_job].cmd, back_jobs[b_job].pid);
                }
                else if(EXIT_SUCCESS!=WEXITSTATUS(status))
                {
                    fprintf(stderr, "\n %s with pid %d exited abnormally \n", back_jobs[b_job].cmd, back_jobs[b_job].pid);
                }
                
            }
                int i=b_job;
            while(i<count_background_task-1)
            {   int x=i;
                back_jobs[x].pid=back_jobs[x+1].pid;
                i++;
                back_jobs[x].cmd=back_jobs[x+1].cmd;
            }
            count_background_task--;
            
        }
    }
}

int check_redirection(char* cmd)
{
    char *in = strstr(cmd,"<");
    char *out = strstr(cmd,">");
   
    if((in==NULL) && (out==NULL)){
        return 0;
    }else{
        return 1;
    }
}

void Add_background_proc(int forkReturn,char* curr_cmd)
{
    curr_cmd[strlen(curr_cmd)-1]='\0';
    printf("Full command= %s",curr_cmd);
    printf("\n");
    printf("Adding above cmd to background process, process=%d ",forkReturn);
    printf("\n");
    back_jobs[count_background_task].cmd = curr_cmd;
    back_jobs[count_background_task++].pid = forkReturn;
}