#include "graphics.h"

namespace aig
{
    Graphics::Graphics() 
    {
        SDL_Init(SDL_INIT_VIDEO);
    }

    bool Graphics::CreateWindow(const char *title, unsigned int width, unsigned int height) 
    {
        this->width = width;
        this->height = height;

        _window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (_window == nullptr) 
        {
            return false;
        }

        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        if (_renderer == nullptr) 
        {
            return false;
        }

        SDL_RenderClear(_renderer);

        return true;
    }

    void Graphics::SetDrawColor(Color color) 
    {
        switch(color) 
        {
            case RED:
                SDL_SetRenderDrawColor(_renderer, 0xff, 0, 0, 0xff);
                break;

            case GREEN:
                SDL_SetRenderDrawColor(_renderer, 0, 0xff, 0, 0xff);
                break;

            case BLUE:
                SDL_SetRenderDrawColor(_renderer, 0, 0, 0xff, 0xff);
                break;

            case WHITE:
                SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0xff);
                break;

            case BLACK:
            default:
                SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0xff);
                break;
        }
    }

    //Assumes x and y are [-extent, extent]
    void Graphics::DrawRectangle(double x, double y, double size_x, double size_y) 
    {
        int size_x_actual = (size_x * width) / (2 * _x_extent);
        int size_y_actual = (size_y * height) / (2 * _y_extent);
        int x_actual = ((x + _x_extent) / (2 * _x_extent)) * width - size_x_actual/2;
        int y_actual = ((-y + _y_extent) / (2 * _y_extent)) * height - size_y_actual/2;

        SDL_Rect r {x_actual, y_actual, size_x_actual, size_y_actual};
        SDL_RenderFillRect(_renderer, &r);
    }

    void Graphics::Clear() 
    {
        SDL_RenderClear(_renderer);
    }

    void Graphics::Show() 
    {
        SDL_RenderPresent(_renderer);
    }

    void Graphics::WaitForQuit() 
    {
        SDL_Event e;
        bool is_done = false;

        while (!is_done) 
        {
            while (SDL_PollEvent(&e) != 0) 
            {
                if (e.type == SDL_QUIT) 
                {
                    is_done = true;
                    break;
                }
            }
        }
    }

    Graphics::~Graphics() 
    {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);

        _renderer = nullptr;
        _window = nullptr;

        SDL_Quit();
    }
}