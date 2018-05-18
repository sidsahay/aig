#include "dummy.h"

double aig::DummyGameState::GetProperty(const std::string & prop_name, const int id) const
{
    if (prop_name == "x_position")
    {
        return _x_position;
    }
    else
    {
        return 0.0;
    }
}

aig::DummyGame::DummyGame(const std::vector<IAgent*>& agents, Graphics * graphics)
{
    if (agents.size() > 0)
    {
        _player = agents[0];
    }

    _graphics = graphics;
}

void aig::DummyGame::Initialize()
{
    _game_state._x_velocity = 100.;
}

void aig::DummyGame::RunAi(double elapsed_time)
{
    _command = _player->Decide(_game_state, elapsed_time);
}

void aig::DummyGame::UpdateState(double elapsed_time)
{
    switch (_command)
    {
    case DUMMY_GO_LEFT:
        _game_state._x_velocity = -100.;
        break;

    case DUMMY_GO_RIGHT:
        _game_state._x_velocity = 100.;
        break;

    default:
        break;
    }

    _game_state._x_position += _game_state._x_velocity * elapsed_time;
}

void aig::DummyGame::Render()
{
    _graphics->SetDrawColor(BLACK);
    _graphics->Clear();
    _graphics->SetDrawColor(RED);
    _graphics->DrawRectangle(_game_state._x_position, 0., 20., 20.);
    _graphics->Show();
}

bool aig::DummyGame::HasEnded()
{
    return false; //Infinite game loop. 
}
