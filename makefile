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
	./main.exe test1.txt test2.txt

plot_sim_test:
	python visualise.py test1.txt
	python visualise.py test2.txt

problem7: comp_sim run_sim_test

run_real:
	./main.exe slit1.txt slit2.txt slit3.txt

plot:
	python visualise.py slit1.txt
	python visualise.py slit2.txt
	python visualise.py slit3.txt

run: comp_sim run_real plot

hello_world:
	echo "Hello World"
