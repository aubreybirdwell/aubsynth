CC := gcc
CFLAGS := -W -Wall -Wpedantic

PROGRAM := SynthSound
SRC := main.c envelope.c sineWave.c floatInt.c writeWaveFile.c quickDecibels.c addBuffers.c transformDecibels.c addfreqs.c squareWave.c sawtoothWave.c triangleWave.c mtof.c ampMod.c sineFM.c additiveFM.c squareFM.c
OBJ := $(SRC:%.c=%.o)

.c.o :
	$(CC) $(CFLAGS) -c $<

$(PROGRAM) : $(OBJ)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJ)

clean :
	$(RM) $(PROGRAM) $(OBJ)


