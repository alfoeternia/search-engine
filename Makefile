
CC := g++
SRCDIR := src
SRCEXT := cpp
BUILDDIR := build
TARGET_BUILDER := bin/builder
TARGET_SEARCH := bin/search

SOURCES_BUILDER := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT) ! -name search.cpp)
SOURCES_SEARCH := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT) ! -name builder.cpp)
OBJECTS_BUILDER := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES_BUILDER:.$(SRCEXT)=.o))
OBJECTS_SEARCH := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES_SEARCH:.$(SRCEXT)=.o))
CFLAGS = -O4 -g -Wall -Wextra -g -fmessage-length=0 -std=c++11 -Wno-write-strings -Wno-unused-parameter -fpermissive -lpthread -fopenmp -D_GLIBCXX_PARALLEL=1
LIB := -lboost_serialization -lpthread -fopenmp -D_GLIBCXX_PARALLEL=1
INC := -I include

all: $(TARGET_BUILDER) $(TARGET_SEARCH)

$(TARGET_BUILDER): $(OBJECTS_BUILDER)
	@echo " Linking builder..."
	@echo " $(CC) $^ -o $(TARGET_BUILDER) $(LIB)"; $(CC) $^ -o $(TARGET_BUILDER) $(LIB)
	strip $(TARGET_BUILDER)
	
$(TARGET_SEARCH): $(OBJECTS_SEARCH)
	@echo " Linking search..."
	@echo " $(CC) $^ -o $(TARGET_SEARCH) $(LIB)"; $(CC) $^ -o $(TARGET_SEARCH) $(LIB)
	strip $(TARGET_SEARCH)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR)"; $(RM) -r $(BUILDDIR)
	@echo " $(RM) -r $(TARGET_BUILDER)"; $(RM) -r $(TARGET_BUILDER)
	@echo " $(RM) -r $(TARGET_SEARCH)"; $(RM) -r $(TARGET_SEARCH)

default: all