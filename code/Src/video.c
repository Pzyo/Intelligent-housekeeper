#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

extern int Flag ;
extern int Mod ;


int Sen_Cmd(char * cmd);

int fd_fifo = -1 ;

int video(void)
{
	int x = 1,video_cont = 0;
	int ret ;
	//system("mplayer ./Video/123.avi -slave -quiet  -input file=/tmp/CuiHua &");

	//char * cmd = "madplay";
	char video_name[100][50];
	bzero( video_name, 5000);
	video_cont = dir("./Video", ".avi", video_name);
	char video_cmd_name[video_cont][50];
	

	//创建管道文件
	if( -1 == access("/tmp/CuiHua" , F_OK) ) 
	{	
		ret = mkfifo("/tmp/CuiHua", 0777);
		if (-1 == ret )
		{
			perror("mkfifo error  ");
			return -1 ;
		}
		printf("mkfifo succeed !\n");
	}
	//打开管道文件
	fd_fifo =  open("/tmp/CuiHua", O_RDWR);
	if ( -1 == fd_fifo)
	{
		perror("open CuiHua error ");
		return -1  ;
	}
	//发送命令
	while(1)
	{
		printf("Now Playing Video!\n");
		bmp_show("./BMPphoto/shipin.bmp");
		sleep(2);
		
		if(Flag == 31)
		{
			//printf("Hello!!!\n\n\n");
			sprintf( video_cmd_name[0], "mplayer %s -slave -quiet  -input file=/tmp/CuiHua &",video_name[0]);
			system(video_cmd_name[0]);
			Flag = 0;
		}
			
		else if(Flag == 38)				//暂停播放
		{
				//printf("Hello!!!\n\n\n");
				system("killall -SIGSTOP mplayer");
				Flag = 0;
		}
		else if(Flag == 39)				//继续播放
		{
				//printf("Hello!!!\n\n\n");
				system("killall -SIGCONT mplayer");
				Flag = 0;
		}
		
		else if(Flag == 33)
		{
			system("killall mplayer");
			if(x >= video_cont) x = 0;
			sprintf( video_cmd_name[x], "mplayer %s -slave -quiet  -input file=/tmp/CuiHua &",video_name[x]);
			system(video_cmd_name[x]);
			x++;
			Flag = 0;
		}			
		
		else if(Flag == 34)
		{
			system("killall mplayer");
			if(x >= video_cont) x = 0;
			sprintf( video_cmd_name[x], "mplayer %s -slave -quiet  -input file=/tmp/CuiHua &",video_name[x]);
			system(video_cmd_name[x]);
			x--;
			Flag = 0;
		}
		
		else if(Flag == 30)
		{
			
			system("killall mplayer");
			bmp_show("./BMPphoto/main.bmp");
			Mod = 0;
			Flag = 0;
			break;
		}
	}
	
	//关闭文件
	close(fd_fifo);

	return 0;
}

int Sen_Cmd(char * cmd)
{
	write( fd_fifo , cmd ,  strlen(cmd));
	return 0 ;
}