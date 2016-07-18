EXE=bates-die
CFLAGS += -std=gnu99 -Werror

ARGCONFIG=libargconfig
ARGCONFIG_INC=$(ARGCONFIG)/inc/argconfig
LIBARGCONFIG=$(ARGCONFIG)/libargconfig.a

CPPFLAGS += -std=gnu99 -Werror -I$(ARGCONFIG_INC) -D_GNU_SOURCE
CFLAGS += -g -std=c99 -I$(ARGCONFIG_INC)
LDLIBS += -lpthread

$(EXE): $(EXE).c $(LIBARGCONFIG)
	$(CC) $(CFLAGS) $(EXE).c -o $(EXE)

$(LIBARGCONFIG):
	make -C $(ARGCONFIG) libargconfig.a

clean:
	rm -rf *.o $(EXE) *~
	make -C $(ARGCONFIG) clean
