CC = g++
BDIR = build
TARGET=example
OUT  = $(BDIR)/$(TARGET)
ODIR = objs
MD = mkdir -p
RCC=../../build/minirc

_OBJS = example.o resource.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all : prepare test

.PHONY: directories prepare
directories: $(BDIR) $(ODIR)
	
$(BDIR) :
	$(MD) $(BDIR)
$(ODIR) :
	$(MD) $(ODIR)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

$(ODIR)/%.o: %.cpp
	$(CC) -c -o $@ $<

prepare: directories
	$(RCC) data.rc

test: prepare $(TARGET)
	$(OUT)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(BDIR)/*