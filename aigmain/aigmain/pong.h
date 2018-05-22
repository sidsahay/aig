#pragma once

#include "game.h"
#include "physics.h"

namespace aig
{
    enum PongCommand
    {
        PONG_GO_UP,
        PONG_GO_DOWN,
        PONG_STOP,
        PONG_DO_NOTHING
    };

    class PongEvent
    {
        enum Event
        {

        };


    };

    class PongGameState
    {
        public:
        Vector2 GetProperty(const std::string & prop_name, const int id) const;
        
        
        private:

    };

    class PongGame
    {
        public:
        using GameT = PongGame;
        using CommandT = PongCommand;
        using StateT = PongGameState;
        using EventT = PongEvent;

        PongGame(const std::vector<IAgent<GameT>*>& agents, Graphics *graphics);

        void Initialize();

        void RunAi(double elapsed_time);
        void UpdateState(double elapsed_time);
        
        void Render();

        bool HasEnded();

        private:
        StateT _game_state;
        
        IAgent<GameT>* _left_player = nullptr;
        IAgent<GameT>* _right_player = nullptr;
        
        Graphics *_graphics = nullptr;
        
        CommandT _left_command = PONG_DO_NOTHING;
        CommandT _right_command = PONG_DO_NOTHING;

        //Component, not superclass, because it would create a type deduction cycle otherwise.
        ObservationTarget<GameT> _observation_target;
    };
}