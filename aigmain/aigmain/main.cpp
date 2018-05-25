//Only #include the game header. Not the others.
#include "pong.h"

//Make sure your agent subclasses the IAgent<GameT> interface. 
//And that IAgent is given the proper game class as its template parameter.
class TrackingAgent : public aig::IAgent<aig::PongGame>
{
    //You should ALWAYS write the signature of Decide() like this when overriding it.
    //Try not to use concrete types. CommandT, StateT, and EventT are typedefs (essentially) 
    //pulled from IAgent<GameT>. Use them.
    virtual CommandT Decide(const StateT& state, double elapsed_time)
    {
        //Try to import namespaces locally, not globally. Good habit.
        using namespace aig;

        //ALWAYS pump events to avoid memory usage buildup.
        //Agents are wired up for events automatically. So if you don't pump
        //the event queue, it will keep accumulating event data. 
        while (observer.EventsAvailable())
        {
            //Does nothing except remove the event from the queue.
            observer.GetEvent();
        }

        //Simple ball tracker.
        //TODO: Implement an identity system for the AI agents and provide a proper mapping to
        //left/right.
        //It's a good idea to use auto so that you don't have to worry about types.
        const auto ball_position = state.GetProperty(PONG_BALL, PONG_POSITION, _id);

        //because left AI has _id of 0 and LEFT_PADDLE is also 0. And similarly for right (1 in both cases). Shady, yes. Will fix.
        const auto self_position = state.GetProperty(PongObject(_id), PONG_POSITION, _id); 

        /*
        A better way to do the above:
        if (_id == 0) {
            self_position = state.GetProperty(PONG_LEFT_PADDLE, PONG_POSITION, _id);
        }
        else {
            self_position = state.GetProperty(PONG_RIGHT_PADDLE, PONG_POSITION, _id);
        }
        see?
        */
        
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


//General flow for main():
//Create system -> register agents -> create window -> run game -> delete agents
//Also, ALWAYS make sure main() has this particular signature. SDL2 requires this. 
//Don't use void main() or int main(). int main(int, char**) is the way to go.
int main(int argc, char **argv)
{
    aig::GameSystem<aig::PongGame> system;
    
    //Since we don't need any subclass details for GameSystem and game classes to use agents,
    //it's a good habit to store the pointer as a base class pointer.
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