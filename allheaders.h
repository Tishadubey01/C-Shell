#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <signal.h>
#define Purple "\033[0;35m"
#define Cyan "\033[0;36m"


struct dirent *GLOBAL_DE;
struct stat SB;
struct background_jobs{
    char* cmd;
    pid_t pid;
    char statuss[100];
};
int count_background_task;
struct background_jobs back_jobs[500]; 
struct stat SB;
int foreground_pid;
int INT_MAIN_PROC_PID;
int stored_cmd_size;

char HOME_DIRECTORY[500];
char HISTORY_PATH[600];

int EXIT_STAT;

int total_builtin_count();
char** builtin_cmds();
void builtin_funcs();



int cd_cmd(char** desired_wd);
int pwd_cmd(char** pwd_para);
int echo_cmd(char** curr_string);
int pinfo_cmd(char** proc_ID);

//int setenv_cmd(char** args);
//int unsetenv_cmd(char** args);
int jobs_cmd(char **args);
int overkill_cmd(char **args);
int sig_cmd(char** args);
int fg_cmd(char** args);
int bg_cmd(char** args);

int ls_cmd(char** curr_ls);

extern void ls_display(int flag_l,int flag_a,char** direc_ptr);
extern void ls_single_display(int flag_l,int flag_a,char* dir);
extern void descriptive_display(int flag_l,char* direc_ptr);




char* command_history[20];
int stored_cmd_size;
int size;
extern void retrieve_history();
int history_cmd(char** proc_ID);
extern void add_in_history(char* cmd_line);
extern void get_file_permission(char* permissions);
extern void get_file_username(char* username);
extern void get_file_groupname(char* groupname);
extern void get_file_time(char* timedisplay);

//int nightswatch_cmd(char** args);
extern void interrupt();
extern void newborn();
int check_keydown();
// int executecommands(char** args);
extern void execute(char** args);
int Execute(char* args);
extern void child_termination_handler();
extern void c_handler();
extern void z_handler();
int check_piping(char* cmd);
int check_redirection(char* cmd);
int piping(char* cmd);
extern void redirection(char* cmd);
int prompt();
char* read_line_command();
char** parse_line(char* line_read, char* delim_str);
extern void Add_background_proc(int forkReturn,char* curr_cmd);