VERSION = 0.2
TARGET = minirc
PREFIX ?= /usr/local
CC = g++
CPPFLAGS = -std=c++11 -DVERSION=$(VERSION)
LFLAGS = 

BDIR = build
ODIR = objs
SDIR = minirc
INC = -I"minirc"
MD = mkdir -p

_OBJS = main.o minirc.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

.PHONY: all clean install uninstall directories

all : directories $(TARGET) example_binary example_text

directories: $(BDIR) $(ODIR)
	
$(BDIR):
	$(MD) $(BDIR)

$(ODIR):
	$(MD) $(ODIR)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(BDIR)/$(TARGET)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c $(INC) -o $@ $< $(CPPFLAGS)

example_binary:
	$(MAKE) -C example/binary clean
	$(MAKE) -C example/binary

example_text:
	$(MAKE) -C example/text clean
	$(MAKE) -C example/text
	
clean:
	rm -f $(ODIR)/*.o $(BDIR)/*
	$(MAKE) -C example/binary clean
	$(MAKE) -C example/text clean
install:
	install $(TARGET) $(PREFIX)/bin
uninstall:
	rm -rf $(PREFIX)/bin/$(TARGET)