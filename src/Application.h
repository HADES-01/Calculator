#include <unordered_map>
#include <string>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "imgui.h"

namespace Calculator{
    class Application {
        public:
        Application() ;
        void Init();
        void Run();
        void Destroy();
        ~Application() ;
        private:
        VkResult m_err;
        GLFWwindow *m_window;
        std::unordered_map<std::string, ImFont*> m_FontMap;
    };
}