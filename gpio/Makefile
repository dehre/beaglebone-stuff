CC = g++
CFLAGS = -g -Wall -Wextra -Werror -O0 -DDEBUG
CFLAGS += -std=c++17

OBJS = GPIO.o main.o
BIN = gpio 

all: $(BIN)

release: clean
release: CFLAGS = -Wall -Wextra -Werror -O2
release: CFLAGS += -std=c++17
release: $(BIN)

gpio: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS) $(BIN)
