#include "Task.h"
#include "Board.h"
#include "constants.h"
#include <mpi.h>

Task::Task(Board b, Slot t, int d) : board(b){
    turn = t;
    depth = d;
}

Task::Task(int *message) : board(message + 2){
    int idx = 0;

    turn = Board::intToSlot(message[idx++]);
    depth = message[idx++];
}

void Task::sendTo(int dest) const{
    // Sent message is, [ turn, depth, packed board state ]
    int message_size = getMsgSizeForBoard(board); 
    int* message = new int[message_size];
    int idx = 0;

    message[idx++] = Board::slotToInt(turn);
    message[idx++] = depth;
    board.pack(&message[idx++]);

    MPI_Send(message, message_size, MPI_INT, dest, TASK_TAG, MPI_COMM_WORLD);

    delete [] message;
}

int Task::getMsgSizeForBoard(const Board &b){
    return b.getPackSize() + 2;
}

Board Task::getBoard() const{
    return board;
}

Slot Task::getTurn() const{
    return turn;
}

int Task::getDepth() const{
    return depth;
}