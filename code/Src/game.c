#include <stdio.h>

extern int Flag;
extern int Mod;
int game_photo;

int Game_Play(void)
{
	int game_cont = 0;
	int jpg_cont = 0;
	int x = 0;
	
	char * cmd = "./GBA/VisualBoyAdvance -3 ";
	char game_name[100][50];
	bzero( game_name, 5000);
	game_cont = dir("./GBA/GBAgame", ".gba", game_name);
	char game_cmd_name[game_cont][50];
	
	char file_name[100][50];
	bzero( file_name, 5000);
	jpg_cont = dir("./GBA/JPG", ".jpg", file_name);
	
	lcd_draw_jpg( 125, 50, file_name[x]);
	
	while(1)
	{
		if(Flag == 61)
		{
			bmp_show("./BMPphoto/main.bmp");
			Mod = 0;
			Flag = 0;
			break;
		}
			
		else if(Flag == 62)
		{
			sprintf( game_cmd_name[game_photo], "%s%s", cmd, game_name[game_photo]);
			system(game_cmd_name[game_photo]);
			Flag = 0;
		}
		
		else if(Flag == 63)
		{
			x++;
			if(x >= game_cont) x = 0;
			lcd_draw_jpg( 125, 50, file_name[x]);
			
			Flag = 0;
		}
		
		else if(Flag == 64)
		{	
			x--;
			if(x < 0) x = game_cont - 1;
			lcd_draw_jpg( 125, 50, file_name[x]);
			Flag = 0;
		}
		game_photo = x;
	}
	
	return 0;
}