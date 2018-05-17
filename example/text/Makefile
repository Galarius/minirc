CC = g++
BDIR = build
TARGET=example
OUT  = $(BDIR)/$(TARGET)
ODIR = objs
MD = mkdir -p
RCC=../../build/minirc

_OBJS = example.o resource.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all : prepare $(TARGET) test

.PHONY: directories
directories: $(BDIR) $(ODIR)
	
$(BDIR) :
	$(MD) $(BDIR)
$(ODIR) :
	$(MD) $(ODIR)

$(TARGET): directories $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

$(ODIR)/example.o: example.cpp
	$(CC) -c -o $@ $<

$(ODIR)/resource.o: resource.cpp resource.hpp
	$(CC) -c -o $@ $<

.PHONY: prepare
prepare:
	$(RCC) data.rc

.PHONY: test
test:
	$(OUT)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(BDIR)/* resource.cpp resource.hpp restored.txt