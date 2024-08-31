#pragma once 

#include <GL/glew.h>

#include <cassert>

#define GlCall(x) while (glGetError());\
    x;\
    assert(GlLogCall());

bool GlLogCall();