#pragma once 

#include <array>
#include "TestBase.hpp"

namespace playtest
{

class TestClearColor : public TestBase
{
public:
    TestClearColor();
    ~TestClearColor() override = default ;

    void OnRender() override;
    void OnImGuiRender() override;

private:
    std::array<float, 4> m_clearColor;
};

}