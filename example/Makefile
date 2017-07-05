CC = gcc
BDIR = build
OUT  = $(BDIR)/example
ODIR = objs
MD = mkdir -p

_OBJS = example.o resources.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all : directories example

.PHONY: directories
directories: $(BDIR) $(ODIR)
	
$(BDIR) :
	$(MD) $(BDIR)
$(ODIR) :
	$(MD) $(ODIR)

example: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(BDIR)/*