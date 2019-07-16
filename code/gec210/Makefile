LIBS = $(wildcard lib/*)
CC = arm-none-linux-gnueabi-gcc

CPPFLAGS += -I ./inc
CPPFLAGS += -I ./inc/libxml2
LDFLAGS  += -L ./lib

LDFLAGS += -lxml2
LDFLAGS += -lasound
LDFLAGS += -lz
LDFLAGS += -lvnet 
LDFLAGS += -lpthread

LDFLAGS += -Wl,-rpath=. -Wl,-rpath=./lib

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

voicectl: $(OBJS)	$(LIBS) 
#voicectl.c common.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -Wall

clean:
	rm voicectl *.o
