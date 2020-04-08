CC := g++-9

CFLAGS=-std=c++11 -Wall -Wno-parentheses -Wno-deprecated

SRCDIR := .
OBJDIR := obj
TARGET := bin/flu

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(info $(SOURCES))

$(TARGET): $(OBJECTS)
	@mkdir -p ./bin
	@echo " Linking..."
	@echo " $(CC) -o $@ $^ $(CFLAGS)"; $(CC) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@ )
	@mkdir -p $(OBJDIR)
	@echo " $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(OBJDIR) $(TARGET)"; $(RM) -r $(OBJDIR) $(TARGET)

.PHONY: clean
