# Makefile for the smash program
CC = gcc
CFLAGS = -g -Wall -Wextra
CCLINK = $(CC)
OBJS =  signals.o history.o commands.o  jobs_list.o smash.o
RM = rm -f
# Creating the  executable
smash: $(OBJS)
	$(CCLINK) -o smash $(OBJS)
# Creating the object files
history.o: history.c history.h
signals.o: signals.c signals.h
commands.o: commands.c commands.h
jobs_list.o: jobs_list.c jobs_list.h
smash.o: smash.c commands.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

