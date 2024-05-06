CXX = g++
CONFIG = -std=c++11 -Wall -g

CONFIG += -Iinclude -Iinclude/Base -Iinclude/Config -Iinclude/User -Iinclude/Work -Iinclude/src


BIN = bin
BUILD = build
TARGET = Server

SOURCES = $(wildcard src/*.cpp) $(wildcard Base/*.cpp) $(wildcard User/*.cpp) $(wildcard Work/*.cpp)
OBJS = $(patsubst %.cpp,$(BUILD)/%.o,$(SOURCES))

all : $(BIN)/$(TARGET)

$(BUILD)/%.o : %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CONFIG) -c $< -o $@
$(BIN)/$(TARGET) : $(OBJS)
	@mkdir -p $(BIN)
	$(CXX) $(CONFIG) $^ -o $@ 

clean:
	rm -rf $(BIN) $(BUILD)
info:
	@echo "$(OBJS)"
	@echo "$(SOURCES)"
