CXX=g++
CPPFLAGS=-g -std=c++17 -Wall

main:
	rm bin/main; clear
	$(CXX) $(CPPFLAGS) -c lib/helper.cpp -o build/helper.o
	$(CXX) $(CPPFLAGS) -c lib/eqparser.cpp -o build/eqparser.o
	$(CXX) $(CPPFLAGS) -c src/ode_ivp_methods.cpp -o build/ode_ivp_methods.o
	$(CXX) $(CPPFLAGS) -c tests/main.cpp -o build/main.o
	$(CXX) $(CPPFLAGS) build/helper.o build/eqparser.o build/ode_ivp_methods.o build/main.o -o bin/main

eqparser:
	rm lib/*
	cp ~/projects/eqparse/src/* lib/

clear:
	rm build/* bin/*
