CXX = g++ -g 

run: run_catalog.o catalog.o
	$(CXX) -o run -Werror=vla run_catalog.o catalog.o

run_catalog.o: run_catalog.cpp
	$(CXX) run_catalog.cpp -c 

catalog.o: catalog.cpp
	$(CXX) catalog.cpp -c
