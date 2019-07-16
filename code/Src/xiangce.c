#include <stdio.h>
#include <strings.h>

int dir(char * pathname, char * type, char file_name[][50]);

extern int Flag ;
extern int Mod ;


int Photo_album(void)
{
	int i, bmp_cont = 0;
	int photonum = 0 ;
	int tmp = 0 ,touch = 1;
	
	lcd_init();

	char file_name[100][50];
	bzero( file_name, 5000);
	
	bmp_cont = dir("./JPG", ".jpg", file_name);
	
	for(i=0; i<bmp_cont; i++)
	{
		printf("%s , %s\n ", __FUNCTION__, file_name[i]);
	}
	
	lcd_draw_jpg( 0, 0, file_name[photonum]);
	while(1)
	{
		
		if(Flag == 21)
		{
			bmp_show("./BMPphoto/main.bmp");
			Mod = 0;
			Flag = 0;
			break;
		}
		
		else if(Flag == 22)
		{
			tmp ++;
			if(tmp >= bmp_cont)
			{
				tmp = 0;
			}
			lcd_draw_jpg( 0, 0, file_name[tmp]);
			
			
			Flag = 0;
		}
		
		else if(Flag == 23)
		{
			tmp --;
			if(tmp < 0)
			{
				tmp = bmp_cont - 1;
			}
			lcd_draw_jpg( 0, 0, file_name[tmp]);
			
			Flag = 0;
		}
		
		else if(Flag == 24)
		{
			while(Flag == 24)
			{
				tmp = photonum;
				lcd_draw_jpg( 0, 0, file_name[tmp]);
				sleep(2);
				if(photonum >= bmp_cont) 
					photonum = 0;
				else 
					photonum ++;
			}
		}
		else if(Flag == 25)
		{
			lcd_draw_jpg( 0, 0, file_name[tmp]);
			Flag = 0;
		}
	}
	return 0;
}