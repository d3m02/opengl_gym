#include "TestMenu.hpp"

#include <imgui.h>

namespace playtest 
{

TestMenu::TestMenu(TestBase*& pCurrTest)
    : m_pCurrTest(pCurrTest)
{
    
}

void TestMenu::OnImGuiRender()
{
    for (const auto& [name, test] : m_tests)
    {
        if (ImGui::Button(name.c_str()))
            m_pCurrTest = test();
    }
}
}