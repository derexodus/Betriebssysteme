#include <stdio.h>
#include <stdlib.h>
#include <linux/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <error.h>



void strupr(char *sPtr)
{
  while(*sPtr != '\0')
    *sPtr = toupper(*sPtr);
}

/*int GoThrough(const char *source, const int level)
{
	DIR *dir;
	struct dirent *entry;

	if (!(dir = opendir(source)))
		return -1;
	if (!(entry = readdir(dir)))
		return -2;

	if (level == 0)
		printf("%s\n", source);

	do
	{
		if (entry->d_type == 4 && (strcmp(entry->d_name, ".") == 0))
			continue;

		if (entry->d_type == 4 && (strcmp(entry->d_name, "..") == 0))
			continue;


		if (entry->d_type == 4 && !(strcmp(entry->d_name, ".") == 0))
		{
			char *result = malloc(strlen(source) + strlen(entry->d_name) + 2);
			strcpy(result, source);
			strcat(result, "/");
			strcat(result, entry->d_name);
			GoThrough(result, level + 1);
		}
		printf("%s/%s\n", source, entry->d_name);
	} while ((entry = readdir(dir)) != NULL);

	closedir(dir);
	return 0;
}
*/



int GoThroughDir(const char *source, const int level)
{
    DIR *dir;
    struct dirent *entry;

    if(!(dir = opendir(source)))
        return -1;
    if(!(entry = readdir(dir)))
        return -2;

    if(level == 0)
        printf("%s\n",source);

    do
    {
        if(entry->d_type == 4 && (strcmp(entry->d_name, ".") == 0))
            continue;

        if(entry->d_type == 4 && (strcmp(entry->d_name, "..") == 0))
            continue;


        if(entry->d_type == 4 && !(strcmp(entry->d_name, ".") == 0))
        {
            char *result = malloc(strlen(source)+strlen(entry->d_name)+2);
            strcpy(result, source);
            strcat(result, "/");
            strcat(result,entry->d_name);
            GoThroughDir(result, level + 1);
        }
        printf("%s/%s\n", source, entry->d_name);
    }while((entry = readdir(dir)) != NULL);

    closedir(dir);
	return 0;
}



void do_dir(const char * dir_name, const char * const * parms)
{
    int i = 2;

  //  printf("%s   %s \n",dir_name, parms[1]);

    while(parms[i] != NULL && strcmp(parms[i],"(null)") != 0)
    {
        if(strcmp(parms[i],"-print") == 0)
        {
            GoThroughDir(dir_name,0);
        }
        else
        {
            printf("Unknown parameter!\n");
        }
        i++;
    }

    
}


int GoThroughFile(const char *source, const char *pattern)
{
	DIR *dir;
	struct dirent *entry;

	if (!(dir = opendir(source)))
		return -1;
	if (!(entry = readdir(dir)))
		return -2;

	do
	{
		if((entry->d_type == DT_REG) && (strcmp(entry->d_name, pattern)==0))
			printf("%s\n", entry->d_name);
	} while ((entry = readdir(dir)) != NULL);

	closedir(dir);
	return 0;
}


int GoThrough(const char *source, const int level)
{
	DIR *dir;
	struct dirent *entry;

	if (!(dir = opendir(source)))
		return -1;
	if (!(entry = readdir(dir)))
		return -2;

	if (level == 0)
		printf("%s\n", source);

	do
	{
		if (entry->d_type == 4 && (strcmp(entry->d_name, ".") == 0))
			continue;

		if (entry->d_type == 4 && (strcmp(entry->d_name, "..") == 0))
			continue;


		if (entry->d_type == 4 && !(strcmp(entry->d_name, ".") == 0))
		{
			char *result = malloc(strlen(source) + strlen(entry->d_name) + 2);
			strcpy(result, source);
			strcat(result, "/");
			strcat(result, entry->d_name);
			GoThroughDir(result, level + 1);
		}
		printf("%s/%s\n", source, entry->d_name);
	} while ((entry = readdir(dir)) != NULL);

	closedir(dir);
	return 0;
}


int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        GoThrough(".",0);
    }
    else if(argc == 2)
    {
        GoThroughFile(".",argv[1]);
    }
    else if(argc > 2)
    {
        do_dir(argv[1], (const char**)argv);
    }
	
	

    return 0;
}
