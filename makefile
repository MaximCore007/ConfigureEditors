BUILDDIR := build

CC := gcc
CFLAGS := -O0 -g

#$(info $$SRCS is [${SRCS}])
#$(info $$OBJS is [${OBJS}])

all: main.c | $(BUILDDIR)
	 $(CC) $(CFLAGS) $< -o $(BUILDDIR)/program
	
$(BUILDDIR):
	mkdir $(BUILDDIR)

debug: all

clean:
	 rm $(BUILDDIR)/*
