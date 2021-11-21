#include "allheaders.h"
typedef long long ll;
char* read_line_command()
{
    char* line_for_return = NULL;
    ssize_t buff_size = 10;


    if( getline(&line_for_return, &buff_size, stdin) == -1 )
    {
        if(!(feof(stdin)))
        {
            perror("readline");
            return NULL;
        }
        else
        {
            perror("EOF");
            return NULL;
            
        }  
    }
    
    int length=strlen(line_for_return);
    if(length>0)
    {
        line_for_return[length-1]='\0';
    }
    if(length>0)
    {
        add_in_history(line_for_return); 
    }
    return line_for_return;
}

int prompt() 
{
    char *curr_user = (char*)malloc(100*sizeof(char));
    char *curr_host = (char*)malloc(100*sizeof(char));
    char *cwd = (char*)malloc(500*sizeof(char));
    int is_host = gethostname(curr_host,100);
    if((!curr_host) || (!curr_user) || (!cwd) )
    {
        printf("Memory Allocation Error");
        printf("\n");
        return 1;
    }

    if(is_host == -1)
    {
        curr_host = "No Host";
    }

    if(getlogin() != NULL)
    {
        curr_user = getlogin();
    }
    else
    {
        curr_user = "No User";
    }

    if(getcwd(cwd, 500)==NULL)
    {
        return 1;
    }

    int flag = 0;
    int index =0;
    if(strlen(cwd) < strlen(HOME_DIRECTORY))
    {
        flag =1;
    }
    else
    {   index=0;
        while(index < strlen(HOME_DIRECTORY))
        {
            if(cwd[index]!=HOME_DIRECTORY[index])
            {
                flag =1;
                break;
            } index++;
        }
        
    }
    
    
    if(!flag)
    {
        if(EXIT_STAT>=1)
        {
            printf("\n<\033[1;32m%s@%s\033[0m:\033[1;34m~%s\033[0m> ",curr_user,curr_host,cwd+index);
        }
        else if(EXIT_STAT<0)
        {
            printf("\n<\033[1;32m%s@%s\033[0m:\033[1;34m~%s\033[0m> ",curr_user,curr_host,cwd+index);
        }
        else
        {
            printf("\n(<\033[1;32m%s@%s\033[0m:\033[1;34m~%s\033[0m> ",curr_user,curr_host,cwd+index);
        }
        
    }
    else
    {
        if(EXIT_STAT>=1)
        {
            printf("\n<\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m> ",curr_user,curr_host,cwd);
        }
        else if(EXIT_STAT<0)
        {
            printf("\n<\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m> ",curr_user,curr_host,cwd);
        }
        else
        {
            printf("\n<\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m> ",curr_user,curr_host,cwd);
        }
    }
    return 0;
    
}
char** parse_line(char* line_read, char* delim_str)
{
    char* line_read_copy = (char*)malloc(strlen(line_read));
    int inif=0;
    if(!line_read_copy)
    {
        printf("Memory Allocation error");
        inif++;
        printf("\n");
        return NULL;
    }
    strcpy(line_read_copy,line_read);
    char** token_ptr_array = malloc(sizeof(char*)*32);
    int buff_size = 32;
    if(!token_ptr_array)
    {
        printf("Memory Allocation error");
        printf("\n");
        return NULL;
    }

    int index = 0;

    while (token_ptr_array[index-1] != NULL)
    {
        if(index==0)
        {
            token_ptr_array[index] = strtok(line_read_copy,delim_str);
            index++;
        }
        else
        {
            token_ptr_array[index] = strtok(NULL,delim_str);
            index++;
        }
        
        
        if( index >= buff_size )
        {
            buff_size=buff_size+32;
            token_ptr_array = realloc(token_ptr_array,buff_size*sizeof(char*));

            if(!token_ptr_array)
            {
                printf("Memory Allocation error");
                printf("\n");
                return NULL;
            }
        }
    }    
    
    
    return token_ptr_array;
}