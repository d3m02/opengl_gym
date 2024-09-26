#pragma once 

#include <GL/glew.h>

#include <string>
#include <cassert>

#define GlCall(x) GlClearErrors();\
    x;\
    assert(GlLogCall())

bool GlLogCall();
void GlClearErrors();

#ifndef RES_FOLDER
#define RES_FOLDER "";
#endif