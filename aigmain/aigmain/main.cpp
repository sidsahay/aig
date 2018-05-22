#include <iostream>

#include "pong.h"

class TrackingAgent : public aig::IAgent<aig::PongGame>
{
    virtual CommandT Decide(const StateT& state, double elapsed_time)
    {
        using namespace aig;

        //pump events to avoid memory usage buildup.
        while (observer.EventsAvailable())
        {
            observer.GetEvent();
        }


        //Simple ball tracker. Works for now because velocities are equal.
        //TODO: Implement an identity system for the AI agents and provide a proper mapping to
        //left/right.
        const auto ball_position = state.GetProperty(PONG_BALL, PONG_POSITION, _id);

        //because left AI has _id of 0 and LEFT_PADDLE is also 0. And similarly for right (1 in both cases). Shady, yes. Will fix.
        const auto self_position = state.GetProperty(PongObject(_id), PONG_POSITION, _id); 

        if (ball_position.y > self_position.y)
        {
            return PONG_GO_UP;
        }
        else if (ball_position.y < self_position.y)
        {
            return PONG_GO_DOWN;
        }
        else
        {
            return PONG_STOP;
        }
    }
};

int main(int argc, char **argv)
{
    aig::GameSystem<aig::PongGame> system;
    
    aig::IAgent<aig::PongGame>* agent_left = new TrackingAgent;
    aig::IAgent<aig::PongGame>* agent_right = new TrackingAgent;

    system.RegisterAgent(agent_left);
    system.RegisterAgent(agent_right);

    system.CreateGameWindow("Pong", 600, 600);
    system.RunGame();

    delete agent_left;
    delete agent_right;

    return 0;
}