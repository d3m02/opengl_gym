#pragma once 

#include <GL/glew.h>

#include <cassert>

#define GlCall(x) GlClearErrors();\
    x;\
    assert(GlLogCall());

bool GlLogCall();
void GlClearErrors();