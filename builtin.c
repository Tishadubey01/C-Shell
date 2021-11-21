#include "allheaders.h"
typedef long long ll;

char* builtin_cmd[] = {"cd", "pwd","echo","ls","pinfo","history","jobs","overkill","sig","fg","bg"};
int (*builtin_func[])(char**)={
    &cd_cmd,
    &pwd_cmd,
    &echo_cmd,
    &ls_cmd,
    &pinfo_cmd,
    &history_cmd,
    &jobs_cmd,
    &overkill_cmd,
    &sig_cmd,
    &fg_cmd,
    &bg_cmd
    };

char** builtin_cmds()
{
    return builtin_cmd;
}

void builtin_funcs(int index,char** req_para)
{
    (*builtin_func[index])(req_para);
}
int total_builtin_count() 
{
    return (sizeof(builtin_cmd) / sizeof(char*));
}


int cd_cmd(char** desired_wd)
{
    EXIT_STAT=-1;
    ll h=0;
    while(desired_wd[h++]!=NULL){
       // h++;
    }

    if(h != 3)
    {
        printf("Unexpected arguments for cd command.");
        printf("\n");
        EXIT_STAT=0;
    }
    else
    {
        char tilda[1] = "~";
        char dash[1] = "-";
        if(desired_wd[1][0] == tilda[0] && strlen(desired_wd[1])==1)
        {
            if(chdir(HOME_DIRECTORY)==0)
            {
                
            }else{
                perror("cd: ~:");
                EXIT_STAT=0;
            }
        }
        else if (desired_wd[1][0] == tilda[0] && strlen(desired_wd[1])>1)
        {
            char temp_cwd[500];
            if(!temp_cwd)
            {
                printf("Memory Allocation Error");
                printf("\n");
                EXIT_STAT=0;
                return -1;
            }else{
                getcwd(temp_cwd,500);
            }

            int err=0;

            if(chdir(HOME_DIRECTORY)!=0)
            {
                perror("cd: ~:");
                EXIT_STAT=0;
                err++;
            }
            if(chdir(desired_wd[1]+2)!=0)
            {
                perror("cd: ChangePath: ");
                chdir(temp_cwd);
                EXIT_STAT=0;
            }
            //free(temp_cwd);
        }
        else if(desired_wd[1][0]==dash[0] && strlen(desired_wd[1])==1)
        {
            if(chdir("..")!=0)
            {
                perror("CD - Error");
                EXIT_STAT=0;
            }
            char tmp[100];
            getcwd(tmp,100);
            printf("%s",tmp);
            printf("\n");
        }
        else if(chdir(desired_wd[1])!=0)
        {
            perror("cd: ChagePath: ");
            EXIT_STAT=0;
        }
    }int chk=1;
    if(EXIT_STAT!=0)
    {
        EXIT_STAT=chk;
    }
    return 0;    
}

int pwd_cmd(char** pwd_para)
{
    EXIT_STAT=-1;
    ll h=0;
    while(pwd_para[h++]!=NULL)
    {//h++;
    }

    char temp_pwd[500];
    if(!temp_pwd)
    {
        printf("Memory Allocation Error");
        printf("\n");
        EXIT_STAT=0;
        return -1;
    }

    int err=0;
    if(getcwd(temp_pwd,500)==NULL)
    {
        perror("PWD");
        EXIT_STAT=0;
        err=1;
        return -1;
    }
    else
    {
        printf("%s",temp_pwd);
        printf("\n");
    }

    if(h > 2)
    {
        printf("Unknown Arguments");
        printf("\n");
        EXIT_STAT=0;
    }
    
    //free(temp_pwd);
    int chk=-1;
    if(EXIT_STAT!=0)
    {
        EXIT_STAT=chk;
    }
    return 0;
}

int echo_cmd(char** curr_string)
{
    EXIT_STAT=-1;
    ll h=1;
    while(curr_string[h]!=NULL)
    {
        if(curr_string[h+1]==NULL)
        {
            printf("%s",curr_string[h]);
            printf("\n");
            h++;
        }
        else
        {
            printf("%s ",curr_string[h]);
            h++;
        }        
    }
    EXIT_STAT=1;
    return 0;
}
