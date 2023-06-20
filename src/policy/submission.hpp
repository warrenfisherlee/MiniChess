#pragma once
#include "../state/state.hpp"



/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Alphabeta2{
public:
  static Move get_move(State *state, int depth);
  //static std::pair<Move, int> minimax(State *state , int depth);
  static std::pair<int, int> alphabeta(State *state , int depth, int alpha, int beta);
};