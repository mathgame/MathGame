#include <iostream>
#include "UniStream/UniStream.h"
#include "libs.h"
#include <SDL2/SDL.h>

#include "Tools/DebugTools.h"
#include "Tools/Timer.h"

#include "Interpolations/InterpolationBase.h"
#include "Tools/Vector2d.h"
#include "PathIterators/Bezier.h"
#include <math.h>

using namespace std;
using namespace MGTools;

void foo()
{
    Vector2d<double> v(3, 4);
    v *= 1.5f;
    v = v * 2;
    Vector2d<double> v2 = {2, 3};

    v /= v2;
    auto x = v.X();

    auto b = Bezier2d<float>(v, v2, v2, v);
}

void DrawGameObject(SDL_Renderer* renderer, Vector2d<int> pos, const SDL_Color& color)
{
    static int width = 50;
    static int height = 50;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect r;
    r.x = pos.X() - width / 2;
    r.y = pos.Y() - height / 2;
    r.w = width;
    r.h = height;
    SDL_RenderFillRect( renderer, &r );
}


class DummyGO
{
public:
    DummyGO() {};
    void Update(const TimerData& tData)
    {
        color.r = UpdateColorComponent(tData, redInterpolation);
        color.g = UpdateColorComponent(tData, greenInterpolation);
        color.b = UpdateColorComponent(tData, blueInterpolation);

        pos = path.Pos( UpdatePositionInterpolation(tData, positionInterpolation) );
    }

    void Render(SDL_Renderer* renderer)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Rect r;
        r.x = pos.X() - width / 2;
        r.y = pos.Y() - height / 2;
        r.w = width;
        r.h = height;
        SDL_RenderFillRect( renderer, &r );
    }

    int UpdateColorComponent(const TimerData& tData, MGTools::LinearInterpolation<int>& comp)
    {
        comp.Update(tData);
        int val = comp.GetValue();
        int colorVal = val % 256;
        if ( (val / 256) % 2 )
        {
            colorVal = 255 - colorVal;
        }
        return colorVal;
    }

    double UpdatePositionInterpolation(const TimerData& tData, MGTools::LinearInterpolation<double>& pos)
    {
        pos.Update(tData);

        double integralPart, rectPosCoeff = modf(pos.GetValue(), &integralPart);
        int rectDirection = ((int)(integralPart+0.5)) % 2;
        if (rectDirection)
            rectPosCoeff = 1.0 - rectPosCoeff;
        return rectPosCoeff;
    }

    int width;
    int height;
    SDL_Color color;
    Bezier2d<int> path;
    MGTools::LinearInterpolation<double> positionInterpolation;
    MGTools::LinearInterpolation<int> redInterpolation;
    MGTools::LinearInterpolation<int> greenInterpolation;
    MGTools::LinearInterpolation<int> blueInterpolation;
    Vector2d<double> pos;
};


void ReadGameObjects(const TimerData& tData, std::vector<DummyGO>& objects)
{
    DummyGO obj1;
    obj1.width = 12;
    obj1.height = 6;
    obj1.color = { 255, 0, 0, 0};
    obj1.path = Bezier2d<int>({5, 5}, {150, 700}, {400, 10}, {900, 300});
    obj1.positionInterpolation = MGTools::LinearInterpolation<double>(0, 0.2, tData);
    obj1.redInterpolation = MGTools::LinearInterpolation<int>(0, 30, tData);
    obj1.greenInterpolation = MGTools::LinearInterpolation<int>(0, 30, tData);
    obj1.blueInterpolation = MGTools::LinearInterpolation<int>(0, 30, tData);

    objects.push_back(obj1);

    obj1.width = 25;
    obj1.height = 35;
    obj1.color = { 0, 0, 255, 0};
    obj1.path = Bezier2d<int>({5, 200}, {452, 800}, {900, 200});
    obj1.positionInterpolation = MGTools::LinearInterpolation<double>(0, 0.4, tData);
    obj1.redInterpolation = MGTools::LinearInterpolation<int>(0, 50, tData);
    obj1.greenInterpolation = MGTools::LinearInterpolation<int>(0, 10, tData);
    obj1.blueInterpolation = MGTools::LinearInterpolation<int>(0, 10, tData);
    objects.push_back(obj1);

    obj1.width = 45;
    obj1.height = 35;
    obj1.color = { 0, 0, 255, 0};
    obj1.path = Bezier2d<int>({5, 200}, {452, 800}, {900, 200});
    obj1.positionInterpolation = MGTools::LinearInterpolation<double>(0, 0.2, tData);
    obj1.redInterpolation = MGTools::LinearInterpolation<int>(0, 50, tData);
    obj1.greenInterpolation = MGTools::LinearInterpolation<int>(0, 0, tData);
    obj1.blueInterpolation = MGTools::LinearInterpolation<int>(0, 10, tData);
    objects.push_back(obj1);
}


int main()
{
    foo();
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Math Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 720, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool runWindow = true;

    //if (runWindow)
    //ASSERT( "window is blocked");

    MGTools::FrameTimer timer;

    SDL_Rect rBasis;
    rBasis.x = 0;
    rBasis.y = 0;
    rBasis.w = 50;
    rBasis.h = 50;

    auto initBasisTime = timer.GetFrameBasisTime();
    MGTools::LinearInterpolation<Uint32> redColorInterpolation(0, 120.0, initBasisTime);

    std::vector<DummyGO> arr;
    ReadGameObjects(initBasisTime, arr);

    while ( runWindow )
    {
        auto tData = timer.GetFrameBasisTime();

        SDL_Event event;
        while( SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                runWindow = false;
        }

        redColorInterpolation.Update(tData);

        SDL_SetRenderDrawColor(renderer, redColorInterpolation.GetValue() % 256, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (auto& go : arr)
        {
            go.Update(tData);
        }

        for (auto& go : arr)
        {
            go.Render(renderer);
        }


        // Up until now everything was drawn behind the scenes.
        // This will show the new, red contents of the window.
        SDL_RenderPresent(renderer);

        SDL_UpdateWindowSurface( window );
        //SDL_Delay(500);
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}
