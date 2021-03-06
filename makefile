all: bin/ram_sim
	
bin/ram_sim: src/main.cpp bin/ram.o bin/ram_debug.o bin/ram_builder.o bin/instructions.o
	g++ -I . -o bin/ram_sim src/main.cpp bin/ram_builder.o bin/ram_debug.o bin/ram.o bin/instructions.o
	
bin/ram_builder.o: headers/ram.hpp src/ram_builder.cpp headers/ram_builder.hpp headers/ram_debug.hpp
	g++ -c -I . -o bin/ram_builder.o src/ram_builder.cpp

bin/ram_debug.o: bin/ram.o headers/ram_debug.hpp src/ram_debug.cpp
	g++ -c -I . -o bin/ram_debug.o src/ram_debug.cpp 
	
bin/ram.o: headers/ram.hpp headers/instructions.hpp headers/memory_state.hpp headers/dynamic_vec.hpp src/ram.cpp 
	g++ -c -I . -o bin/ram.o src/ram.cpp 
	
bin/instructions.o: headers/instructions.hpp headers/memory_state.hpp src/instructions.cpp
	g++ -c -I . -o bin/instructions.o src/instructions.cpp

clean:
	rm bin/*