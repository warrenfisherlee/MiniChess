#include <cstdlib>
#include <fstream>

#include "../state/state.hpp"
#include "./minimax.hpp"

std::ofstream test("test.txt", std::ios::app);


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
  {
    state->get_legal_actions();
    //state->evaluate();
  }
  auto actions=state->legal_actions;
  std::pair<Move, int> gogo=minimax(state, depth);
  test<<"gg"<<gogo.second<<std::endl;
  return gogo.first;
}

std::pair<Move, int> Minimax::minimax(State *state, int depth){
  //test<<"in minimax"<<std::endl;
  if(!state->legal_actions.size())
  {
    state->get_legal_actions();
    //state->evaluate();
  }
  Move what; //useless move
  if (depth==0)
  {
    
    state->evaluate();
    //test<<"in 0"<<std::endl;
    //test<<state->total<<std::endl;
    return std::pair<Move, int>(what, state->total);
  }

  std::pair<Move, int> temp;

  if (depth%2) //max
  {
    //test<<"in 1"<<std::endl;
    temp.second=-2e9;
    int ref_max=temp.second;
    auto actions=state->legal_actions;
    test<<"size: "<<actions.size()<<"player: "<<state->player<<std::endl;
    Move max_move;
    for (int i=0; i<actions.size(); i++)
    {
      temp=minimax(state->next_state(actions[i]), depth-1);
      if (depth==1) temp.first=actions[i];
      //if (depth==1) temp.first=i;
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
    temp.second=2e9;
    int ref_min=temp.second;
    auto actions=state->legal_actions;
    Move min_move;
    for (int i=0; i<actions.size(); i++)
    {
      temp=minimax(state->next_state(actions[i]), depth-1);
      if (temp.second<ref_min)
      {
        min_move=temp.first;
        ref_min=temp.second;
      }
    }
    return std::pair<Move, int>(min_move, ref_min);
  }
}