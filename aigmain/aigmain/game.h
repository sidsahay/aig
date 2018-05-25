#pragma once
#include <vector>
#include <chrono>
#include <string>

#include "graphics.h"
#include "observer.h"
#include "observer_impl.h"

namespace aig
{
    //Templated agent interface, pass in the game type here (eg. for Pong it's PongGame).
    //It pulls the required types from inside the GameT.
    //Always use CommandT, StateT, and EventT instead of concrete types. 
    //And use auto as much as possible. Type deduction is an asset.
    template <typename GameT>
    class IAgent
    {
        public:
        using CommandT = typename GameT::CommandT;
        using StateT = typename GameT::StateT;
        using EventT = typename GameT::EventT;

        //Method you need to override. Takes a const state and an elapsed time as parameters, returns a CommandT object.
        //Eg for Pong it takes a PongGameState and a double, and returns a PongCommand.
        virtual typename GameT::CommandT Decide(const typename GameT::StateT& state, const double elapsed_time) = 0;

        //Used by GameSystem to assign unique IDs. Will disable this in the future. 
        //For now each agent is assigned a unique ID so that your code can identify it.
        //Usually, left player = 0, right player = 1.
        void SetId(int id);

        //You can use this to query for events. Agents are automatically wired up for events.
        //Component not parent class because components > inheritance. Usually.
        Observer<GameT> observer;

        virtual ~IAgent();

        protected:
        int _id = 0;
    };

    //Dependency injector (I think), also runs game loop and wires everything up.
    //Pass in the game type here (eg. for Pong, it's PongGame).
    template <typename GameT>
    class GameSystem
    {
        public:

        //Registers your agents with the system. They'll be injected into the game object automatically.
        //IMPORTANT: the system is not responsible for freeing memory for agents, you must do it yourself. 
        //IMPORTANT: each agent must be a unique object. Do NOT register two pointers to the same agent.
        //If you want to pass the same agent multiple times create multiple objects.
        void RegisterAgent(IAgent<GameT>* agent);
        
        //Initializes graphics, creates a window.
        //IMPORTANT: Must call this BEFORE RunGame().
        void CreateGameWindow(const char *title, int width, int height);
        
        //Game loop.
        void RunGame();

        ~GameSystem();

        private:
        std::vector<IAgent<GameT>*> _agents;
        Graphics* _graphics = nullptr;
        
        //Shady GUID system, lel.
        int _counter = 0;
    };
}