#include "Board.h"
#include "Task.h"
#include <mpi.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include "constants.h"

int id;

Slot getOtherTurn(Slot current){
    if(current == Slot::PLAYER_1)
        return Slot::PLAYER_2;
    else if(current == Slot::PLAYER_2)
        return Slot::PLAYER_1;
    else{
        std::cerr << "Something went terriby wrong in turn switching" << std::endl;
        exit(8);
    }
}

double aiSearch(Board board, Slot turn, int depth){
    if(board.getWinner() == AI_PLAYER){
        return 1.;
    }
    else if(board.getWinner() == HUMAN_PLAYER){
        return -1.;
    }

    if(depth == 0){
        return 0.;
    }

    Slot next_turn = getOtherTurn(turn);
    double totVal = 0.;
    std::vector<int> valid_moves = board.getValidMoves();

    for(unsigned i = 0; i < valid_moves.size(); i++){
        board.insertCoin(next_turn, valid_moves[i]);
        double val = aiSearch(board, next_turn, depth - 1);

        if(val == 1. && next_turn == AI_PLAYER){
            return 1.;
        }
        else if(val == -1. && next_turn == HUMAN_PLAYER){
            return -1.;
        }
        
        totVal += val;

        board.undoLast();
    }

    totVal /= valid_moves.size();

    return totVal;
}

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    //std::cout << "Hello from worker, id = " << id << std::endl;

    int msg_size;
    MPI_Recv(&msg_size, 1, MPI_INT, MPI_ANY_SOURCE, MSG_SIZE_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    int *msg = new int[msg_size];
    while(true){
        MPI_Status status;

        MPI_Recv(msg, msg_size, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if(status.MPI_TAG == TASK_TAG){
            Task task(msg);
            double val = aiSearch(task.getBoard(), task.getTurn(), task.getDepth());
            MPI_Send(&val, 1, MPI_DOUBLE, status.MPI_SOURCE, TASK_TAG, MPI_COMM_WORLD);
        }
        else if(status.MPI_TAG == TERMINATE_TAG){
            break;
        }
        else{
            std::cerr << "Unknown tag, ignoring message" << std::endl;
        }
    }

    delete [] msg;

    MPI_Finalize();

    return 0; 
}