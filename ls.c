#include "allheaders.h"
typedef long long ll;
void ls_display(int flag_l, int flag_a, char **direc_ptr)
{
    ll h = -1;
    char tilda[1] = "~";
    while (direc_ptr[++h] != NULL)
    {
        if (direc_ptr[h][0] == tilda[0])
        {   int tildaif;
            if (strcmp(direc_ptr[h], "~") == 0)
            {
                ls_single_display(flag_l, flag_a, HOME_DIRECTORY);
                tildaif=1;
            }
            else
            {
                char temp[500];
                if (!temp)
                {
                    printf("Memory Allocation Error");
                    printf("\n");
                    return;
                }

                strcpy(temp, HOME_DIRECTORY);
                tildaif=0;
                ls_single_display(flag_l, flag_a, strcat(temp, direc_ptr[h] + 1));
                //free(temp);
            }
        }
        else
        {
            ls_single_display(flag_l, flag_a, direc_ptr[h]);
        }
    }
    if (h == 0)
    {
        char currentdirec[2];
        currentdirec[0] = '.';
        currentdirec[1] = '\0';
        ls_single_display(flag_l, flag_a, currentdirec);
        //free(currentdirec);
    }
}

int ls_cmd(char **curr_ls)
{
    char **direc_ptr = malloc(32*sizeof(char*));
    if (!direc_ptr)
    {
        printf("Memory Allocation Error");
        printf("\n");
        return 0;
    }

    int flag_l = 0;
    int flag_a = 0;
    char dash[1] = "-";
    int direc_count = 0;
    int h = 0;
    int buf_size = 32;
    while (curr_ls[++h] != NULL)
    {
        //h++;
        if (curr_ls[h][0] == dash[0]) //flag
        {
            if (strcmp("-l", curr_ls[h]) == 0)
            {
                flag_l = 1;
            }
            else if (strcmp("-a", curr_ls[h]) == 0)
            {
                flag_a = 1;
            }
            else if ((strcmp("-la", curr_ls[h]) == 0) || (strcmp("-al", curr_ls[h]) == 0))
            {
                flag_a = 1;
                flag_l=1;
            }
        }
        else
        {
            direc_ptr[direc_count++] = curr_ls[h];
            if (direc_count >= buf_size)
            {   int add=32;
                buf_size=buf_size+add;
                char **direc_ptr = realloc(direc_ptr, buf_size * sizeof(char *));
                if (!direc_ptr)
                {
                    printf("Memory Allocation Error");
                    printf("\n");
                    printf("Too much directory");
                    printf("\n");
                    return -1;
                }
            }
        }
    }int exit=0;
    direc_ptr[direc_count] = NULL;
    ls_display(flag_l, flag_a, direc_ptr);
    exit=1;
    return 0;
}

void ls_single_display(int flag_l, int flag_a, char *direc_ptr)
{

    printf("%s :", direc_ptr);
    printf("\n");

    DIR *dir = opendir(direc_ptr);
    if (dir != NULL)
    {
        struct dirent *de;
        for (;;)
        {
            if ((de = readdir(dir)) == NULL)
            {
                break;
            }
            else
            {
                if (!flag_a)
                {
                    char dot[1] = ".";
                    if (de->d_name[0] == dot[0])
                    {
                        continue;
                    }
                    else
                    {
                        GLOBAL_DE = de;
                        descriptive_display(flag_l, direc_ptr);
                        
                    }
                }
                else
                {
                    GLOBAL_DE = de;
                    descriptive_display(flag_l, direc_ptr);
                }
            }
        }
        

        closedir(dir);
    }
    else
    {
        perror("Directory");
    }
    printf("\n");
}

void descriptive_display(int flag_l, char *direc_ptr)
{
    char filename[300];
    if (!filename)
    {
        printf("Memory Allocation Error");
        printf("\n");
        return;
    }

    strcpy(filename, GLOBAL_DE->d_name);

    if (!flag_l)
    {
        printf("%s", filename);
        printf("\n");
    }
    else
    {
        struct stat sb;
        char permissions[11];
        char *fullpath = (char *)malloc(strlen(direc_ptr) + strlen(filename) + 50);
        char username[300];
        if (!fullpath)
        {
            printf("Memory Allocation Error");
            printf("\n");
            return;
        }

        fullpath = strcpy(fullpath, direc_ptr);
        int filechk=0;
        fullpath = strcat(fullpath, "/");
        strcat(fullpath, filename);

        if (stat(fullpath, &sb) == -1)
        {
            perror("filename");
            filechk=-1;
            return;
        }

        SB = sb;
        char groupname[300];
        int sz = (int)sb.st_size;
        get_file_permission(permissions);
        get_file_groupname(groupname);
        get_file_username(username);
        char timedisplay[300];
        get_file_time(timedisplay);
        printf("%s %*d %s %s %*d %s %s", permissions, 4, (int)sb.st_nlink, username, groupname, 12, sz, timedisplay, filename);
        printf("\n");
    }

}

void get_file_permission(char *permissions)
{
    int i=0;
    while (i < 10)
    {
        permissions[i] = '-';
        i++;
    }

    if ((SB.st_mode & S_IFMT) == S_IFDIR)
    {
        permissions[0] = 'd';
        int d=1;
    }
    if (SB.st_mode & S_IRUSR)
    {
        permissions[1] = 'r';
        int r=1;
    }
    if (SB.st_mode & S_IWUSR)
    {
        permissions[2] = 'w';
        int w=1;
    }
    if (SB.st_mode & S_IXUSR)
    {
        permissions[3] = 'x';
        int x=1;
    }
    if (SB.st_mode & S_IWOTH)
    {
        permissions[8] = 'w';
        int w=1;
    }
    if (SB.st_mode & S_IWGRP)
    {
        permissions[5] = 'w';
        int w=1;
    }
    if (SB.st_mode & S_IRGRP)
    {
        permissions[4] = 'r';
        int r=1;
    }
    permissions[10] = '\0';
    if (SB.st_mode & S_IROTH)
    {
        permissions[7] = 'r';
        int r=1;
    }
    if (SB.st_mode & S_IXGRP)
    {
        permissions[6] = 'x';
        int x=1;
    }
    
    if (SB.st_mode & S_IXOTH)
    {
        permissions[9] = 'x';
        int x=1;
    }

    
}

void get_file_username(char *username)
{
    int size;
    struct passwd *usernm;
    usernm = getpwuid(SB.st_uid);
    size=300;
    strncpy(username, usernm->pw_name, size);
}

void get_file_time(char *timedisplay)
{
    time_t s;
    int inelif=0;
    int inelse=0;
    s = time(NULL);
    struct tm *tmstamp = localtime((time_t *)&SB.st_mtim);
    int curr_year = localtime(&s)->tm_year;
    int inif;
    if ((tmstamp->tm_year >= curr_year) && (tmstamp->tm_min < 10))
    {
        inif=1;
        sprintf(timedisplay, "%*d %*d %*d:0%*d", 2, tmstamp->tm_mon, 2, tmstamp->tm_mday, 2, tmstamp->tm_hour, 1, tmstamp->tm_min);
    }
    else if(tmstamp->tm_year >= curr_year){
        inelif=1;
        sprintf(timedisplay, "%*d %*d %*d:%*d", 2, tmstamp->tm_mon, 2, tmstamp->tm_mday, 2, tmstamp->tm_hour, 2, tmstamp->tm_min);
    }
    else
    {
        inelse=1;
        sprintf(timedisplay, "%*d %*d %*d", 2, tmstamp->tm_mon, 2, tmstamp->tm_mday, 5, tmstamp->tm_year);
    }
}
void get_file_groupname(char *groupname)
{
    struct passwd *groupnm;
    groupnm = getpwuid(SB.st_gid);
    strncpy(groupname, groupnm->pw_name, 300);
}