CC=g++
CFLAGS=-g -Wall -std=c++11 -I$(INC_DIR)
LDFLAGS=
LDLIBS=

INC_DIR=inc
SRC_DIR=src
OBJ_DIR=obj

SOURCES=thread main
OBJS=$(patsubst %,$(OBJ_DIR)/%.o,$(SOURCES))
DEPS=$(patsubst %,$(OBJ_DIR)/%.d,$(SOURCES))

TARGET=test.out
STATIC_LIB=libthread.a

.PHONY: all
all: $(TARGET)
lib: $(STATIC_LIB)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) -o $@ $< -c $(CFLAGS) $(LDFLAGS) $(LDLIBS) -MD
 
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET) $(DEPS)
	rmdir $(OBJ_DIR)