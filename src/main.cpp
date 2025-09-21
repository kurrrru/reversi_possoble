#include <src/Board.hpp>

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>
#include <deque>
#include <tuple>

int main() {
    Board board;
    board.printBoard();

    try {
        std::vector<std::string> customBoard = { // フラットローズ定石
            "........",
            "........",
            "...xx...",
            "...xxxx.",
            "..xoxo..",
            "..oooo..",
            "...o....",
            "........"
        };
        Board custom(customBoard);
        custom.printBoard();
        std::deque<std::tuple<int, int, int>> path;
        if (reachable(board, custom, -1, path)) {
            for (std::size_t i = 0; i < path.size(); ++i) {
                std::tuple<int, int, int> move = path[i];
                char playerChar = std::get<2>(move) == -1 ? 'x' : 'o';
                std::cout << "Move " << i + 1 << ": Player " << playerChar
                    << " to " << static_cast<char>('A' + std::get<1>(move)) << std::get<0>(move) << "\n";
            }
            std::cout << "reachable" << std::endl;
        } else {
            std::cout << "not reachable" << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
