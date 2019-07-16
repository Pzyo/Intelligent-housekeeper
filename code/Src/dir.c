#include <stdio.h>
#include <sys/types.h> 
#include <dirent.h>
#include <string.h>

int dir(char * pathname, char * type, char file_name[][50])
{
	int num = 0;
	
	DIR * fd_dir = opendir( pathname);
	if(fd_dir == NULL)
	{
		perror("open dir error");
		return -1;
	}
	
	struct dirent * dir_info;
	while((dir_info = readdir(fd_dir)) != NULL)
	{
		if(strstr( dir_info->d_name, type))
		{
			printf("File_Name : %s\n", dir_info->d_name);
			sprintf(file_name[num],"%s/%s", pathname, dir_info->d_name);
			num++;
		}
	}
	
	return num;
}