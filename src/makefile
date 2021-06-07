# Name of the project
PROJ_NAME=siguel

# .c files
C_SOURCE=$(wildcard *.c)

# .h files
H_SOURCE=$(wildcard *.h)

# Object files
OBJ=$(C_SOURCE:.c=.o)

# Compiler
CC=gcc

# Flags for compiler
CC_FLAGS=-W         \
         -Wall      \
         -ansi      \
         -pedantic  \
		 -std=c99   \
		 -fstack-protector-all 

LINKER_FLAGS = -lm

#
# Compilation and linking
#
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CC_FLAGS) $(LINKER_FLAGS)

%.o: %.c %.h
	$(CC) -o $@ $< -c $(CC_FLAGS) $(LINKER_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< -c $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~