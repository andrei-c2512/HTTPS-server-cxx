#variables
CXX = g++
CXXFLAGS = -std=c++20 -lstdc++ -static-libstdc++ -Wall -Wextra -O2 
DEPFLAGS = -MMD
SRC_DIR = .
INC_DIRS = 
BUILD_DIR = build
BINARY_NAME= WebResourceGenerator
SRC = $(foreach D , $(SRC_DIR) , $(wildcard $(D)/*.cpp))

#for every cpp file , create an object
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

#the executable
TARGET = $(BUILD_DIR)/$(BINARY_NAME).exe

#default
all : $(TARGET)

#linking
$(TARGET) : $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) 


$(BUILD_DIR) :
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@
	
status:
	@git status
	@git diff --stat

src_files:
	echo "$(SRC)"
obj_files:
	echo "$(OBJ)"

#cleaning lol
clean:
	rm -f $(TARGET) $(OBJ)
