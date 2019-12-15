IF NOT EXIST bin mkdir bin
gcc -c "main.c" -o "bin/main.o" 
gcc -c "library.c" -o "bin/library.o"
gcc -o "bin/main" "bin/main.o" "bin/library.o" 
