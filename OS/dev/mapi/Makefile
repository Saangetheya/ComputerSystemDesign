init:
	@mkdir build

compilec: $(fname)
	@gcc -Wall -o main.out $(fname) -I .
	
runc: compile
	@ ./main.out

compilep: $(fname)
	@g++ -std=c++20 -o main.out $(fname) -static -I .
	