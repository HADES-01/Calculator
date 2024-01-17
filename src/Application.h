#include <unordered_map>
#include <string>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "imgui.h"
#include <vector>
#include "Calculator/Calculator.cpp"

namespace Calculator
{
    struct ApplicationSpec
    {
        int Width = 1280;
        int Height = 720;
        std::string Name = "Calculator";
    };

    class Application
    {
    public:
        Application(const ApplicationSpec &applicationSpecification = ApplicationSpec());
        void Init();
        void Run();
        void Destroy();
        void RenderLayer();
        ~Application();
        void UI_DrawTitlebar(float& outTitlebarHeight);

    private:
        bool m_Running;
        ApplicationSpec m_Specification;
        VkResult m_Err;
        GLFWwindow *m_Window;
        CalculatorScreen m_Calculator; 
        std::unordered_map<std::string, ImFont *> m_FontMap;
    };
}