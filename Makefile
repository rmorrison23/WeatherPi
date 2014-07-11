#################################################################################
#																				#
# Makefile for EECS 113 final project 											#
#																				#
#	Author: Ryan M. Morrison													#
#	Date:   May 2014															#
#																				#
#################################################################################

CC	= gcc
CFLAGS = -g -Wall -ansi
INCLUDE = -I include

vpath %.c src
vpath %.h include

LDFLAGS	= -L/usr/local/lib
LDLIBS    = -lwiringPi -lwiringPiDev -lpthread -lm

SRCS = main.c cimisData.c pumpOps.c screenRender.c sensorData.c timeUtils.c

OBJDIR := build
OBJS = $(SRCS:.c=.o)

MAIN = weather

.PHONY: depend clean

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(MAIN) $(OBJS) $(LDFLAGS) $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	
clean:
	@echo "[Clean]"
	rm *.o
	rm weather
	rm -f *.csv

depend: $(SRCS)
	makedepend $(INCLUDE) $^

#DO NOT DELETE THIS LINE
