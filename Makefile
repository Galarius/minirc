PREFIX ?= /usr/local
CC = g++
CPPFLAGS = -std=c++11
LFLAGS = 
TARGET = minirc

BDIR = build
ODIR = objs
SDIR = minirc
INC = -I"minirc"
MD = mkdir -p

_OBJS = main.o minirc.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

.PHONY: all clean install uninstall directories

all : directories $(TARGET)

directories: $(BDIR) $(ODIR)
	
$(BDIR) :
	$(MD) $(BDIR)

$(ODIR) :
	$(MD) $(ODIR)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(BDIR)/$(TARGET)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c $(INC) -o $@ $< $(CPPFLAGS)

clean:
	rm -f $(ODIR)/*.o $(BDIR)/*
install:
	install $(TARGET) $(PREFIX)/bin
uninstall:
	rm -rf $(PREFIX)/bin/$(TARGET)