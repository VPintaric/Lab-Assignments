#include "Board.h"
#include <iostream>
#include <sstream>
#include <string>  
#include <cstdlib>
#include <fstream>
#include <vector>
#include <utility>

#ifdef DEBUG
#define REDEF_DEBUG
#undef DEBUG
#endif

#if defined(DEBUG) && !defined(D_PRINT) 
#define D_PRINT(M) std::cout << __func__ << ": " << M << std::endl;
#endif

Board::Board(int w, int h) : width(w), height(h){
#ifdef DEBUG
    D_PRINT("width = " << width << ", height = " << height);
#endif

    if(width < 0 || height < 0){
        std::cerr << "Width or height is negative" << std::endl;
        exit(3);
    }

    board = new Slot[width * height];
    col_height = new int[width]();
    winner = Slot::EMPTY;
    can_undo = false;

#ifdef DEBUG
    D_PRINT("board = " << board);
#endif

#ifdef DEBUG
    D_PRINT("board state = " << std::endl << str());
#endif
}

Board::Board(const Board &obj){
#ifdef DEBUG
    D_PRINT("obj.width = " << obj.getWidth() << ", obj.height = " << obj.getHeight());
#endif

    width = obj.getWidth();
    height = obj.getHeight();
    winner = obj.getWinner();
    can_undo = obj.canUndo();
    last_winner = obj.getLastWinner();
    last_move = obj.getLastMove();

    board = new Slot[width * height];
    col_height = new int[width];

#ifdef DEBUG
    D_PRINT("board = " << board);
#endif

    for(int c = 0; c < width; c++)
        col_height[c] = obj.getColHeight(c);
    for(int r = 0; r < height; r++)
        for(int c = 0; c < width; c++)
            slot(r, c) = obj(r, c);

#ifdef DEBUG
    D_PRINT("board state = " << std::endl << str());
#endif
}

Board::Board(std::string file_name){
#ifdef DEBUG
    D_PRINT("file_name = " << file_name);
#endif

    winner = Slot::EMPTY;
    can_undo = false;

    std::ifstream file(file_name);

    if(!file.is_open()){
        std::cerr << "Could not open file " << file_name << std::endl;
        exit(1);
    }

    file >> width >> height;

    if(width < 0 || height < 0){
        std::cerr << "Width or height is negative" << std::endl;
        exit(3);
    }

#ifdef DEBUG
    D_PRINT("width = " << width << ", height = " << height);
#endif

    board = new Slot[width * height];
    col_height = new int[width]();

#ifdef DEBUG
    D_PRINT("board = " << board);
#endif

    for(int r = height - 1; r >= 0; r--){
        for(int c = 0; c < width; c++){
            if(file.eof()){
                std::cerr << "EOF reached but didn't read whole board" << std::endl;
                file.close();
                exit(2);
            }
            char sym;
            file >> sym;
            slot(r, c) = getSlotFromSymbol(sym);

            if(slot(r, c) != Slot::EMPTY && col_height[c] == 0){
                col_height[c] = r + 1;
            }
            else if(slot(r, c) == Slot::EMPTY && col_height[c] > r){
                std::cerr << "Invalid board state" << std::endl;
                file.close();
                exit(4);
            }
        }
    }
    file.close();

#ifdef DEBUG
    D_PRINT("board state = " << std::endl << str());
#endif
}

Board::Board(int *pack){
    last_move = -1;
    last_winner = Slot::EMPTY;
    can_undo = false;

    int idx = 0;
    winner = intToSlot(pack[idx++]);
    width = pack[idx++];
    height = pack[idx++];

    board = new Slot[width * height];
    col_height = new int[width]();

#ifdef DEBUG
    D_PRINT("winner = " << getSymbol(winner) << ", width = " << width << ", height = " << height);
#endif

    for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
            Slot s = intToSlot(pack[idx++]);

            slot(r, c) = s;
#ifdef DEBUG
            D_PRINT("current slot = " << getSymbol(s));
#endif

            if(s != Slot::EMPTY){
                if(r == col_height[c])
                    col_height[c]++;
                else{
                    std::cerr << "Invalid packed board" << std::endl;
                    exit(9);
                }
            }
        }
    }

    checkWinner();
}

Board::~Board(){
#ifdef DEBUG
    D_PRINT("board = " << board);
#endif
    delete [] board;
}

Slot& Board::slot(int r, int c){
    assertBoundary(r, c);
// #ifdef DEBUG
//     D_PRINT("r = " << r << ", c = " << c);
//     D_PRINT("ret = " << getSymbol(board[r * width + c]));
// #endif
    return board[r * width + c];
}

Slot Board::operator()(int r, int c) const{
    assertBoundary(r, c);
    return board[r * width + c];
}

void Board::insertCoin(Slot tag, int c){
#ifdef DEBUG
    D_PRINT("tag = " << getSymbol(tag) << ", c = " << c);
    D_PRINT("col_height[" << c << "] = " << col_height[c]);
    //D_PRINT("board state before = " << std::endl << str() << std::endl);
#endif

    if(tag == Slot::EMPTY){
        std::cerr << "Can't \"insert\" empty coin" << std::endl;
        exit(5);
    }

    if(col_height[c] == height){
        std::cerr << "Invalid move" << std::endl;
        exit(6);
    }

    last_move = c;
    last_winner = winner;
    can_undo = true;

    slot(col_height[c]++, c) = tag;

    checkWinnerIncludingTile(col_height[c] - 1, c);

#ifdef DEBUG
    //D_PRINT("board state after = " << std::endl << str() << std::endl);
#endif
}

void Board::undoLast(){
#ifdef DEBUG
    D_PRINT("last_move = " << last_move << ", last_winner = " << getSymbol(last_winner));
#endif

    if(!can_undo){
        std::cerr << "Can't undo" << std::endl;
        exit(6);
    }

    can_undo = false;

    winner = last_winner;
    slot(--col_height[last_move], last_move) = Slot::EMPTY;
}

std::vector<int> Board::getValidMoves(){
    std::vector<int> valid_moves;

    for(int c = 0; c < width; c++)
        if(col_height[c] < height)
            valid_moves.push_back(c);

    return valid_moves;
}

void Board::checkWinnerIncludingTile(int sr, int sc){
#ifdef DEBUG
    D_PRINT("sr = " << sr << ", sc = " << sc);
#endif

    if(winner != Slot::EMPTY || slot(sr, sc) == Slot::EMPTY)
        return;

    do{
        Slot potWin = slot(sr, sc);
        int count, r, c;

        // Check left -> right
        r = sr; c = sc; count = 0;
        while(c >= 0 && slot(r, c) == potWin) c--;
        c++;
        while(c < width && slot(r, c) == potWin) count++, c++; 
        if(count >= IN_ROW_TO_WIN){
            winner = potWin;
            c--;
            while(count-- > 0) winning_slots.push_back(std::make_pair(r, c--));
            break;
        }

        // Check bottom -> top
        r = sr; c = sc; count = 0;
        while(r >= 0 && slot(r, c) == potWin) r--;
        r++;
        while(r < height && slot(r, c) == potWin) count++, r++;
        if(count >= IN_ROW_TO_WIN){
            winner = potWin;
            r--;
            while(count-- > 0) winning_slots.push_back(std::make_pair(r--, c));
            break;
        }

        // Check bottom-left -> top-right
        r = sr; c = sc; count = 0;
        while(r >= 0 && c >= 0 && slot(r, c) == potWin) r--, c--;
        r++, c++;
        while(r < height && c < width && slot(r, c) == potWin) r++, c++, count++;
        if(count >= IN_ROW_TO_WIN){
            winner = potWin;
            r--, c--;
            while(count-- > 0) winning_slots.push_back(std::make_pair(r--, c--));
            break;
        }

        // Check bottom-right -> top-left
        r = sr; c = sc; count = 0;
        while(r >= 0 && c < width && slot(r, c) == potWin) r--, c++;
        r++, c--;
        while(r < height && c >= 0 && slot(r, c) == potWin) r++, c--, count++;
        if(count >= IN_ROW_TO_WIN){
            winner = potWin;
            r--, c++;
            while(count-- > 0) winning_slots.push_back(std::make_pair(r--, c++));
            break;
        }

    }while(false);

#ifdef DEBUG
    if(winner != Slot::EMPTY){
        D_PRINT("winner = " << getSymbol(winner));
        std::stringstream ss;
        ss << "Winning slots = [";
        for(unsigned i = 0; i < winning_slots.size(); i++)
            ss << "(" << winning_slots[i].first << ", " << winning_slots[i].second << "), ";
        ss << "]";
        D_PRINT(ss.str());
    }
#endif
}

void Board::checkWinner(){
    int r, c;
    for(r = 0, c = 0; r < height && c < width && winner == Slot::EMPTY; r++, c++)
        checkWinnerIncludingTile(r, c);
}

int Board::getWidth() const{
    return width;
}

int Board::getHeight() const{
    return height;
}

int Board::getColHeight(int c) const{
    return col_height[c];
}

Slot Board::getWinner() const{
    return winner;
}

Slot Board::getLastWinner() const{
    return last_winner;
}

int Board::getLastMove() const{
    return last_move;
}

bool Board::canUndo() const{
    return can_undo;
}

void Board::assertBoundary(int r, int c) const{
    if(r < 0 || r >= height || c < 0 || c >= width){
        std::cerr << "Out of bounds" << std::endl;
        exit(3);
    }
}

char Board::getSymbol(Slot s){
    switch(s){
        case(Slot::EMPTY):
            return SLOT_EMPTY_SYMBOL;
            //break;
        case(Slot::PLAYER_1):
            return SLOT_PLAYER_1_SYMBOL;
            //break;
        case(Slot::PLAYER_2):
            return SLOT_PLAYER_2_SYMBOL;
            //break;

        default:
            return SLOT_GARBAGE_SYMBOL;
    }
}

Slot Board::getSlotFromSymbol(char sym){
    switch(sym){
        case(SLOT_EMPTY_SYMBOL):
            return Slot::EMPTY;
            //break;
        case(SLOT_PLAYER_1_SYMBOL):
            return Slot::PLAYER_1;
            //break;
        case(SLOT_PLAYER_2_SYMBOL):
            return Slot::PLAYER_2;
            //break;

        default:
            return Slot::EMPTY;
    }
}

bool Board::slotIsWinningSlot(int r, int c) const{
    for(unsigned i = 0; i < winning_slots.size(); i++){
        std::pair<int, int> slot = winning_slots[i];

        if(slot.first == r && slot.second == c)
            return true;
    }
    return false;
}

std::string Board::str() const{
    std::stringstream ss;

    int row_length = (STR_SPACING_WIDTH + 1) * width + STR_SPACING_WIDTH + 2;

    for(int i = 0; i < row_length; i++)
        ss << STR_UPPER_AND_LOWER_BOUNDARY_SYMBOL;

    ss << std::endl;

    for(int i = 0; i < STR_SPACING_HEIGHT; i++){
        ss << "|";
        for(int j = 0; j < row_length - 2; j++)
            ss << " ";
        ss << "|" << std::endl;
    }

    for(int i = (STR_SPACING_HEIGHT + 1) * height; i > 0; i--){
        ss << "|";

        // Empty row
        if(i % (STR_SPACING_HEIGHT + 1)){
            for(int j = 0; j < row_length - 2; j++)
                ss << " ";
        }
        // Non-empty row
        else{
            for(int j = 0; j < STR_SPACING_WIDTH; j++)
                ss << " ";
            for(int j = 0; j < (STR_SPACING_WIDTH + 1) * width; j++){
                if(j % (STR_SPACING_WIDTH + 1))
                    ss << " ";
                else{
                    int r = i / (STR_SPACING_HEIGHT + 1) - 1;
                    int c = j / (STR_SPACING_WIDTH + 1);
                    Slot tag = operator()(r, c);
                    if(slotIsWinningSlot(r, c))
                        ss << "\033[33m" << getSymbol(tag) << "\033[0m";
                    else if(tag == Slot::PLAYER_1)
                        ss << "\033[31m" << getSymbol(tag) << "\033[0m";
                    else if(tag == Slot::PLAYER_2)
                        ss << "\033[32m" << getSymbol(tag) << "\033[0m";
                    else
                        ss << getSymbol(tag);
                }
            }
        }

        ss << "|" << std::endl;
    }

    for(int i = 0; i < row_length; i++)
        ss << STR_UPPER_AND_LOWER_BOUNDARY_SYMBOL;
    ss << std::endl;

    ss << numberingStr() << std::endl;

#ifdef DEBUG
    ss << colHeightStr() << std::endl;
#endif

    return ss.str();
}

std::string Board::numberingStr() const{
    std::stringstream ss;

    for(int i = 0; i < STR_SPACING_WIDTH + 1; i++)
        ss << " ";

    for(int i = 0; i < (STR_SPACING_WIDTH + 1) * width; i++){
        if(i % (STR_SPACING_WIDTH + 1))
            ss << " ";
        else
            ss << (i / (STR_SPACING_WIDTH + 1));
    }

    ss << " ";

    return ss.str();
}

std::string Board::colHeightStr() const{
    std::stringstream ss;

    ss << "H";
    for(int i = 0; i < STR_SPACING_WIDTH; i++)
        ss << " ";

    for(int i = 0; i < (STR_SPACING_WIDTH + 1) * width; i++){
        if(i % (STR_SPACING_WIDTH + 1))
            ss << " ";
        else
            ss << col_height[i / (STR_SPACING_WIDTH + 1)];
    }

    ss << " ";

    return ss.str();
}

std::string Board::winnerStr() const{
    std::stringstream ss;

    ss << "Winner: ";

    switch(winner){
        case Slot::EMPTY:
            ss << "still no one";
            break;
        case Slot::PLAYER_1:
            ss << "Player 1";
            break;
        case Slot::PLAYER_2:
            ss << "Player 2";
            break;

        default:
            ss << "unknown";
    }

    return ss.str();
}

int Board::slotToInt(Slot s){
    switch(s){
        case Slot::PLAYER_1:
            return 1;
        case Slot::PLAYER_2:
            return 2;
        default:
            return 0;
    }
}

Slot Board::intToSlot(int x){
    switch(x){
        case 1:
            return Slot::PLAYER_1;
        case 2:
            return Slot::PLAYER_2;
        default:
            return Slot::EMPTY;
    }
}

int Board::getPackSize() const{
    return width * height + 3;
}

void Board::pack(int *pack) const{
    int idx = 0;

    pack[idx++] = slotToInt(winner);
    pack[idx++] = width;
    pack[idx++] = height;

    for(int r = 0; r < height; r++)
        for(int c = 0; c < width; c++)
            pack[idx++] = slotToInt(operator()(r, c));
}


#ifdef REDEF_DEBUG
#define DEBUG
#endif