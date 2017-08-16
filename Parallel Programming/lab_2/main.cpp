#include "Board.h"
#include "Task.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include "constants.h"
#include <mpi.h>
#include <cmath>

#if defined(DEBUG) && !defined(D_PRINT) 
#define D_PRINT(M) std::cout << __func__ << ": " << M << std::endl;
#endif

#ifdef BENCHMARK
int BOARD_WIDTH;
int BOARD_HEIGHT;
#else
const int BOARD_WIDTH = 7;
const int BOARD_HEIGHT = 6;
#endif

static const double UNFINISHED_SEARCH = -999.;
static const int WAITING_FOR_WORKERS = -10;

static const int WORKER_NOT_WORKING_STATUS = -1;

int nr_workers, id;
int *worker_status;
int min_depth_for_master;

std::vector<Task> tasks;
double *workers_results;
bool workers_did_tasks;
int workers_results_access_index;

int doHumanTurn(Slot my_tag, Board board){
    int move;
    std::vector<int> valid_moves = board.getValidMoves();
    bool invalidMove = true;

    do{
        std::cout << "Enter a column number: ";
        std::cin >> move;

        for(unsigned i = 0; i < valid_moves.size(); i++)
            if(valid_moves[i] == move)
                invalidMove = false;

    }while(invalidMove);

    return move;
}

int getWorkerId(int i){
    if(i < id)
        return i;
    else
        return i + 1;
}

int getWorkerIndex(int wid){
    if(wid < id)
        return wid;
    else
        return wid - 1;
}

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
// #ifdef DEBUG
//     D_PRINT("turn = " << board.getSymbol(turn) << ", depth = " << depth);
//#endif

    if(board.getWinner() == AI_PLAYER){
// #ifdef DEBUG
//         D_PRINT("WIN");
// #endif
        return 1.;
    }
    else if(board.getWinner() == HUMAN_PLAYER){
// #ifdef DEBUG
//         D_PRINT("LOSE");
// #endif
        return -1.;
    }

    if(depth == 0){
// #ifdef DEBUG
//         D_PRINT("DUNNO");
// #endif
        return 0.;
    }

    if(MAX_DEPTH - depth == SPLITTING_DEPTH){
        if(workers_did_tasks){
            double ret_val = workers_results[workers_results_access_index++];

#ifdef DEBUG
            if(ret_val == -1.){
                D_PRINT("LOSING BOARD: " << std::endl << board.str());
            }
            else if(ret_val == 1.){
                D_PRINT("WINNING BOARD: " << std::endl << board.str());
            }
#endif

            return ret_val;
        }
        else{
            Task task(board, turn, depth);
            tasks.push_back(task);
            return UNFINISHED_SEARCH;
        }
    }
    else if(MAX_DEPTH - depth > SPLITTING_DEPTH){
        std::cerr << "This shouldn't happen" << std::endl;
        exit(10);
    }

    Slot next_turn = getOtherTurn(turn);
    double totVal = 0.;
    std::vector<int> valid_moves = board.getValidMoves();

    for(unsigned i = 0; i < valid_moves.size(); i++){
        board.insertCoin(next_turn, valid_moves[i]);
        double val = aiSearch(board, next_turn, depth - 1);

        if(val == 1. && next_turn == AI_PLAYER){
#ifdef DEBUG
            D_PRINT("WINNING BOARD: " << std::endl << board.str());
#endif
            return 1.;
        }
        else if(val == -1. && next_turn == HUMAN_PLAYER){
#ifdef DEBUG
            D_PRINT("LOSING BOARD: " << std::endl << board.str());
#endif
            return -1.;
        }
        
        totVal += val;

        board.undoLast();
    }

    totVal /= valid_moves.size();

// #ifdef DEBUG
//     D_PRINT("totVal = " << totVal);
// #endif

    return totVal;
}

int startAiSearch(Slot my_tag, Board board){
    std::vector<int> valid_moves = board.getValidMoves();
    std::vector<int> best_moves;

    double max_val = -99999.;
    Slot turn = AI_PLAYER;
    bool waiting_for_workers = false;

    for(unsigned i = 0; i < valid_moves.size(); i++){
        board.insertCoin(turn, valid_moves[i]);
        double val = aiSearch(board, turn, MAX_DEPTH - 1);

        if(val == UNFINISHED_SEARCH){
            waiting_for_workers = true;
        }

        if(val > max_val){
            max_val = val;
            best_moves.clear();
            best_moves.push_back(valid_moves[i]);
        }
        else if(max_val == val){
            best_moves.push_back(valid_moves[i]);
        }
        board.undoLast();
    }

    if(waiting_for_workers)
        return WAITING_FOR_WORKERS;

    int best_move; 
    if(best_moves.size() == 0)
        best_move = -1;
    else
        best_move = best_moves[rand() % best_moves.size()];
#ifdef DEBUG
    D_PRINT("best_move = " << best_move << ", value = " << max_val);
#endif

    return best_move;
}

void sendTasksToWorkersAndSaveResults(){
    unsigned task_idx = 0;
    int working_workers = 0;
    workers_results = new double[tasks.size()];

    for(; task_idx < (unsigned) nr_workers && task_idx < tasks.size(); task_idx++){
        tasks[task_idx].sendTo(getWorkerId(task_idx));
        worker_status[task_idx] = task_idx;
        working_workers++;
    }

    while(working_workers > 0){
        MPI_Status status;
        double res;

        MPI_Recv(&res, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        int worker_idx = getWorkerIndex(status.MPI_SOURCE);
        workers_results[ worker_status[worker_idx] ] = res;

        if(task_idx < tasks.size()){
            tasks[task_idx].sendTo(status.MPI_SOURCE);
            worker_status[worker_idx] = task_idx;
            task_idx++;
        }
        else{
            worker_status[worker_idx] = WORKER_NOT_WORKING_STATUS;
            working_workers--;
        }
    }
}

void cleanUpForNextTurn(){
    delete [] workers_results;
    tasks.clear();
}

int doAiTurn(Slot my_tag, Board board){
    workers_did_tasks = false;
    int move = startAiSearch(my_tag, board);
    if(move == WAITING_FOR_WORKERS){
        sendTasksToWorkersAndSaveResults();
        workers_did_tasks = true;
        workers_results_access_index = 0;
        move = startAiSearch(my_tag, board);
        cleanUpForNextTurn();
    }

    return move;
}

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);

    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &nr_workers);

    nr_workers--; // i'm not a worker!
    worker_status = new int[nr_workers]();
    for(int i = 0; i < nr_workers; i++)
        worker_status[i] = WORKER_NOT_WORKING_STATUS;

    //std::cout << "Hello from master, id = " << id << std::endl;

#ifdef BENCHMARK
    Board board("board.txt");
    BOARD_WIDTH = board.getWidth();
    BOARD_HEIGHT = board.getHeight();
#else
    Board board(BOARD_WIDTH, BOARD_HEIGHT);
#endif

    int msg_size = Task::getMsgSizeForBoard(board);
    for(int i = 0; i < nr_workers; i++){
        MPI_Send(&msg_size, 1, MPI_INT, getWorkerId(i), MSG_SIZE_TAG, MPI_COMM_WORLD);
    }

    srand(time(NULL));

#ifdef BENCHMARK
    Slot turn = Slot::PLAYER_1;
    int c = doAiTurn(turn, board);
    board.insertCoin(turn, c);
#else
    Slot turn = Slot::PLAYER_1;
    while(board.getWinner() == Slot::EMPTY){
        std::cout << board.str() << std::endl;
        
        int c;

        if(turn == AI_PLAYER){
            c = doAiTurn(turn, board);
        }

        else if(turn == HUMAN_PLAYER){
            c = doHumanTurn(turn, board);
        }

        board.insertCoin(turn, c);

        if(turn == Slot::PLAYER_1)
            turn = Slot::PLAYER_2;
        else
            turn = Slot::PLAYER_1;
    }

    std::cout << board.str() << std::endl;

    std::cout << board.winnerStr() << std::endl;
#endif

    for(int i = 0; i < nr_workers; i++){
        int dummy = 42;
        MPI_Send(&dummy, 1, MPI_INT, getWorkerId(i), TERMINATE_TAG, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}