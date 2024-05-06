CXX = g++
CONFIG = -std=c++14 -g
LIBS = -L/usr/lib/x86_64-linux-gnu -ljsoncpp -I/usr/include/jsoncpp
CONFIG += -I. -Iinclude -Iinclude/Base -Iinclude/Config -Iinclude/User -Iinclude/Work

TARGET = main
BUILD = build
BIN = bin



SOURCES = $(wildcard Sem/*.cpp) $(wildcard Base/*.cpp) $(wildcard User/*.cpp) $(wildcard Work/*.cpp) $(wildcard src/*.cpp)
OBJS = $(patsubst %.cpp,$(BUILD)/%.o,$(SOURCES))

all : $(BIN)/$(TARGET)


$(BUILD)/%.o : %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CONFIG) -c $< -o $@

$(BIN)/$(TARGET) : $(OBJS)
	@mkdir -p $(BIN)
	$(CXX) $(CONFIG) $^ -o $@ $(LIBS)

clean:
	rm -rf $(BUILD) $(BIN)

info:
	@echo "$(OBJS)"

