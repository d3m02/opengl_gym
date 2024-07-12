#include <string>
#include <string_view>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGlGym 
{
public:
    OpenGlGym() = default;
    ~OpenGlGym(); 

    [[nodiscard]] bool Init(); 
    [[nodiscard]] static unsigned int CreateShader(const std::string& path);

    void CreateBuffer() const;
    void RenderLoop();   

private:
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    [[nodiscard]] static ShaderProgramSource ParseShader(const std::string& path);
    [[nodiscard]] static unsigned int CompileShader(unsigned int type, std::string_view source); 

    GLFWwindow* window{};
    bool m_initilized {false};
};
