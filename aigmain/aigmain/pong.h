#pragma once
#include <iostream>

#include "game.h"
#include "game_impl.h"
#include "physics.h"

namespace aig
{
    constexpr double PONG_NORM_SPEED = 300;

    enum PongCommand
    {
        PONG_GO_UP,
        PONG_GO_DOWN,
        PONG_STOP,
        PONG_DO_NOTHING
    };

    enum PongEventAction
    {
        PONG_HIT,
        PONG_GAME_OVER,
    };

    enum PongObject
    {
        PONG_LEFT_PADDLE,
        PONG_RIGHT_PADDLE,
        PONG_BALL,
        PONG_TOP_BOUNDARY,
        PONG_BOTTOM_BOUNDARY,
        PONG_LEFT_BOUNDARY,
        PONG_RIGHT_BOUNDARY
    };

    enum PongProperty
    {
        PONG_POSITION,
        PONG_BOUNDING_BOX_EXTENT,
        PONG_VELOCITY
    };

    class PongEvent
    {
        public:
        PongEventAction action;
        PongObject objects[2];
    };

    class PongGameState
    {
        public:
        Vector2 GetProperty(const PongObject object, const PongProperty property, const int id) const;
        friend class PongGame;

        private:
        Rectangle _objects[7]; //two paddles, one ball, four boundaries. Indexed by PongObject values.
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

        void PreProcess();

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
        
        Observer<GameT> _observer;

        bool _has_ended = false;
    };
}