#pragma once

#include "Board.h"

class Task{
    Board board;
    Slot turn;
    int depth;

public:
    Task(Board b, Slot t, int d);
    Task(int *message);

    void sendTo(int dest) const;

    Board getBoard() const;
    Slot getTurn() const;
    int getDepth() const;

    static int getMsgSizeForBoard(const Board &b);
};