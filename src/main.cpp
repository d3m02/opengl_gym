#include "OpenGlGym.hpp"

int main()
{
    OpenGlGym ogg;
    if (!ogg.Init())
        return -1;

    ogg.CreateDrawElement();
    ogg.RenderLoop();
    return 0;
}
