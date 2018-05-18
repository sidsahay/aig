#pragma once
#include "game.h"
#include "game_impl.h"

namespace aig
{
    enum DummyCommands
    {
        DUMMY_GO_LEFT,
        DUMMY_GO_RIGHT,
        DUMMY_DO_NOTHING
    };

    class DummyGameState : public IGameState
    {
        public:
        virtual double GetProperty(const std::string & prop_name, const int id) const override;
        friend class DummyGame;

        private:
        double _x_position = 0.;
        double _x_velocity = 0.;
    };

    class DummyGame
    {
        public:
        DummyGame(const std::vector<IAgent*>& agents, Graphics *graphics);

        void Initialize();

        void RunAi(double elapsed_time);
        void UpdateState(double elapsed_time);
        
        void Render();

        bool HasEnded();

        private:
        DummyGameState _game_state;
        IAgent* _player = nullptr;
        Graphics *_graphics = nullptr;
        int _command = DUMMY_DO_NOTHING;
    };
}