#pragma once 

#include "TestBase.hpp"

#include <functional>
#include <unordered_map>
#include <string>
#include <iostream>

namespace playtest
{
    
class TestMenu final : public TestBase
{
public:
    TestMenu(TestBase*& pCurrTest);
    ~TestMenu() override = default;

    template<typename T>
    void RegisterTest(const std::string& name)
    {
        std::cout << "Registering test " << name << '\n';
        m_tests[name] = [](){ return new T(); };
    }

    void OnImGuiRender() override;

private:

    TestBase*& m_pCurrTest;
    std::unordered_map<std::string, std::function<TestBase*()>> m_tests;
};

}