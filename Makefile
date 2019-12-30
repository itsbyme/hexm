CC=gcc
INCLUDE=-Iinclude/

NAME=hexm

SOURCE=src/main.c src/hexm.c

OBJDIR=obj

OBJS = $(OBJDIR)/main.o $(OBJDIR)/hexm.o

_all: Welcome mkobjdir install clean

Welcome:
	@echo -e "Welcome to\e[0;32m $(NAME) \e[0m"

mkobjdir:
	@echo -e "\e[0;33m=>\e[0mCreating object's dirictory\r"
	@mkdir $(OBJDIR)

install: compiling $(OBJS)
	@echo -e "\e[0;33m=>\e[0mCompile hexm interpreter"
	@$(CC) $(OBJS) -o $(NAME)
	@echo -e "\e[0;32m=>\e[0mhexm interpreter compiled"

compiling:
	@echo -e "\e[0;33m=>\e[0mCompiling object files"

clean:
	@rm -rf $(OBJDIR)
	@echo Cleaned

obj/main.o: src/main.c
	
	@echo "CC 	src/main.c"
	@$(CC) -c src/main.c -o $(OBJDIR)/main.o $(INCLUDE)

obj/hexm.o: src/hexm.c
	@echo "CC 	src/hexm.c"
	@$(CC) -c src/hexm.c -o $(OBJDIR)/hexm.o $(INCLUDE)
