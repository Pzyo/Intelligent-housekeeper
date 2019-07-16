#include <stdio.h>

extern int Flag ;
extern int Mod ;

int voice(void)
{
	
	while(1)
	{
		
		
		
		if(Flag == 51)
		{
			printf("end!!!\n");
			system("killall voicectl");
			bmp_show("./BMPphoto/main.bmp");
			Mod = 0;
			Flag = 0;
			break;
		}
		else if(Flag == 52)
		{
			printf("start!!!!!\n");
			system("./voicectl 192.168.32.250");
			break;
		}
	}
}