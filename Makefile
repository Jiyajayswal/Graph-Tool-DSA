# CC = gcc
# CFLAGS = -Wall -Wextra -g

# # Default target
# all: a4

# # Build the final executable
# a4: main.o graph_functions.o
# 	$(CC) $(CFLAGS) -o a4 main.o graph_functions.o

# # Compile main.c into main.o
# main.o: main.c graph.h
# 	$(CC) $(CFLAGS) -c main.c

# # Compile graph_functions.c into graph_functions.o
# graph_functions.o: graph_functions.c graph.h
# 	$(CC) $(CFLAGS) -c graph_functions.c

# # Clean up object files and executable
# clean:
# 	rm -f *.o a4

# # Run the program
# run: a4
# 	./a4

# # Declare phony targets to avoid confusion with filenames
# .PHONY: all clean run


CC = gcc
CFLAGS = -Wall -Wextra -g

all: a4

a4: main.o graph_functions.o
	$(CC) $(CFLAGS) -o a4 main.o graph_functions.o

main.o: main.c graph.h
	$(CC) $(CFLAGS) -c main.c

graph_functions.o: graph_functions.c graph.h
	$(CC) $(CFLAGS) -c graph_functions.c

clean:
	rm -f *.o a4
