#include <stdio.h>
#include <stdlib.h>
#include <linux/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

void do_dir(const char *dir_name, const char *const *parms)
{
    DIR *dir;
    struct dirent *entry;

    if(!(dir = opendir(dir_name)))
        return;
    if(!(entry = readdir(dir)))
        return;

    do
    {
        if(entry->d_type == 4 && (strcmp(entry->d_name, "..") == 0))
            continue;
        if(entry->d_type == 4 && (strcmp(entry->d_name, ".") == 0))
            continue;
        if(entry->d_type == 4 && !(strcmp(entry->d_name, ".") == 0))
        {
             char *result = malloc(strlen(dir_name)+strlen(entry->d_name)+2);
             strcpy(result, dir_name);
             strcat(result, "/");
             strcat(result,entry->d_name);
             do_dir(result,NULL);
        }
       // printf("%d\n", entry->d_type);
        printf("%2d %5s %s/%s  %d\n", entry->d_ino, dir_name, entry->d_name);
    }while(entry = readdir(dir));
    closedir(dir);
}


int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        do_dir(".", NULL);
    }

    return 0;
}
