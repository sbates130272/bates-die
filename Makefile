EXE=bates-die
CFLAGS += -std=gnu99 -Werror

$(EXE): $(EXE).c
	$(CC) $(CFLAGS) $(EXE).c -o $(EXE)

clean:
	rm -rf $(EXE) *.o *~
