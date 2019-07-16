#include <stdio.h>
#include <strings.h>
#include  <pthread.h>

//函数声明
void thread_music(void);
void thread_video(void);

int bmp_show(char * pathName);
int touch_xy(int *x, int *y);
int dir(char * pathname, char * type, char file_name[][50]);

int Flag = 0;

extern void * Ts_Xy( void * arg) ;
extern void * Linux_Video( void * arg);

int main(void)
{
	
	pthread_t TID ;
	pthread_create( &TID ,NULL,Ts_Xy, NULL);
	
	pthread_t TID_Video ;
	pthread_create( &TID_Video ,NULL,Linux_Video, NULL);
	
	bmp_show("./BMPphoto/main.bmp");
	
	while(1)
	{
		if(Flag == 1)									//音乐
		{
			bmp_show("./BMPphoto/yinyue.bmp");
			printf("Music!\n");
			music_play();
		}
		
		else if(Flag == 2)								//相册
		{	
			bmp_show("./BMPphoto/xiangce.bmp");
			printf("Photo_album!\n");
			Photo_album();
		}
		
		else if(Flag == 3)								//视频
		{	
			bmp_show("./BMPphoto/shipin.bmp");
			printf("Video!\n");
			video();
		}
		
		else if(Flag == 4)								//摄像头
		{	
			bmp_show("./BMPphoto/shexiangtou.bmp");
			printf("Camera!\n");
			linux_v4l2();
			
		}
		
		else if(Flag == 5)								//语音
		{	
			bmp_show("./BMPphoto/yuyin.bmp");
			printf("Welconme To Use Voice!\n");
			sleep(1);
			voice();
		}
		
		else if(Flag == 6)								//游戏
		{	
			bmp_show("./BMPphoto/game.bmp");
			printf("Game!\n");
			Game_Play();
			
		}
	}
	return 0;
}
