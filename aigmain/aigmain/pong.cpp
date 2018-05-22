#include "pong.h"

namespace aig
{
    Vector2 aig::PongGameState::GetProperty(const PongObject object, const PongProperty property, const int id) const
    {
        //TODO: Get rid of magic constants.
        if (object >= 0 && object < 7)
        {
            switch (property)
            {
            case PONG_POSITION:
                return _objects[object].position;

            case PONG_BOUNDING_BOX_EXTENT:
                return _objects[object].bounding_box_extent;

            case PONG_VELOCITY:
                return _objects[object].velocity;

            default:
                return Vector2();
            }
        }
        else
        {
            return Vector2();
        }
    }

    PongGame::PongGame(const std::vector<IAgent<GameT>*>& agents, Graphics * graphics)
    {
        //TODO: Indicate failure somehow. Ugh, could really use a Maybe monad.
        if (agents.size() >= 2)
        {
            _left_player = agents[0];
            _right_player = agents[1];

            _observation_target.AddObserver(&(_left_player->observer));
            _observation_target.AddObserver(&(_right_player->observer));
            _observation_target.AddObserver(&_observer);
        }

        _graphics = graphics;
    }

    void PongGame::Initialize()
    {
        //Hardcoding ftw
        _game_state._objects[PONG_LEFT_PADDLE].position = Vector2(-600, 0);
        _game_state._objects[PONG_RIGHT_PADDLE].position = Vector2(600, 0);
        _game_state._objects[PONG_BALL].position = Vector2(0, 0);
        _game_state._objects[PONG_TOP_BOUNDARY].position = Vector2(0, 800);
        _game_state._objects[PONG_BOTTOM_BOUNDARY].position = Vector2(0, -800);
        _game_state._objects[PONG_LEFT_BOUNDARY].position = Vector2(-800, 0);
        _game_state._objects[PONG_RIGHT_BOUNDARY].position = Vector2(800, 0);

        _game_state._objects[PONG_LEFT_PADDLE].bounding_box_extent = Vector2(20, 100);
        _game_state._objects[PONG_RIGHT_PADDLE].bounding_box_extent = Vector2(20, 100);
        _game_state._objects[PONG_BALL].bounding_box_extent = Vector2(20, 20);
        _game_state._objects[PONG_TOP_BOUNDARY].bounding_box_extent = Vector2(1600, 20);
        _game_state._objects[PONG_BOTTOM_BOUNDARY].bounding_box_extent = Vector2(1600, 20);
        _game_state._objects[PONG_LEFT_BOUNDARY].bounding_box_extent = Vector2(20, 1600);
        _game_state._objects[PONG_RIGHT_BOUNDARY].bounding_box_extent = Vector2(20, 1600);

        _game_state._objects[PONG_BALL].velocity = Vector2(PONG_NORM_SPEED, PONG_NORM_SPEED);
    }

    void PongGame::PreProcess()
    {
        //Handle events
        //TODO: Refactor to remove state changes from this code.
        while (_observer.EventsAvailable())
        {
            auto event = _observer.GetEvent();

            if (event.action == PONG_HIT)
            {
                const auto target = event.objects[1];
                if (target == PONG_LEFT_PADDLE || target == PONG_RIGHT_PADDLE)
                {
                    _game_state._objects[PONG_BALL].velocity.x *= -1;
                }
                else if (target == PONG_TOP_BOUNDARY || target == PONG_BOTTOM_BOUNDARY)
                {
                    _game_state._objects[PONG_BALL].velocity.y *= -1;
                }
            } 
            else if (event.action == PONG_GAME_OVER)
            {
                _has_ended = true;
            }

            std::cout << "[Event] Action: " << event.action << ", Object1: " << event.objects[0] << ", Object2: " << event.objects[1] << "\n";
        }
    }

    void PongGame::RunAi(double elapsed_time)
    {
        _left_command = _left_player->Decide(_game_state, elapsed_time);
        _right_command = _right_player->Decide(_game_state, elapsed_time);
    }

    void PongGame::UpdateState(double elapsed_time)
    {
        //TODO: Get rid of magic constants, find a more elegant way to do this.
        CommandT command = _left_command;
        for (int i = 0; i < 2; i++)
        {
            if (i == 1)
                command = _right_command;

            switch (command)
            {
            case PONG_GO_UP:
                _game_state._objects[i].velocity = Vector2(0, PONG_NORM_SPEED);
                break;

            case PONG_GO_DOWN:
                _game_state._objects[i].velocity = Vector2(0, -PONG_NORM_SPEED);
                break;

            case PONG_STOP:
                _game_state._objects[i].velocity = Vector2(0, 0);
                break;

            case PONG_DO_NOTHING:
            default:
                break;
            }
        }

        //Move all the movable objects. 
        //In a proper impl this would be a scene graph (technically it still is)
        Physics::Move(&(_game_state._objects[PONG_LEFT_PADDLE]), elapsed_time);
        Physics::Move(&(_game_state._objects[PONG_RIGHT_PADDLE]), elapsed_time);
        Physics::Move(&(_game_state._objects[PONG_BALL]), elapsed_time);

        //Check and fire collision events
        //TODO: Refactor into physics processing class/method.
        //TODO: use a spatial data structure instead of a loop.
        const auto& ball = _game_state._objects[PONG_BALL];
        for (int i = 0; i < 7; i++)
        {
            if (i != PONG_BALL)
            {
                if (Physics::IsBoundingBoxColliding(ball, _game_state._objects[i]))
                {
                    if (i < 5)
                    {
                        _observation_target.Broadcast(PongEvent{ PONG_HIT, {PONG_BALL, PongObject(i)} });
                    }
                    else
                    {
                        _observation_target.Broadcast(PongEvent{ PONG_GAME_OVER, {PONG_BALL, PongObject(i)} });
                    }
                }
            }
        }
    }
    void PongGame::Render()
    {
        _graphics->SetDrawColor(BLACK);
        _graphics->Clear();
        
        //Draw all objects in red. Because I'm a programmer, not an artist.
        //TODO: Refactor to remove magic constants.
        _graphics->SetDrawColor(RED);
        for (int i = 0; i < 7; i++)
        {
            _graphics->DrawRectangle(_game_state._objects[i].position.x, _game_state._objects[i].position.y
                , _game_state._objects[i].bounding_box_extent.x, _game_state._objects[i].bounding_box_extent.y);
        }
        _graphics->Show();
    }
    bool PongGame::HasEnded()
    {
        return _has_ended;
    }
}