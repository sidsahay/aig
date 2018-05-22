#pragma once
#include "game.h"
#include "game_impl.h"

namespace aig
{
    enum DummyCommand
    {
        DUMMY_GO_LEFT,
        DUMMY_GO_RIGHT,
        DUMMY_DO_NOTHING
    };

    class DummyGameState
    {
        public:
        double GetProperty(const std::string & prop_name, const int id) const;
        friend class DummyGame;

        private:
        double _x_position = 0.;
        double _x_velocity = 0.;
    };

    class DummyGame
    {
        public:
        using CommandT = DummyCommand;
        using StateT = DummyGameState;
        using EventT = int;

        DummyGame(const std::vector<IAgent<DummyGame>*>& agents, Graphics *graphics);

        void Initialize();

        void PreProcess();

        void RunAi(double elapsed_time);
        void UpdateState(double elapsed_time);
        
        void Render();

        bool HasEnded();

        private:
        DummyGameState _game_state;
        IAgent<DummyGame>* _player = nullptr;
        Graphics *_graphics = nullptr;
        DummyCommand _command = DUMMY_DO_NOTHING;

        //Component, not superclass, because it would create a type deduction cycle otherwise.
        ObservationTarget<DummyGame> _observation_target;
    };
}