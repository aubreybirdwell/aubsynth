CC := gcc
CFLAGS := -W -Wall -Wpedantic

PROGRAM := FFT_ECM
SRC := cfft.c rfft.c main_fft.c	
OBJ := $(SRC:%.c=%.o)

.c.o :
	$(CC) $(CFLAGS) -c $<

$(PROGRAM) : $(OBJ)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJ)

clean :
	$(RM) $(PROGRAM) $(OBJ)


