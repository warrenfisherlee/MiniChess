#include <cstdlib>
#include <fstream>

#include "../state/state.hpp"
#include "./alphabeta.hpp"

std::ofstream al("al.txt", std::ios::app);


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
/*
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
    test<<state->total<<std::endl;
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
*/


Move Alphabeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
  {
    state->get_legal_actions();
    //state->evaluate();
  }
  auto actions=state->legal_actions;
  al<<"why"<<std::endl;
  std::pair<std::pair<int, int>, std::pair<int, int>> gogo = alphabeta(state, depth, -2e9, 2e9);
  al<<"gg"<<gogo.first.second<<std::endl;
  return actions[gogo.first.first];
}

std::pair<std::pair<int, int>, std::pair<int, int>> Alphabeta::alphabeta(State *state, int depth, int alpha, int beta){
  //test<<"in minimax"<<std::endl;
  //alpha=-2e9;
  //beta=2e9;
  Move what; //useless move
  if (depth==0)
  {
    state->evaluate();
    std::pair<std::pair<int, int>, std::pair<int, int>> p;
    p.first.first=0;
    p.first.second=state->total;
    p.second.first=-2e9;
    p.second.second=2e9;
    al<<"depth0: "<<state->total<<std::endl;
    return p;
  }

  std::pair<std::pair<int, int>, std::pair<int, int>> temp;

  if (depth%2) //max
  {
    //al<<"depth: "<<depth<<std::endl;
    //test<<"in 1"<<std::endl;
    std::pair<std::pair<int, int>, std::pair<int, int>> maxmax;
    maxmax.first.second=-2e9;
    int ref_max=maxmax.first.second;
    auto actions=state->legal_actions;
    //al<<"size: "<<actions.size()<<"player: "<<state->player<<std::endl;
    al<<"what"<<std::endl;
    int max_move;
    for (int i=0; i<actions.size(); i++)
    {
      temp=alphabeta(state->next_state(actions[i]), depth-1, alpha, beta);
      if (depth!=1) alpha=std::max(temp.second.first, alpha);
      if (temp.first.second>maxmax.first.second)
      {
        maxmax.first.first=i;
        maxmax.first.second=temp.first.second;
      }
      alpha=std::max(alpha, maxmax.first.second);
      if (alpha>=beta) break;
    }
    maxmax.second.second=alpha;
    return maxmax;
  }
  else //min
  {
    std::pair<std::pair<int, int>, std::pair<int, int>> minmin;
    minmin.first.second=2e9;
    int ref_min=minmin.first.second;
    auto actions=state->legal_actions;
    int min_move;
    for (int i=0; i<actions.size(); i++)
    {
      temp=alphabeta(state->next_state(actions[i]), depth-1, alpha, beta);
      if (depth!=1) beta=std::min(temp.second.second, beta);
      if (temp.first.second<minmin.first.second)
      {
        minmin.first.first=i;
        minmin.first.second=temp.first.second;
      }
      beta=std::min(beta, minmin.first.second);
      if (beta<=alpha) break;
    }
    minmin.second.first=beta;
    return minmin;
  }
}

/*
Move Minimax::get_move(State *state, int depth){
    if(!state->legal_actions.size())
    state->get_legal_actions();

    //mydebug << "haha\n";
    auto bestValue = minimax(state, depth);
    auto actions = state->legal_actions;
    
    return actions[bestValue.second];
}

std::pair<int, int> Minimax::minimax(State *state, int depth){  //odd depth for max, even for min

    if(depth == 0){
        std::pair<int, int> p;
        p.first = state->evaluate();
        //mydebug << p.first << std::endl;
        p.second = 0;
        return p;
    }
    if(depth % 2 == 1){ //search for max
        //mydebug << "max~" << std::endl;
        std::pair<int, int>bestValue;
        bestValue.first = -2e9;
        bestValue.second = 0;
        int n = 0;
        auto actions = state->legal_actions;
        for(auto it=actions.begin();it!=actions.end();it++){
            auto nextState = state->next_state(*it);
            int score = minimax(nextState, depth-1).first;
            //mydebug << "score: " << score << ", orig: " << bestValue.first << "\n";
            if(score > bestValue.first){
                bestValue.first = score;
                bestValue.second = n;
            }
            n ++;
        }
        return bestValue;
    }else{  //search for min
        //mydebug << "min~!~" << std::endl;
        std::pair<int, int>bestValue;
        bestValue.first = 2e9;
        bestValue.second = 0;
        int n = 0;
        auto actions = state->legal_actions;
        for(auto it=actions.begin();it!=actions.end();it++){
            auto nextState = state->next_state(*it);
            int score = minimax(nextState, depth-1).first;
            if(score < bestValue.first){
                bestValue.first = score;
                bestValue.second = n;
            }
            n ++;
        }
        return bestValue;
    }
}
*/