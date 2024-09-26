#pragma once 

namespace playtest
{

class TestBase
{
public:
    TestBase() = default;
    virtual ~TestBase() = default;

    virtual void OnUpdate(float) {}
    virtual void OnRender() {}
    virtual void OnImGuiRender() {}
};

}