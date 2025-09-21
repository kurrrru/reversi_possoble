#include <src/Board.hpp>

#include <iostream>
#include <deque>
#include <tuple>
#include <unordered_map>
#include <functional> // for std::hash

namespace std {
    template<>
    struct hash<Board> {
        size_t operator()(const Board& b) const {
            return std::hash<std::string>()(b.toString());
        }
    };
}

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

std::unordered_map<std::pair<Board, int>, bool, pair_hash> memo;


bool reachable(Board& now, const Board& goal, int player, std::deque<std::tuple<int, int, int>>& path) {
    static int call_count = 0;
    ++call_count;
    if (call_count % 100000 == 0) {
        std::cerr << "Call count: " << call_count << ", Memo size: " << memo.size() << std::endl;
        now.printBoard();
    }
    if (now == goal) {
        return true;
    }
    if (now.getTotalCount() >= goal.getTotalCount()) {
        return false;
    }
    std::pair<Board, int> key = std::make_pair(now, player);
    if (memo.count(key)) {
        return memo[key];
    }
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (goal.getCell(r, c) == '.')
                continue;
            if (now.isValidMove(r, c, player)) {
                now.placePiece(r, c, player);
                if (reachable(now, goal, -player, path)) {
                    path.push_front(std::make_tuple(r, c, player));
                    return true;
                }
                now.undo();
            }
        }
    }
    memo[key] = false;
    return false;
}
