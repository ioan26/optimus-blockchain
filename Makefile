CC = clang++

CFLAGS  = -g -Wall
INCLUDE = -I/opt/ssl/include/
LIBS = -L/opt/ssl/lib/
libs = -lcrypto

TARGET = blockchain

.PHONY: clean
$(TARGET): src/$(TARGET).cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o $(TARGET) src/$(TARGET).cpp $(libs)

clean:
	rm $(TARGET)