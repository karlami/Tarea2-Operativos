all: build run 

clean:
	rm -rf ./*.bin
	
build:
	clear
	gcc MiPrograma.c -o MiPrograma
	
run:
	./MiPrograma ./hello -a -0
	./MiPrograma ./hello -a -1
	./MiPrograma ./hello -a -2
	./MiPrograma ./hello -a
	./MiPrograma ./hello
	./MiPrograma ./hello -A -0
