#include "allheaders.h"
typedef long long ll;
int main()
{
    printf("\n\e[1;36m\t\t\t Welcome to Nutshell\n");
    printf("\n\e[1;36m \t\t\t The shell in a nut\n");
     //printf("Purple \t\t\t The shell in a nut\n");

    if(getcwd(HOME_DIRECTORY,500) == NULL)
    {
        perror("Home");
        return 0;
    }

    strcpy(HISTORY_PATH,HOME_DIRECTORY);
    strcat(HISTORY_PATH,"/history.txt");

    ll inloop=0;
    retrieve_history();
    count_background_task=0;
    signal(SIGINT,c_handler);
    int inif=0;
    signal(SIGCHLD,child_termination_handler);
    int inelif=0;
    signal(SIGTSTP,z_handler);
    EXIT_STAT=-1;
    INT_MAIN_PROC_PID=getpid();

    for(;;)
    {
        //printf("\e[40m");
        foreground_pid=0;
        if(prompt())
        {
            perror("CWD");
            return 0;
        }
        EXIT_STAT=-1;
        char** args = malloc(sizeof(char*)*10);
        char* line = (char*)malloc((sizeof(char))*500);

        line = read_line_command();

        if((line==NULL))
        {
            char** tempo = malloc(20*sizeof(char*));
            tempo[0] = "overkill";
            tempo[1] = NULL;
            inif++;
            overkill_cmd(tempo);
            free(tempo);
            exit(0);
        }
        else if(strcmp(line,"quit")==0){
            char** tempo = malloc(sizeof(char*)*20);
            tempo[0] = "overkill";
            tempo[1] = NULL;
            inloop++;
            overkill_cmd(tempo);
            
            free(tempo);
            exit(0);
        }
        args = parse_line(line,";");
        if(args == NULL)
        {
            return 0;
        }
        inloop++;
        execute(args);
        fflush(stdout);

    }
}
