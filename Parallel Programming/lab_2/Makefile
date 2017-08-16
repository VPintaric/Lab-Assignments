OPTS=-std=c++11 -Wall
MPI_CHILL=--mca mpi_yield_when_idle 1

game:
	mpic++ $(OPTS) main.cpp Board.cpp Task.cpp -o master
	mpic++ $(OPTS) worker.cpp Board.cpp Task.cpp -o worker

debug:
	mpic++ $(OPTS) -DDEBUG main.cpp Board.cpp Task.cpp -o master
	mpic++ $(OPTS) -DDEBUG worker.cpp Board.cpp Task.cpp -o worker

benchmark:
	mpic++ $(OPTS) -DBENCHMARK main.cpp Board.cpp Task.cpp -o master
	mpic++ $(OPTS) -DBENCHMARK worker.cpp Board.cpp Task.cpp -o worker

run_game:
	mpirun -np 1 $(MPI_CHILL) master : -np 5 $(MPI_CHILL) worker

run_debug:
	mpirun -np 1 $(MPI_CHILL) master : -np 4 $(MPI_CHILL) worker

run_benchmark:
	for N in 7 6 5 4 3 2 1; do \
		echo "Benchmarking for number of workers $$N" ; \
		time --format=%e mpirun -np 1 $(MPI_CHILL) master : -np $$N $(MPI_CHILL) worker ; \
	done

clean:
	rm master worker