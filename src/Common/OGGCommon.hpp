#pragma once 

#include <GL/glew.h>

#include <string>
#include <cassert>
#include <iostream>

#define GlCall(x) GlClearErrors();\
    x;\
    assert(GlLogCall())

#define LogInfo(x) std::cout << "[info]\t" << __PRETTY_FUNCTION__ << ": " << x << "\n"
bool GlLogCall();
void GlClearErrors();

#ifndef RES_FOLDER
#define RES_FOLDER "";
#endif