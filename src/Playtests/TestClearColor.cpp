#include "TestClearColor.hpp"

#include <imgui.h>

#include "OGGCommon.hpp"

namespace playtest
{

void TestClearColor::OnRender()
{
    GlCall(glClearColor(m_clearColor[0], m_clearColor[1],
                        m_clearColor[2], m_clearColor[3]));
    GlCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestClearColor::OnImGuiRender()
{
    ImGui::ColorEdit4("Clear Color", m_clearColor.data());
}

}