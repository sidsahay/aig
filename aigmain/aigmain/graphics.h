#pragma once

//Heck yeah, jugaad ftw
//Fixes SDL.h not found on Linux.
#ifdef _WIN32
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

namespace aig
{
    enum Color 
    {
        RED,
        GREEN,
        BLUE,
        WHITE,
        BLACK
    };

    class Graphics 
    {
        public:
        Graphics();

        bool CreateWindow(const char *title, unsigned int width, unsigned int height);
        void SetDrawColor(Color color);

        void DrawRectangle(double x, double y, double size_x, double size_y);

        void Clear();
        void Show();

        void WaitForQuit();

        ~Graphics();

        unsigned int width;
        unsigned int height;

        private:
        SDL_Window *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;

        double _x_extent = 1000.;
        double _y_extent = 1000;
    };
}