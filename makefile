comp_test:
	g++ Source/*.cpp test.cpp -o test.exe -larmadillo -I Include/

run_test:
	./test.exe

count_test:
	./test.exe | uniq -c

test: comp_test run_test

test_count: comp_test count_test
