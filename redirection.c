#include "allheaders.h"
typedef long long ll;
void redirection(char *cmd)
{
    int flag_custm_inpt;
    int flag_custm_outpt;

    if (NULL == strstr(cmd, "<"))
    {
        flag_custm_inpt = 0;
    }
    else
    {
        flag_custm_inpt = 1;
    }
    if (NULL == strstr(cmd, ">>"))
    {
        flag_custm_outpt = 0;
    }
    else
    {
        flag_custm_outpt = 2;
    }

    if (flag_custm_outpt == 0)
    {
        if (NULL == strstr(cmd, ">"))
        {
            flag_custm_outpt = 0;
        }
        else
        {
            flag_custm_outpt = 1;
        }
    }

    char *input_ptr;
    int saved_stdout = dup(STDOUT_FILENO);
    char *input_file;
    char *output_ptr;
    int saved_stdin = dup(STDIN_FILENO);

    output_ptr = &cmd[0];
    char *output_file;
    if (flag_custm_outpt)
    {
        output_ptr = strtok(cmd, ">");
        output_file = strtok(NULL, ">");
        int inif=0;
        output_file = strtok(output_file, " \t");

        if (output_file == NULL)
        {
            write(2, "Error No output file provided\n", 31);
            inif++;
            return;
        }
    }

    input_ptr = output_ptr;
    if (flag_custm_inpt)
    {
        input_ptr = strtok(input_ptr, "<");
        input_file = strtok(NULL, "<");
        struct stat sb;
        input_file = strtok(input_file, " \t");

        if (input_file == NULL)
        {
            write(2, "Error No Input file provided\n", 30);
            return;
        }

        if (!((stat(input_file, &sb) == 0)))
        {
            if (!S_ISDIR(sb.st_mode))
            {
                write(2, "Error Input File doesnot exist\n", 32);
                return;
            }
        }
    }

    
    pid_t forkReturn = fork();
    char **input_arg = parse_line(input_ptr, " \t");
    int status;
    if (forkReturn < 0)
    {
        perror("REDIRECTION FORK");
        return;
    }
    else if (forkReturn > 0)
    {
        while (wait(&status) != forkReturn);
    }
    else if(forkReturn==0)
    {   int out_fd;
        if (flag_custm_inpt)
        {
            int in_fd = open(input_file, O_RDONLY);
            if (in_fd < 0)
            {
                perror("Input file");
                return;
            }
            dup2(in_fd, 0);
            close(in_fd);
        }
        
        if (flag_custm_outpt)
        {   int inelif=0;
            if (flag_custm_outpt != 2)
            {
                out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(out_fd, 1);
                close(out_fd);
            }
            else if(flag_custm_outpt==2)
            {
                out_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                dup2(out_fd, 1);
                inelif=1;
                close(out_fd);
            }
    
        }

        if (execvp(input_arg[0], input_arg) <= -1)
        {
            perror("Command not found");
            exit(EXIT_FAILURE);
        }

        dup2(saved_stdin, 0);
        close(saved_stdin);

        dup2(saved_stdout, 1);
        close(saved_stdout);
    }
}
