all: bin/ bin/main.o bin/library.o
	gcc -o "bin/main" "bin/main.o" "bin/library.o" 
bin/:
	[ -d bin ] || mkdir -p bin
bin/main.o: main.c
	gcc -c "main.c" -o "bin/main.o"
bin/library.o: library.c
	gcc -c "library.c" -o "bin/library.o" 
