#include "allheaders.h"





void add_in_history(char* cmd_line)
{
    int fd = open(HISTORY_PATH,O_RDONLY | O_WRONLY);
    if(fd < 0)
    {
        perror("History File Access Issue");
        return;
    }
    int zerocmd=0;
    if(stored_cmd_size == 20)
    {
        if(strcmp(cmd_line,command_history[stored_cmd_size-1])==0)
        {
            close(fd);
            return;
        }
        else
        {   int x=0;
            while(x<stored_cmd_size-1)
            {
                command_history[x]=command_history[x+1];
                x++;
            }
            command_history[stored_cmd_size-1]=cmd_line;
        }
    }
    else if(stored_cmd_size == 0)
    {
        command_history[stored_cmd_size++]=cmd_line;
        zerocmd=1;
        command_history[stored_cmd_size]=NULL;   
    }
    else if(stored_cmd_size < 20)
    {
        if(strcmp(cmd_line,command_history[stored_cmd_size-1])==0)
        {
            close(fd);
            zerocmd=-1;
            return;
        }
        else
        {
            zerocmd=-1;
            command_history[stored_cmd_size++]=cmd_line;
        }
    }

    int x=0;
    while(x<stored_cmd_size)
    {
        write(fd,command_history[x],strlen(command_history[x]));
        write(fd,"\n",1);
        x++;
    }
    close(fd);
    return;
}

void retrieve_history()
{
    int fd = open(HISTORY_PATH,O_RDONLY );
    if(fd < 0)
    {
        perror("History File Access Issue");
        return;
    }

    char *buffer = (char*)malloc(1000*(sizeof(char)));
    
    int szr = read(fd,buffer,1000);
    int chk;
    char* temp = strtok(buffer,"\n");
    while(temp!=NULL && (stored_cmd_size<20))
    {
        command_history[stored_cmd_size++]=temp;
        chk++;
        temp = strtok(NULL,"\n");
    }

    close(fd);
}

int history_cmd(char** history_args)
{
    int count_show_cmd = 10;
    int atint=0;
    if(history_args[1]!=NULL)
    {
        atint = atoi(history_args[1]);
        count_show_cmd=atint;
    }

    if(stored_cmd_size<count_show_cmd)
    {
        count_show_cmd=stored_cmd_size;
    }
    int i=stored_cmd_size-count_show_cmd;
    while(i<stored_cmd_size)
    {
        printf("%s",command_history[i]);
        printf("\n");
        i++;
    }

    
    return 0;
}
