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
    //You can add your own colors by modifying this enum and Graphics::SetDrawColor().
    enum Color 
    {
        RED,
        GREEN,
        BLUE,
        WHITE,
        BLACK
    };

    //Wrapper for SDL2 graphcis library.
    //IMPORTANT: All units EXCEPT for those passed to CreateWindow() are in terms of game coordinates.
    //Game coordinates range from -x_extent to +x_extent and -y_extent to +y_extent.
    class Graphics 
    {
        public:
        Graphics();

        bool CreateWindow(const char *title, unsigned int width, unsigned int height);
        void SetDrawColor(Color color);

        void DrawRectangle(double x, double y, double size_x, double size_y);

        void Clear();
        void Show();

        //Runs basic SDL event loop so that the X button is active (and Alt+F4 as well).
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