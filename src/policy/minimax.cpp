#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  std::pair<Move, int> gogo=minimax(state, depth);
  return gogo.first;
}

std::pair<Move, int> Minimax::minimax(State *state, int depth){
  if(!state->legal_actions.size())
  {
    state->get_legal_actions();
    //state->evaluate();
  }
  Move what;
  if (depth==0)
  {
    state->evaluate();
    return std::pair<Move, int>(what, state->total);
  }

  std::pair<Move, int> temp;

  if (depth%2) //max
  {
    int ref_max=state->total;
    auto actions=state->legal_actions;
    Move max_move;
    for (int i=0; i<actions.size(); i++)
    {
      temp=minimax(state->next_state(actions[i]), depth-1);
      if (depth==1) temp.first=actions[i];
      if (temp.second>ref_max)
      {
        max_move=temp.first;
        ref_max=temp.second;
      }
    }
    return std::pair<Move, int>(max_move, ref_max);
  }
  else //min
  {
    int ref_min=state->total;
    auto actions=state->legal_actions;
    Move min_move;
    for (int i=0; i<actions.size(); i++)
    {
      temp=minimax(state->next_state(actions[i]), depth-1);
      if (temp.second>ref_min)
      {
        min_move=temp.first;
        ref_min=temp.second;
      }
    }
    return std::pair<Move, int>(min_move, ref_min);
  }
}