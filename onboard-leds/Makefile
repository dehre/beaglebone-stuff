CC = arm-linux-gnueabihf-g++
CFLAGS = -g -Wall -Wextra -Werror -O0 -DDEBUG
CFLAGS += -std=c++17

OBJS = make-leds.o
BIN = make-leds

all: $(BIN)

release: clean
release: CFLAGS = -Wall -Wextra -Werror -O2
release: CFLAGS += -std=c++17
release: $(BIN)

makeLEDs: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS) $(BIN)
