#pragma once
#include <iostream>

#include "game.h"
#include "game_impl.h"
#include "physics.h"

namespace aig
{
    //Just a declaration here so that it can be used as a named constant.
    constexpr double PONG_NORM_SPEED = 300;

    //All the commands that the AI can emit.
    enum PongCommand
    {
        PONG_GO_UP,
        PONG_GO_DOWN,
        PONG_STOP,
        PONG_DO_NOTHING
    };

    //All the "happenings" that can happen in an event
    enum PongEventAction
    {
        PONG_HIT,
        PONG_GAME_OVER,
    };

    //Assigns an id to each object onscreen so that you can refer to it.
    //Enums set their constant to integral values stating from 0 by default.
    //So these constants can be used to index into an array of 7 elements.
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

    //The properties of each object you can query for via GetProperty()
    enum PongProperty
    {
        PONG_POSITION,
        PONG_BOUNDING_BOX_EXTENT,
        PONG_VELOCITY
    };

    //An event is a bag containing what happened and which objects it happened to.
    //So eg. an event with PONG_HIT as the action will have the two objects that collided
    //filled in the objects[] array.
    class PongEvent
    {
        public:
        PongEventAction action;
        PongObject objects[2];
    };

    //Records the state of the game. Duh.
    //An outsider can only get data about this from GetProperty()
    //This is so that the game state representation can be changed (eg. network it to another PC)
    //without changing the way data is accessed.
    class PongGameState
    {
        public:

        //Used to query data from the game state. You specify which object (a PongObject value) 
        //and what data to get about that object (a PongProperty value). Also hand in the id in the third argument.
        //Because reasons. It doesn't do anything right now.
        Vector2 GetProperty(const PongObject object, const PongProperty property, const int id) const;

        friend class PongGame;

        private:

        //two paddles, one ball, four boundaries. Indexed by PongObject values.
        Rectangle _objects[7]; 
    };

    //Internal class that represents the game.
    class PongGame
    {
        public:

        //So that this becomes a template kinda thing for all games.
        using GameT = PongGame;
        using CommandT = PongCommand;
        using StateT = PongGameState;
        using EventT = PongEvent;

        //Assigns the first two agents to left_player and right_player.
        PongGame(const std::vector<IAgent<GameT>*>& agents, Graphics *graphics);

        //Called before game starts running.
        void Initialize();

        //Called at the start of processing a frame. Event handling etc.
        void PreProcess();

        //Called after PreProcess(). Runs the Decide() function for agents.
        void RunAi(double elapsed_time);

        //Called after RunAi(). Interprets AI commands, does physics processing.
        void UpdateState(double elapsed_time);
        
        //Last step in frame processing. Draws the output.
        void Render();

        //Used for the game loop.
        bool HasEnded();

        private:

        //Contains the state of  the game.
        StateT _game_state;
        
        //Pong is a 2 player game.
        IAgent<GameT>* _left_player = nullptr;
        IAgent<GameT>* _right_player = nullptr;
        
        Graphics *_graphics = nullptr;
        
        //Stores the outputs of the two AI agents.
        CommandT _left_command = PONG_DO_NOTHING;
        CommandT _right_command = PONG_DO_NOTHING;

        //Component, not superclass, because it would create a type deduction cycle otherwise.
        //Used to fire events.
        ObservationTarget<GameT> _observation_target;
        
        //Internal observer for observing events like game endings.
        Observer<GameT> _observer;

        bool _has_ended = false;
    };
}