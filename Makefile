#######################
# Compiler definition #
#######################

CC = clang
CXX = clang++

###########################
# Build config definition #
###########################

ifeq ($(CONFIG),)
	CONFIG := debug
endif

#######################
# Project definitions #
#######################

TARGET := vikey

GENERIC_BUILD_DIR := build
BUILD_DIR := $(GENERIC_BUILD_DIR)/$(TARGET)/$(CONFIG)

HEADER_DIR := src
SOURCE_DIR := src
MODULES :=
MODULES_HEADER_DIR := $(addprefix $(HEADER_DIR)/, $(MODULES))
SOURCE_FILES := $(shell find $(SOURCE_DIR) -name *.cpp)
OBJECT_FILES := $(addprefix $(BUILD_DIR)/, $(SOURCE_FILES:%.cpp=%.o))

################################
# Compilation flags definition #
################################

ifeq ($(CONFIG), debug)
	CXXFLAGS += -g
endif

CXXFLAGS += -std=c++11 -Wall -O2
CXXFLAGS += -I$(HEADER_DIR) $(addprefix -I, $(MODULES_HEADER_DIR))
CXXFLAGS += -D__MACOSX_CORE__

###########################
# Linker flags definition #
###########################

LDFLAGS += -lm
LDFLAGS += -framework CoreMIDI -framework CoreAudio -framework CoreFoundation

#####################
# Compilation rules #
#####################

.PHONY: build_info clean distclean help

all: build_info $(TARGET)

build_info:
	@echo '# Build Information'
	@echo '#   Target       : $(TARGET)'
	@echo '#   Config       : $(CONFIG)'
	@echo '#   C++ compiler : $(CXX)'
	@echo '#   C++ Flags    : $(CXXFLAGS)'
	@echo '#   Linker Flags : $(LDFLAGS)'

$(TARGET): $(OBJECT_FILES)
	@echo 'linking $(notdir $@)'
	$(CXX) $(LDFLAGS) $(OBJECT_FILES) -o $@

$(BUILD_DIR)/%.o: %.cpp
	@echo 'compiling $(notdir $<)'
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo 'cleaning $(TARGET)'
	@rm -rf $(BUILD_DIR) $(TARGET)

distclean:
	@echo 'cleaning everything'
	@rm -rf $(GENERIC_BUILD_DIR) $(TARGET)

help:
	@echo '# Available options:'
	@echo '#   CONFIG=[ debug | release ]'

