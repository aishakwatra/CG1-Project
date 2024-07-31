#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "DrawFrame.h"
using namespace std;


// global data (ugh)
int width = 700, height = 700;
const char* name = "DT284 Final Project";
double time_last;
Raster* raster;
Raster::byte* frame_buffer;
int frame_count;
double frame_time;
int camera_number;
bool should_close = false;
SDL_Window* window;


void Init(void) {
    time_last = float(SDL_GetTicks() / 1000.0f);
    frame_buffer = new Raster::byte[3 * width * height];
    raster = new Raster(frame_buffer, width, height, 3 * width);
    InitFrame(width, height);
    frame_count = 0;
    frame_time = 0;
    camera_number = 0;
}


void draw(void) {
    // compute the time elapsed since the last call to 'Draw' (in seconds)
    double t = double(SDL_GetTicks() / 1000.0f);
    double dt = (t - time_last);
    time_last = t;

    // frame rate
    ++frame_count;
    frame_time += dt;
    if (frame_time >= 0.5) {
        double fps = frame_count / frame_time;
        frame_count = 0;
        frame_time = 0;
        stringstream ss;
        ss << name << " [fps=" << int(fps) << "]";
        SDL_SetWindowTitle(window, ss.str().c_str());
    }

    DrawFrame(*raster, dt, camera_number);
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, frame_buffer);
}

void key_pressed(SDL_Keycode keycode) {
    if (keycode == SDLK_ESCAPE) {
        should_close = true;
    }
    switch (keycode) {
    case '\x1b':
        exit(0);
        break;
    case ' ':
        camera_number = (camera_number == 0 ? 1 : 0);
        break;
    }
}


int main(int argc, char* argv[]) {

    // SDL: initialize and create a window
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    Init();
    //// animation loop
    while (!should_close) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                should_close = true;
                break;
            case SDL_KEYDOWN:
                key_pressed(event.key.keysym.sym);
                break;
            }
        }
        draw();
        SDL_GL_SwapWindow(window);
    }

    // clean up
    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}

