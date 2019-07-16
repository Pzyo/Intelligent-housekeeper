#定义变量保存gcc,arm-linux-gcc
CC=arm-linux-gcc

T=main

CONFIG=-I../Inc -L../Lib -ljpeg -lapi_v4l2_arm

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

$(T):$(OBJS)
	$(CC) -o $@ $^ -lpthread $(CONFIG)

%.o:%.c
	$(CC) -c $< -o $@ $(CONFIG)

clean:
	rm *.o $(TARGET)
