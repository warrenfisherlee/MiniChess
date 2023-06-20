#pragma once
#include "../state/statewu.hpp"
using namespace std;

class AplhaBeta{
    public:
    static Move get_move(State *state, int depth);
    static pair<int, int> dfsGetValue(State *state, int depth, int alpha, int beta);
};