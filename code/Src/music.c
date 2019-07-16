#include <stdio.h>
#include <stdlib.h>
#include <linux/soundcard.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

extern int Flag ;
extern int Mod ;
extern int num ;

int music_play(void)
{
	int i, music_cont = 0;
	int ret;
	int left, right, vol = -1;
	
	int x = 1;
	
	char * cmd = "madplay";
	char music_name[100][50];
	bzero( music_name, 5000);
	music_cont = dir("./Music", ".mp3", music_name);
	char music_cmd_name[music_cont][50];
	
	int fd_mixer = open("/dev/mixer", O_RDWR);
	if(fd_mixer == -1)
	{
		perror("open mixer error!\n");
		return -1;
	}
	
	ret = ioctl( fd_mixer, MIXER_READ(SOUND_MIXER_OGAIN), &vol);
	if(ret == -1)
	{
		perror("read SOUND_MIXER_OGAIN ERROR!\n");
		return -1;
	}
	
	//拆分左右音道
	left = vol & 0xFF;
	right = (vol & 0xFF00) >>8;
			
	while(1)
	{
		printf("Now Playing Music!\n");
		sleep(2);
		
		if(Flag == 11)						//返回
		{
			system("killall madplay");
			bmp_show("./BMPphoto/main.bmp");
			Mod = 0;
			Flag = 0;
			break;
		}
		
		else if(Flag == 12)				//开始播放
		{		
				sprintf( music_cmd_name[0], "%s %s &", cmd, music_name[0]);
				system(music_cmd_name[0]);
				printf("Flag : %d\n",Flag);
				Flag = 0;
		}
		else if(Flag == 18)				//暂停播放
		{
				system("killall -SIGSTOP madplay");
				Flag = 0;
		}
		else if(Flag == 19)				//继续播放
		{
				system("killall -SIGCONT madplay");
				Flag = 0;
		}
		
		else if(Flag == 13)				//下一首
		{
			system("killall madplay");
			if(x >= music_cont) x = 0;
			sprintf( music_cmd_name[x], "%s %s &", cmd, music_name[x]);
			system(music_cmd_name[x]);
			x++;
			Flag = 0;
		}
		
		else if(Flag == 14)				//上一首
		{
			system("killall madplay");	
			if(x < 0) x = music_cont - 1;
			sprintf( music_cmd_name[x], "%s %s &", cmd, music_name[x]);
			system(music_cmd_name[x]);	
			x--;
			Flag = 0;
		}
		
		else if(Flag == 15)				//加大音量
		{
			left  += 3;
			right += 3;
			if(left > 100 && right > 100)
			{
				left = right =100;
				printf("Sound can't add more\n");
			}
				
			vol = left | (right<<8);
			ioctl( fd_mixer, MIXER_WRITE(SOUND_MIXER_OGAIN), &vol);
			Flag = 0;
		
		}
		
		else if(Flag == 16)				//减小音量
		{
			left  -= 3;
			right -= 3;
			if(left < 70 && right <70)
			{
				left = right =70;
				printf("Sound can't reduce more\n");
			}
				
			vol = left | (right<<8);
			ioctl( fd_mixer, MIXER_WRITE(SOUND_MIXER_OGAIN), &vol);
			Flag = 0;
			
		}
	}
		
}