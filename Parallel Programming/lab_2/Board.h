#pragma once

#include <string>
#include <vector>
#include <utility>

enum class Slot {
    EMPTY,
    PLAYER_1,
    PLAYER_2
};

class Board {

    Slot *board;
    int *col_height;
    int width, height;
    Slot winner;

    int last_move;
    Slot last_winner;
    bool can_undo;

    std::vector< std::pair<int, int> > winning_slots;

    Slot& slot(int r, int c);
    static Slot getSlotFromSymbol(char sym);
    void assertBoundary(int r, int c) const;
    bool slotIsWinningSlot(int r, int c) const;

    void checkWinnerIncludingTile(int r, int c);
    void checkWinner();


public:

    static const int STR_SPACING_WIDTH = 3;
    static const int STR_SPACING_HEIGHT = 1;
    static const char STR_UPPER_AND_LOWER_BOUNDARY_SYMBOL = '=';
    static const char STR_RIGHT_AND_LEFT_BOUNDARY_SYMBOL = '|';
    static const char SLOT_GARBAGE_SYMBOL = '~';
    static const char SLOT_EMPTY_SYMBOL = '.';
    static const char SLOT_PLAYER_1_SYMBOL = 'X';
    static const char SLOT_PLAYER_2_SYMBOL = 'O';
    static const int IN_ROW_TO_WIN = 4;

    Board(int w, int h);
    Board(const Board &obj);
    Board(std::string file_name);
    Board(int *pack);
    ~Board();

    Slot operator()(int r, int c) const;
    int getWidth() const;
    int getHeight() const;
    int getColHeight(int c) const;
    Slot getWinner() const;
    Slot getLastWinner() const;
    int getLastMove() const;
    bool canUndo() const;

    std::vector<int> getValidMoves();
    void insertCoin(Slot tag, int c);
    void undoLast();

    static char getSymbol(Slot s);
    static int slotToInt(Slot s);
    static Slot intToSlot(int x);

    int getPackSize() const;
    void pack(int *pack) const;

    std::string str() const;
    std::string numberingStr() const;
    std::string colHeightStr() const;
    std::string winnerStr() const;
};