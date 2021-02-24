bin/instructions.o: headers/instructions.hpp
	g++ -c -I . -o bin/instructions.o src/instructions.cpp
	
clean:
	rm bin/*