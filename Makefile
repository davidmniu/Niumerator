CXX=g++
CPPFLAGS=-g -std=c++17 -Wall

main:
	rm bin/main; clear
	$(CXX) $(CPPFLAGS) -c lib/helper.cpp -o build/helper.o
	$(CXX) $(CPPFLAGS) -c lib/niutron.cpp -o build/niutron.o
	$(CXX) $(CPPFLAGS) -c src/ode_ivp_methods.cpp -o build/ode_ivp_methods.o
	$(CXX) $(CPPFLAGS) -c tests/main.cpp -o build/main.o
	$(CXX) $(CPPFLAGS) build/helper.o build/niutron.o build/ode_ivp_methods.o build/main.o -o bin/main

niucleus:
	cp ~/school/Niucleus/src/* lib/

clear:
	rm build/* bin/*
