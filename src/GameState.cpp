#include <GameState.h>

using namespace ExomoMarsLander;

GameState::GameState()
{
    //ctor
}

GameState::~GameState()
{
    //dtor
}

StateMachine::StateMachine(const GameStatePtr& initialState)
    : currentState(initialState)
{

}
