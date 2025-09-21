#pragma once

#include <vector>
#include <string>
#include <deque>
#include <stack>

class Board {
 public:
    Board();
    Board(const Board& other);
    Board& operator=(const Board& other);
    ~Board();

    explicit Board(const std::vector<std::string>& board);

    bool setBoard(const std::vector<std::string>& board);

    // player: -1 for black, 1 for white
    bool isValidMove(int row, int col, int player) const;
    bool placePiece(int row, int col, int player);

    void printBoard() const;

    int getBlackCount() const;
    int getWhiteCount() const;
    int getTotalCount() const;

    bool operator==(const Board& other) const;

    char getCell(int row, int col) const;

    std::string toString() const;

    void undo();

 private:
    std::vector<std::vector<char>> _board;
    std::stack<std::vector<std::tuple<int, int, char>>> _history; // (row, col, previous state)
    const int _width = 8;
    const int _height = 8;
    const char _emptyCell = '.';
    const char _blackCell = 'x';
    const char _whiteCell = 'o';
    int _blackCount;
    int _whiteCount;
};

bool reachable(Board& now, const Board& goal, int player, std::deque<std::tuple<int, int, int>>& path);
