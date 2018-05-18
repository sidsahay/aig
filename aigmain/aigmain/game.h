#pragma once
#include <vector>
#include <chrono>

#include "graphics.h"

namespace aig
{
    class IGameState
    {
        public:
        virtual double GetProperty(const std::string& prop_name, const int id) const = 0;
    };

    class IAgent
    {
        public:
        virtual int Decide(const IGameState& state, const double elapsed_time) = 0;
        void SetId(int id);

        protected:
        int _id = 0;
    };

    template <typename GameT>
    class GameSystem
    {
        public:
        void RegisterAgent(IAgent* agent);
        
        void CreateGameWindow(const char *title, int width, int height);
        void RunGame();

        ~GameSystem();

        private:
        std::vector<IAgent*> _agents;
        Graphics* _graphics = nullptr;
        int _counter = 0;
    };
}