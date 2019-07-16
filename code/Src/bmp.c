#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>

#define H 480
#define W 800
#define bmp_size H*W*3
#define lcd_size H*W*4

int bmp_show(char * pathName)
{
	int x,y;
	int lcd_fd;
	int bmp_fd;
	int ret;
	int retval;
	unsigned int buf;
	
	//打开LCD设备
	lcd_fd = open("/dev/fb0", O_RDWR);
	if(lcd_fd == -1)
	{
		perror("open lcd device error!\n");
		return -1;
	}
	
	//内存映射
	unsigned int *lcd_fb_addr = mmap( NULL, lcd_size, PROT_READ|PROT_WRITE, MAP_SHARED, lcd_fd, 0);
	if(*(lcd_fb_addr) == -1)
	{
		perror("mmap error!\n");
		goto err;
	}
	//打开图片
	bmp_fd = open( pathName, O_RDONLY);
	if(bmp_fd == -1)
	{
		perror("open bmp error!\n");
		return -1;
	}
	
	//读写图片位置偏移
	ret = lseek( bmp_fd, 54, SEEK_SET);
	if(ret == -1)
	{
		perror("lseek error!\n");
		return -1;
	}
	
	//读取图片信息
	char bmp_buf[bmp_size];
	ret = read( bmp_fd, bmp_buf, bmp_size);
	//printf("read : %d\n", ret);
	
	//图片数据处理
	int lcd_buf[480][800];
	for(y=0; y<H; y++)
		for(x=0; x<W; x++)
		{
			lcd_buf[479-y][x] = bmp_buf[ (y*800 + x)*3 + 0] << 0  | 
								 bmp_buf[ (y*800 + x)*3 + 1] << 8  | 
								 bmp_buf[ (y*800 + x)*3 + 2] << 16 ;
		}
	//写入图片到LCD
	for(y=0; y<H; y++)
		for(x=0; x<W; x++)
		{
				*(lcd_fb_addr + x + y*800) = lcd_buf [y][x] ;
		}
	
	//关闭图片
	retval = munmap( lcd_fb_addr, lcd_size);
	if(retval == -1)
	{
		perror("unmap fb error\n");
		return -1;
	}

	retval = close(lcd_fd);
	if(retval == -1)
	{
		perror("open lcd device error\n");
		return -1;

	}
	
	return 0;
	
err:
	close(lcd_fd);
	return -1;
}

