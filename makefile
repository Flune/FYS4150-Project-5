comp_test:
	g++ Source/*.cpp test.cpp -o test.exe -larmadillo -I Include/

run_test:
	./test.exe

test: comp_test run_test
