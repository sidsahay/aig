#pragma once
#include <vector>
#include <chrono>

#include "graphics.h"
#include "observer.h"
#include "observer_impl.h"

namespace aig
{
    template <typename GameT>
    class IAgent : public Observer<typename GameT>
    {
        public:
        using CommandT = typename GameT::CommandT;
        using StateT = typename GameT::StateT;
        using EventT = typename GameT::EventT;

        virtual typename GameT::CommandT Decide(const typename GameT::StateT& state, const double elapsed_time) = 0;
        void SetId(int id);

        protected:
        int _id = 0;
    };

    template <typename GameT>
    class GameSystem
    {
        public:
        void RegisterAgent(IAgent<GameT>* agent);
        
        void CreateGameWindow(const char *title, int width, int height);
        void RunGame();

        ~GameSystem();

        private:
        std::vector<IAgent<GameT>*> _agents;
        Graphics* _graphics = nullptr;
        int _counter = 0;
    };
}