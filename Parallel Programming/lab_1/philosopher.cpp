#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>

#define NUMBER_OF_MEALS 2
#define MAX_THINK_TIME_USECONDS 5000000
#define MAX_EAT_TIME_USECONDS 5000000
#define RESPOND_TIME_INTERVAL_USECONDS 100000
#define MAX_NUMBER_OF_PHILOSOPHERS 100

#define PHILOSOPHER_SAYS(M) _ss_.str("");\
                            _ss_ << msg_prefix << M << std::endl;\
                            _s_ = _ss_.str();\
                            _msg_ = _s_.c_str();\
                            MPI_Send(_msg_, strlen(_msg_), MPI_CHAR, nr_philosophers, PRINT, MPI_COMM_WORLD);

// Message tags
#define REQUEST 0
#define ANSWER 1
#define PRINT 2
#define PRINT_END 3

typedef struct {
    int idx;
    bool isClean, gotIt;
} philosophers_fork;

std::string msg_prefix("P: ");
int rank, nr_philosophers;
philosophers_fork fork_left, fork_right;
bool got_request_left = false, got_request_right = false;
int left_idx, right_idx;
bool i_want_to_eat = false;

// Global printing variables
std::stringstream _ss_;
std::string _s_;
const char *_msg_;

void wake_up(int rank){
    // Set random seed which is a function of this philosophers rank
    //  so each philosopher has different seed
    srand((unsigned) time(NULL) * rank);

    // Set this philosophers message prefix according to his rank
    std::stringstream ss;

    for(int i = 0; i < rank; i++)
        ss << " ";
    ss << "P" << rank << ": ";

    msg_prefix = ss.str();

    // Set initial fork locations and status
    fork_left.idx = (rank - 1) < 0 ? nr_philosophers - 1 : rank - 1;
    fork_right.idx = rank;
    fork_left.isClean = fork_right.isClean = false;

    left_idx = (rank - 1) < 0 ? nr_philosophers - 1 : rank - 1;
    right_idx = (rank + 1) % nr_philosophers;

    if(rank == 0){
        fork_left.gotIt = fork_right.gotIt = true;
    }
    else if(rank == nr_philosophers - 1){
        fork_left.gotIt = fork_right.gotIt = false;
    }
    else{
        fork_left.gotIt = false;
        fork_right.gotIt = true;
    }
}

void cleanUp(){
    // Tell the printing process you're done
    char dummy[1] = {0};
    MPI_Send(dummy, 1, MPI_CHAR, nr_philosophers, PRINT_END, MPI_COMM_WORLD);
    MPI_Finalize();
    exit(0);
}

void processRequest(int fork_idx){
    if(fork_idx != fork_right.idx && fork_idx != fork_left.idx){
        PHILOSOPHER_SAYS("I can't reach fork " << fork_idx << "!");
        return;
    }

    philosophers_fork *req_fork;
    bool leftForkRequested;
    if(fork_idx == fork_right.idx){
        req_fork = &fork_right;
        leftForkRequested = false;
    }
    else{
        req_fork = &fork_left;
        leftForkRequested = true;
    }

    if(!i_want_to_eat || (i_want_to_eat && !req_fork->isClean)){
        req_fork->isClean = true;
        req_fork->gotIt = false;

        int dest = leftForkRequested ? left_idx : right_idx;

        PHILOSOPHER_SAYS("Sending fork " << req_fork->idx << " to philosopher " << dest << "...");

        MPI_Request request;
        MPI_Isend(&req_fork->idx, 1, MPI_INT, dest, ANSWER, MPI_COMM_WORLD, &request);
        MPI_Request_free(&request);

        // Means that i want to eat but the fork is dirty so i have to send
        // the fork as requested, but i also need to tell the other guy to give
        // back the fork ASAP
        if(i_want_to_eat){
            MPI_Isend(&req_fork->idx, 1, MPI_INT, dest, REQUEST, MPI_COMM_WORLD, &request);
            MPI_Request_free(&request);
        }
    }
    else{
        if(leftForkRequested)
            got_request_left = true;
        else
            got_request_right = true;
    }
}

void answerToCachedRequests(){
    if(got_request_left)
        processRequest(fork_left.idx);
    if(got_request_right)
        processRequest(fork_right.idx);
}

void receiveFork(int fork_idx){
    if(fork_idx != fork_right.idx && fork_idx != fork_left.idx){
        PHILOSOPHER_SAYS("I can't reach fork " << fork_idx << "!");
        return;
    }

    philosophers_fork *recv_fork;
    if(fork_idx == fork_right.idx)
        recv_fork = &fork_right;
    else
        recv_fork = &fork_left;

    recv_fork->isClean = true;
    recv_fork->gotIt = true;

    PHILOSOPHER_SAYS("Received fork " << fork_idx << "!");
}

void checkRequests(){
    int flag = false;
    do{
        MPI_Iprobe(MPI_ANY_SOURCE, REQUEST, MPI_COMM_WORLD, &flag, MPI_STATUS_IGNORE);
        if(flag){
            int fork_idx;
            MPI_Recv(&fork_idx, 1, MPI_INT, MPI_ANY_SOURCE, REQUEST, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            processRequest(fork_idx);
        }
    }while(flag);
}

// Q: Does a philosopher always give away only his dirty forks? even when thinking?
void think(){
    int thinking_time = rand() % MAX_THINK_TIME_USECONDS;
    PHILOSOPHER_SAYS("Thinking...");
    
    checkRequests();
    for(int time_passed = 0;
        time_passed < thinking_time;
        time_passed += RESPOND_TIME_INTERVAL_USECONDS){
        
            usleep(RESPOND_TIME_INTERVAL_USECONDS);
            checkRequests();
    }
}

// Q: Does a philosopher give away his dirty fork when waiting for the other one?
void getForks(){
    MPI_Request request;
    i_want_to_eat = true;
    PHILOSOPHER_SAYS("I want forks!");
    if(!fork_left.gotIt){
        MPI_Isend(&fork_left.idx, 1, MPI_INT, left_idx, REQUEST, MPI_COMM_WORLD, &request);
        MPI_Request_free(&request);
    }
    if(!fork_right.gotIt){
        MPI_Isend(&fork_right.idx, 1, MPI_INT, right_idx, REQUEST, MPI_COMM_WORLD, &request);
        MPI_Request_free(&request);
    }
    while(!fork_left.gotIt || !fork_right.gotIt){
        MPI_Status status;
        int fork_idx;

        MPI_Recv(&fork_idx, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        switch(status.MPI_TAG){
            case REQUEST:
                processRequest(fork_idx);
                break;
            case ANSWER:
                receiveFork(fork_idx);
                break;
            default:
                PHILOSOPHER_SAYS("Philosopher " << status.MPI_SOURCE << " is drunk!");
        }
    }
    PHILOSOPHER_SAYS("Got both forks!");
}

void giveAwayMyForks(){
    MPI_Request request;

    if(fork_left.gotIt){
        PHILOSOPHER_SAYS("Sending fork " << fork_left.idx << " to philosopher " << left_idx << "...");
        fork_left.isClean = true;
        fork_left.gotIt = false;
        MPI_Isend(&fork_left.idx, 1, MPI_INT, left_idx, ANSWER, MPI_COMM_WORLD, &request);
        MPI_Request_free(&request);
    }
    if(fork_right.gotIt){
        PHILOSOPHER_SAYS("Sending fork " << fork_right.idx << " to philosopher " << right_idx << "...");
        fork_right.isClean = true;
        fork_right.gotIt = false;
        MPI_Isend(&fork_right.idx, 1, MPI_INT, right_idx, ANSWER, MPI_COMM_WORLD, &request);
        MPI_Request_free(&request);
    }
}

void eat(){
    PHILOSOPHER_SAYS("Eating!");
    usleep(rand() % MAX_EAT_TIME_USECONDS);
    i_want_to_eat = false;
    PHILOSOPHER_SAYS("Done eating!");
    answerToCachedRequests();
}

int main (int argc, char* argv[]) {
    MPI_Init (&argc, &argv);

    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &nr_philosophers);

    // The last process is the printer!
    nr_philosophers--;

    if(nr_philosophers > MAX_NUMBER_OF_PHILOSOPHERS){
        if(rank == 0)
            PHILOSOPHER_SAYS("Too many philosophers!");
        cleanUp();
    }

    wake_up(rank);
    PHILOSOPHER_SAYS("Good morning!");
    for(int i = 0; i < NUMBER_OF_MEALS; i++){
        think();
        getForks();
        eat();
    }
    giveAwayMyForks();
    PHILOSOPHER_SAYS("Good night!");

    cleanUp();
    return 0;
}