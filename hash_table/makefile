# FlieName : makeflie
# Created by Wei Zhou on 2019/10/7
# Copyright © 2017 Muyiro. All rights reserved.

# Executable file name.
TARGET = hash_table_example
# Source directory address.
DIR_SRC = ./src
# Object directory address.
DIR_OBJ = ./obj

# Compile file type: cpp / c ...
EXTENSION = c
# The compiler: g++ / gcc ...
# CC = g++ -std=c++11

# *** Don't modify!!! ***

# Gets the source file address
SRC = $(wildcard $(DIR_SRC)/*.$(EXTENSION))
# Gets the object file address
OBJ = $(patsubst %.$(EXTENSION),$(DIR_OBJ)/%.o,$(notdir $(SRC)))

# Generate the executable.
$(TARGET): clean MKDIR_OBJ $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
	$(CC) $(OBJ) -o $(DIR_OBJ)/$(TARGET).out

# Creat a object directory.
MKDIR_OBJ:
	mkdir -p $(DIR_OBJ)

# Compile all source files.
$(DIR_OBJ)/%.o: $(DIR_SRC)/%.$(EXTENSION)
	$(CC) -c $< -o $@

# View the source file that will compile
.PHONY: source
source:
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(CC) $(OBJ) -o $(TARGET)

# Clean target file, object files and its directory.
.PHONY: clean
clean:
	rm -rf $(DIR_OBJ) $(TARGET)

# Clean object files and its directory.
.PHONY: clean_obj
clean_obj:
	rm -rf $$(DIR_OBJ)
