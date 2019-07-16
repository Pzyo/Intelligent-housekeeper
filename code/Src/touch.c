#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

extern int Flag;
int Mod = 0; //0主界面	1音乐	2相册	3视频	4摄像头		5语音	6游戏
int num = 0;
extern int game_photo;

void * Ts_Xy( void * arg)
{	
	int cont = 0;
	int video_cont = 0;
	int photo_cont = 1;
	int jpg_cont;
	// 决定需要判断的坐标值
	int x, y;
	
	char file_name[100][50];
	bzero( file_name, 5000);
	jpg_cont = dir("./GBA/JPG", ".jpg", file_name);
	
	while(1)
	{
		touch_xy( &x , &y);
		printf("Func: %s (%d,%d)\n", __FUNCTION__ , x, y  );

		if (0 == Mod )		//主界面
		{
			if (x > 555 && x < 760 && y > 263 && y < 393)
			{
				/* 音乐 */
				Mod = 1 ;
				Flag = 1 ;
			}
			else if (x > 35 && x < 226 && y > 55 && y < 183)
			{
				/* 相册 */
				Mod = 2 ;
				Flag = 2 ;
			}
			else if (x > 556 && x < 756 && y > 53 && y < 200)
			{
				/* 视频 */
				Mod = 3 ;
				Flag = 3 ;
			}
			else if (x > 36 && x < 231 && y > 257 && y < 385)
			{
				/* 摄像头 */
				Mod = 4 ;
				Flag = 4 ;
			}
			else if (x > 321 && x < 486 && y > 0 && y < 100)
			{
				/* 语音 */
				Mod = 5 ;
				Flag = 5 ;
			}
			else if(x > 316 && x < 471 && y > 393 && y < 480)
			{
				/* 游戏 */
				Mod = 6 ;
				Flag = 6 ;
			}
		}	
		
		else if (1 == Mod )	//音乐
		{
			if (x > 4 && x < 192 && y > 7 && y < 70)
			{
				/* 返回 */
				Flag = 11 ;
			}
			else if(x > 212 && x < 369 && y > 265 && y < 408)
			{
				cont ++;
				/*开始播放*/
				if( cont == 1)
				{
					Flag = 12 ;
					cont = 1 ;
				}
				/*暂停播放*/
				if( cont == 2)		
				{
					Flag = 18 ;
					cont = 2 ;
				}
					
				/*继续播放*/	
				if( cont == 3)
				{
					Flag = 19 ;	
					cont = 1 ;
				}		
			}
			else if(x > 402 && x < 534 && y > 285 && y < 393)
			{
				/*下一首*/
				Flag = 13 ;
				num ++;
			}
			else if(x > 47 && x < 182 && y > 285 && y < 393)
			{
				/*上一首*/
				Flag = 14 ;
				num --;
			}
			else if(x > 408 && x < 500 && y > 40 && y < 123)
			{
				/*加大音量*/
				Flag = 15 ;
			}
			else if(x > 408 && x < 500 && y > 128 && y < 203)
			{
				/*减小音量*/
				Flag = 16 ;
			}
		}
		
		else if (2 == Mod )	//相册
		{
			if (x > 720 && x < 800 && y > 0 && y < 75)
			{
				/* 返回 */
				Flag = 21 ;
			}
			else if (x > 720 && x < 800 && y > 328 && y < 480)
			{
				/* 下一张 */
				Flag = 22 ;
			}
			else if (x > 720 && x < 800 && y > 160 && y < 328)
			{
				/* 上一张 */
				Flag = 23 ;
			}
			else if (x > 630 && x < 715 && y > 160 && y <480)
			{
				//photo_cont++;
				/* 播放与暂停 */
				if(photo_cont == 1)
				{
					Flag = 24 ;
					photo_cont = 2;
				}
				else if(photo_cont == 2)
				{
					Flag = 25;
					photo_cont = 1;
					printf("%d\n",Flag);
				}
				
			}
		}
		
		else if (3 == Mod )	//视频
		{
			if(x > 730 && x < 800 && y > 0 && y < 60)
			{
				Flag = 30;//back
			}
			else if(x > 640 && x < 720 && y > 340 && y < 480)
			{
				//Flag = 31;//play
				video_cont ++;
				/*开始播放*/
				if( video_cont == 1)
				{
					Flag = 31 ;
					video_cont = 1 ;
				}
				/*暂停播放*/
				if( video_cont == 2)		
				{
					Flag = 38 ;
					video_cont = 2 ;
				}
					
				/*继续播放*/	
				if( video_cont == 3)
				{
					Flag = 39 ;	
					video_cont = 1 ;
				}
			}
			else if(x > 730 && x < 800 && y > 340 && y < 480)
			{
				Flag = 33;//down
			}
			else if(x > 730 && x < 800 && y > 184 && y < 340)
			{
				Flag = 34;//up
			}	
		}
		
		else if (4 == Mod )	//摄像头
		{
			if (x > 0 && x < 80 && y > 240 && y < 480)
			{
				/* 返回 */
				Flag = 41 ;
			}
			else if (x > 720 && x < 800 && y > 0 && y < 240)
			{
				/* 录像 */
				Flag = 42 ;
			}
			else if (x > 720 && x < 800 && y > 240 && y < 480)
			{
				/* 拍照 */
				Flag = 43 ;
			}					
			else if (x > 0 && x < 80 && y > 0 && y < 240)
			{
				/* 相册 */
				Flag = 44 ;
			}
			else
			{
				/* 开启 */
				Flag = 40 ;
			}
		}
		
		else if (5 == Mod )	//语音
		{
			if (x > 690 && x < 800 && y > 0 && y < 81)
			{
				/* 返回 */	
				Flag = 51 ;
			}
			else if (x > 298 && x < 544 && y > 156 && y < 292)
			{
				/* start */	
				Flag = 52 ;
			}
		}	
		
		else if (6 == Mod )	//游戏
		{
			
			if (x > 694 && x < 800 && y > 0 && y < 103)
			{
				/* 返回 */	
				Flag = 61 ;
			}
			else if (x > 630 && x < 800 && y > 358 && y < 480)
			{
				/* 开始游戏 */
				Flag = 62 ;
			}
			else if (x > 401 && x < 516 && y > 407 && y < 480)
			{
				/* 下一个游戏 */
				Flag = 63 ;
			}
			else if (x > 259 && x < 373 && y > 407 && y < 480)
			{
				/* 上一个游戏 */
				Flag = 64 ;
			}
			else if (x > 12 && x < 160 && y > 357 && y < 461)
			{
				/* 退出 */
				system("killall VisualBoyAdvance");
				sleep(1);
				bmp_show("./BMPphoto/game.bmp");
				usleep(10);
				lcd_draw_jpg( 125, 50, file_name[game_photo]);
			}
		}	
	}
}


int touch_xy(int *x, int *y)
{
	int count = 0;
	int ts_fd = open("/dev/event0", O_RDONLY);
	if(ts_fd == -1)
	{
		perror("open ts error\n");
		return -1;
	}
	
	struct input_event ts_event;
	while(1)
	{
		read( ts_fd, &ts_event, sizeof(struct  input_event));
		
		if(EV_ABS == ts_event.type)
			if(ABS_X == ts_event.code)
			{
				*x = ts_event.value;
				count++;
			}
			else if(ABS_Y == ts_event.code)
			{
				*y = ts_event.value;
				count++;
			}
		if(count == 2)
		{
			printf("%s: ( %d, %d)\n", __FUNCTION__ ,*x, *y );
			count = 0;
			break;
		}
	
	}	
	return 0;
}
