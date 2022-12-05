comp_test:
	g++ Source/*.cpp test.cpp -o test.exe -larmadillo -I Include/

run_test:
	./test.exe

count_test:
	./test.exe | uniq -c

test: comp_test run_test

test_count: comp_test count_test

comp_sim:
	g++ Source/*.cpp simulate.cpp -o main.exe -fopenmp -larmadillo -I Include/

run_sim_test:
	# ./main.exe test1.txt
	./main.exe test1.txt test2.txt

problem7: comp_sim run_sim_test

hello_world:
	echo "Hello World"
