# Makefile for the smash program
CC = gcc
CFLAGS = -g -Wall -Wextra
CCLINK = $(CC)
OBJS =  signals.o history.o jobs_linked_list.o commands.o smash.o
RM = rm -f
# Creating the  executable
smash: $(OBJS)
	$(CCLINK) -o smash $(OBJS)
# Creating the object files
history.o: history.c history.h
signals.o: signals.c signals.h
jobs_linked_list.o: jobs_linked_list.c jobs_linked_list.h
commands.o: commands.c commands.h
smash.o: smash.c commands.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*



# build tests
build-tests: .build-tests-post

.build-tests-pre:
# Add your pre 'build-tests' code here...

.build-tests-post: .build-tests-impl
# Add your post 'build-tests' code here...


# run tests
test: .test-post

.test-pre:
# Add your pre 'test' code here...

.test-post: .test-impl
# Add your post 'test' code here...
