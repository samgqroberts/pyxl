# ----------------------------------------
# Makefile for SylverStudios/LogoAnimation
# ----------------------------------------

# executable name
TARGET   = sylver

# compilation command - compiles .cpp sources into .o objects
CC       = g++

# linking command - links .o objects into sylver executable
LINKER   = g++ -o

# source, objects, and bin directory names
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

# both of the directories containing resultant artifacts
ARTIFACTDIRS = $(OBJDIR) $(BINDIR)

# space-separated lists of file names
SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# linking rule
$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo "Linking "$<" to create executable "$@
	@$(LINKER) $@ $(OBJECTS)
	@echo "Linking complete."

# compilation rule
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp | $(ARTIFACTDIRS)
	@echo "Compiling "$<
	@$(CC) -c $< -o $@
	@echo "Compilation complete."

# TODO make it a function
# ensures that artifcat directories exist
$(ARTIFACTDIRS):
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@test -d $(BINDIR) || mkdir $(BINDIR)

# clean all artifacts (objects and executable)
clean: 
	rm -rf $(OBJDIR) $(BINDIR)