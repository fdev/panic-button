all: button.o main.o
	gcc -o button_tool main.o button.o -lusb-1.0

clean:
	rm *.o
