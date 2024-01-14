#include "Application.h"
#include "imgui.h"

void Calculator::Application::RenderLayer() {
    m_Calculator.CreateGrid();
    m_Calculator.HandleKeyboardInput();
}

int main() {
    Calculator::Application *app = new Calculator::Application({400, 590, "Calculator"});
    app->Run();
    return 0;
}