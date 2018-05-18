#include "dummy.h"

class DummyAgent : public aig::IAgent
{
    // Inherited via IAgent
    virtual int Decide(const aig::IGameState & state, const double elapsed_time) override
    {
        double x_position = state.GetProperty("x_position", _id);

        if (x_position < -800.)
        {
            return aig::DUMMY_GO_RIGHT;
        }
        else if (x_position > 800.)
        {
            return aig::DUMMY_GO_LEFT;
        }
        else
        {
            return aig::DUMMY_DO_NOTHING;
        }
    }
};

int main(int argc, char **argv)
{
    aig::GameSystem<aig::DummyGame> system;
    
    aig::IAgent* my_agent = new DummyAgent;
    system.RegisterAgent(my_agent);

    system.CreateGameWindow("Dummy Game", 600, 600);
    system.RunGame();


    return 0;
}