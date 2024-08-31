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

    void CreateDrawElement();
    void RenderLoop();

private:
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    [[nodiscard]] static ShaderProgramSource ParseShader(const std::string& path);
    [[nodiscard]] static unsigned int CompileShader(unsigned int type, std::string_view source);
    void CreateVertexArray();
    static void CreateVertexBuffer();
    void CreateIndexBuffer();
    void CreateShaderProgram();
    bool GlLogCall();

    GLFWwindow* window{};
    bool m_initilized {false};
    unsigned int m_vao {0};
    unsigned int m_ibo {0};
    unsigned int m_shader {0};
    int m_uLocation {-1};
};
