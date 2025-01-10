Q = @

# Compiler flags
CPPSTD 				= -std=c++17
CXXFLAGS 			= -g -Wall -Wextra $(CPPSTD) $(CFLAGS_PLATFORM)
LDFLAGS	 			= $(LDFLAGS_PLATFORM) -L. -Lsrc/six502 -lsix502 -L/opt/local/lib -lSDL2 -lSDL2_image

# Architecture related stuff
TARGET_SYSTEM = ""

TARGET_SYSTEM := $(shell uname -s)
ifeq ($(OS), Windows_NT)
	TARGET_SYSTEM 	= "WIN_32"
	CXXFLAGS 		+= -D__WIN_32__
else
	ifeq ($(TARGET_SYSTEM), Darwin)
			OSX_SDL_FRAMEWORKS = -framework SDL2	\
							-framework SDL2_ttf		\
							-framework SDL2_image
			OSX_F = -F/Library/Frameworks
			CXXFLAGS += -D__OSX__
	endif
	ifeq ($(TARGET_SYSTEM), Linux)
			CXXFLAGS += -D__LINUX__
	endif
endif

# Six502 submodule directory
SIX502_DIR	= src/six502

# CojoNES related variables
COJONES_TARGET = CojoNES
COJONES_MAIN_CPP = main.cpp
COJONES_MAIN_OBJ = main.o

SRCDIR			:= src
SRCOBJDIR		:= $(SRCDIR)/obj

SRCDEVDIR		:= $(SRCDIR)/devices
SRCDEVOBJDIR	:= $(SRCDEVDIR)/obj

SRCEMUDIR		:= $(SRCDIR)/emulator
SRCEMUOBJDIR	:= $(SRCEMUDIR)/obj

SRCMAPDIR		:= $(SRCDEVDIR)/mappers
SRCMAPOBJDIR	:= $(SRCMAPDIR)/obj

SRCUTILSDIR		:= $(SRCDIR)/utils
SRCUTILSOBJDIR	:= $(SRCUTILSDIR)/obj

SOURCES			:= $(wildcard $(SRCDIR)/*.cpp)
OBJECTS			:= $(SOURCES:$(SRCDIR)/%.cpp=$(SRCOBJDIR)/%.o)

DEV_SOURCES		:= $(wildcard $(SRCDEVDIR)/*.cpp)
DEV_OBJECTS		:= $(DEV_SOURCES:$(SRCDEVDIR)/%.cpp=$(SRCDEVOBJDIR)/%.o)

EMU_SOURCES		:= $(wildcard $(SRCEMUDIR)/*.cpp)
EMU_OBJECTS		:= $(EMU_SOURCES:$(SRCEMUDIR)/%.cpp=$(SRCEMUOBJDIR)/%.o)

MAP_SOURCES		:= $(wildcard $(SRCMAPDIR)/*.cpp)
MAP_OBJECTS		:= $(MAP_SOURCES:$(SRCMAPDIR)/%.cpp=$(SRCMAPOBJDIR)/%.o)

UTILS_SOURCES	:= $(wildcard $(SRCUTILSDIR)/*.cpp)
UTILS_OBJECTS	:= $(UTILS_SOURCES:$(SRCUTILSDIR)/%.cpp=$(SRCUTILSOBJDIR)/%.o)

ALLOBJ			:= $(OBJECTS) $(DEV_OBJECTS) $(EMU_OBJECTS) $(MAP_OBJECTS) $(UTILS_OBJECTS)

INCLUDES		:= -I. -I$(SRCDIR) -I$(SRCDEVDIR) -I$(SRCEMUDIR) -I$(SRCMAPDIR) -I$(SRCUTILSDIR) -I$(SIX502_DIR) -I$(SIX502_DIR)/src

# Colored output to console
ANSI_RESET	= \e[0m
ANSI_BOLD	= \e[1m
ANSI_ULINE	= \e[4m
ANSI_RED	= \e[31m
ANSI_GREEN	= \e[32m

# ---------------- Main make targets ----------------

all: cojones

cojones: $(COJONES_MAIN_OBJ) 
$(COJONES_MAIN_OBJ): $(ALLOBJ)
	$(Q)$(CXX) $(INCLUDES) $(CXXFLAGS) $(OSX_F) -c $(COJONES_MAIN_CPP) -o $(COJONES_MAIN_OBJ)
	$(Q)$(CXX) $(INCLUDES) $(COJONES_MAIN_OBJ) $(ALLOBJ) -o $(COJONES_TARGET) $(LDFLAGS)

# Main sources
$(OBJECTS): $(SRCOBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(Q)mkdir -p $(SRCOBJDIR)
	$(Q)$(CXX) $(INCLUDES) $(CXXFLAGS) $(OSX_F) -c $< -o $@
	$(Q)printf "Compiled $<\n"

$(DEV_OBJECTS): $(SRCDEVOBJDIR)/%.o : $(SRCDEVDIR)/%.cpp
	$(Q)mkdir -p $(SRCDEVOBJDIR)
	$(Q)$(CXX) $(INCLUDES) $(CXXFLAGS) $(OSX_F) -c $< -o $@
	$(Q)printf "Compiled $<\n"

$(EMU_OBJECTS): $(SRCEMUOBJDIR)/%.o : $(SRCEMUDIR)/%.cpp
	$(Q)mkdir -p $(SRCEMUOBJDIR)
	$(Q)$(CXX) $(INCLUDES) $(CXXFLAGS) $(OSX_F) -c $< -o $@
	$(Q)printf "Compiled $<\n"

$(MAP_OBJECTS): $(SRCMAPOBJDIR)/%.o : $(SRCMAPDIR)/%.cpp
	$(Q)mkdir -p $(SRCMAPOBJDIR)
	$(Q)$(CXX) $(INCLUDES) $(CXXFLAGS) $(OSX_F) -c $< -o $@
	$(Q)printf "Compiled $<\n"

$(UTILS_OBJECTS): $(SRCUTILSOBJDIR)/%.o : $(SRCUTILSDIR)/%.cpp
	$(Q)mkdir -p $(SRCUTILSOBJDIR)
	$(Q)$(CXX) $(INCLUDES) $(CXXFLAGS) $(OSX_F) -c $< -o $@
	$(Q)printf "Compiled $<\n"

.PHONY: clean
clean:
	$(Q)printf "\nClearing $(ANSI_BOLD)Cojones$(ANSI_RESET)...\n\n"
	$(Q)rm -f $(COJONES_MAIN_OBJ)
	$(Q)rm -rf $(SRCOBJDIR)
	$(Q)rm -rf $(SRCDEVOBJDIR)
	$(Q)rm -rf $(SRCEMUOBJDIR)
	$(Q)rm -rf $(COJONES_TARGET)

# Aux info targets
.PHONY: info
info:
	$(Q)printf "\nBuilding $(ANSI_BOLD)Cojones$(ANSI_RESET)...\n\n"

