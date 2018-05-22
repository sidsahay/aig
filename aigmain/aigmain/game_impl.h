#pragma once
#include "game.h"

template <typename GameT>
void aig::IAgent<GameT>::SetId(int id)
{
    _id = id;
}

template<typename GameT>
inline aig::IAgent<GameT>::~IAgent()
{
}

template <typename GameT>
void aig::GameSystem<GameT>::RegisterAgent(IAgent<GameT> * agent)
{
    //TODO use a PRNG here to generate a proper GUID. Or some other form of GUID generation.
    agent->SetId(_counter);
    _counter++;
    _agents.push_back(agent);
}

template <typename GameT>
void aig::GameSystem<GameT>::CreateGameWindow(const char * title, int width, int height)
{
    _graphics = new Graphics();
    _graphics->CreateWindow(title, width, height);
}

template <typename GameT>
void aig::GameSystem<GameT>::RunGame()
{
    using namespace std::chrono;

    high_resolution_clock::time_point 
        previous_time = high_resolution_clock::now();

    GameT game(_agents, _graphics);
    game.Initialize();

    //Simple game loop
    while (!game.HasEnded())
    {
        high_resolution_clock::time_point 
            current_time = high_resolution_clock::now();

        duration<double> span = current_time - previous_time;
        double elapsed_time = span.count();
        previous_time = current_time;

        game.PreProcess();
        game.RunAi(elapsed_time);
        game.UpdateState(elapsed_time);
        game.Render();
    }

    _graphics->WaitForQuit();
}

template<typename GameT>
aig::GameSystem<GameT>::~GameSystem()
{
    delete _graphics;
}