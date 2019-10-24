TARGET		= mtale
OBJS_TARGET	= main.o

CFLAGS += -g
LIBS += -lm -lc -lncursesw

include Makefile.in
