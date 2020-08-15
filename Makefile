# Makefile for Writing Make Files Example

# *****************************************************

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -g -O3 -std=c++11 -J 4

# Directory containing the program
SOURCE_DIR = source
# Directory containing the executables            
BIN_DIR = bin
# Directory containing the libraries
LIB_DIR = lib

# Add the include directories
INC_DIR = include
INCS = $(foreach d, $(INC_DIR), -I$d)

# Add the libs
LIBS = -pedantic # -ansi

# List of the directories that should be created
DIRS = $(BIN_DIR) $(OBJ_DIR)

# Add the obj
OBJ_DIR = build
_OBJ = stencode.o stdecode.o lodepng.o pngtools.o encoder.o decoder.o
OBJ = $(foreach d, $(_OBJ), $(OBJ_DIR)/$d)

# Add the encoder obj
_ENC_OBJ = stencode.o lodepng.o pngtools.o encoder.o
ENC_OBJ = $(foreach d, $(_ENC_OBJ), $(OBJ_DIR)/$d)

# Add the decoder obj
_DEC_OBJ = stdecode.o lodepng.o pngtools.o decoder.o
DEC_OBJ = $(foreach d, $(_DEC_OBJ), $(OBJ_DIR)/$d)

# Add the DEPS
_DEPS = cxxopts.hpp lodepng.h pngtools.hpp encoder.hpp decoder.hpp
DEPS = $(foreach d, $(_DEPS), $(INC_DIR)/$d)


# ****************************************************

all: pre-build encoder-build decoder-build post-build

pre-build:
	@echo "START"
	@mkdir -p $(DIRS)
	@echo "Creating required directories to build"

encoder-build: $(BIN_DIR)/stencode 

decoder-build: $(BIN_DIR)/stdecode

post-build: encoder-build decoder-build
	@echo "DONE"

$(BIN_DIR)/stencode: $(ENC_OBJ)
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) $? -o $@

$(BIN_DIR)/stdecode: $(DEC_OBJ)
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) $? -o $@
	
$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(DEPS)
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) $(INCS) $(LIBS) -c $< -o $@ 

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.cpp $(DEPS)
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) $(INCS) $(LIBS) -c $< -o $@

clean:
	@echo "Removing $(OBJ_DIR)"
	@rm -r $(OBJ_DIR)

.PHONY: all
