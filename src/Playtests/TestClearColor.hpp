#pragma once 

#include <array>
#include "TestBase.hpp"

namespace playtest
{

class TestClearColor : public TestBase
{
public:
    TestClearColor() = default;
    ~TestClearColor() override = default ;

    void OnRender() override;
    void OnImGuiRender() override;

private:
    std::array<float, 4> m_clearColor { 0.4F, 0.3F, 0.6F, 1.F };
};

}