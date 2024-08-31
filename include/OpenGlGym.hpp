#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGlGym 
{
public:
    OpenGlGym() = default;
    ~OpenGlGym(); 

    [[nodiscard]] bool Init(); 

    void Run();

private:
    GLFWwindow* pWindow{};
    bool m_initilized {false};
};
