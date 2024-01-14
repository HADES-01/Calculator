#include "imgui.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "CalculatorView.cpp"

namespace Calculator
{
    static std::unordered_map<std::string, ImFont *> m_FontMap;
    typedef std::pair<std::string, ImGuiKey> KEY;
    static ImColor DARK_BUTTON(50, 50, 50);
    static ImColor LIGHT_BUTTON(60, 60, 61);
    static std::vector<KEY> NUM_KEYS = std::vector<KEY>({
        {"0", ImGuiKey_Keypad0},
        {"1", ImGuiKey_Keypad1},
        {"2", ImGuiKey_Keypad2},
        {"3", ImGuiKey_Keypad3},
        {"4", ImGuiKey_Keypad4},
        {"5", ImGuiKey_Keypad5},
        {"6", ImGuiKey_Keypad6},
        {"7", ImGuiKey_Keypad7},
        {"8", ImGuiKey_Keypad8},
        {"9", ImGuiKey_Keypad9},
    });

    static std::vector<KEY> SPECIAL_KEYS = std::vector<KEY>({
        {"-", ImGuiKey_KeypadSubtract},
        {"+", ImGuiKey_KeypadAdd},
        {"*", ImGuiKey_KeypadMultiply},
        {"/", ImGuiKey_KeypadDivide},
        {".", ImGuiKey_KeypadDecimal},
        {"^", ImGuiKey_Period},
        {"=", ImGuiKey_KeypadEnter},
    });

    class CalculatorScreen
    {
        CalculatorData m_Calc;
        int m_GridSize;
        std::unordered_map<std::string, bool> m_Focused;
        ImDrawList *m_DrawList;
        double time;

        void createButtons(KEY key, ImVec2 topLeft, bool focused, bool dark)
        {
            ImVec2 bottomRight({topLeft.x + m_GridSize, topLeft.y + m_GridSize});
            topLeft.x += 5;
            topLeft.y += 5;
            ImVec2 mousePos = ImGui::GetMousePos();
            if (focused || (mousePos.x > topLeft.x && mousePos.x < bottomRight.x && mousePos.y > topLeft.y && mousePos.y < bottomRight.y))
            {
                m_DrawList->AddRectFilled(topLeft, bottomRight, (dark ? DARK_BUTTON : LIGHT_BUTTON), 10);
                if(ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
                    if(key.first[0] >= '0' && key.first[0] <= '9')
                        m_Calc.OnNumKeyPressed(key.first);
                    else m_Calc.OnSpecialKeyPressed(key.first);
                }
            }
            else
            {
                m_DrawList->AddRectFilled(topLeft, bottomRight, (dark ? LIGHT_BUTTON : DARK_BUTTON), 10);
            }
            int length = bottomRight.x - topLeft.x, height = bottomRight.y - topLeft.y;
            m_DrawList->AddText(ImVec2(topLeft.x + length / 2 - 10, topLeft.y + height / 2 - 20), ImColor(255, 255, 255), key.first.c_str());
        }

    public:
        CalculatorScreen() : m_GridSize(99), m_Calc()
        {
            time = 0;
        }

        void CreateGrid()
        {
            m_DrawList = ImGui::GetBackgroundDrawList();
            ImVec2 pos1 = ImGui::GetMainViewport()->Pos;
            ImVec2 region = ImGui::GetMainViewport()->Size;

            ImVec2 text_pos = pos1;
            text_pos.x += 10;
            text_pos.y += region.y - m_GridSize * 5 - 30 ;
            m_DrawList->AddText(
                text_pos,
                ImColor(210, 210, 210),
                m_Calc.GetExpression().c_str());

            m_DrawList->AddText(
                ImGui::GetFont(), 60,
                ImVec2(text_pos.x , text_pos.y + 40),
                ImColor(255, 255, 255),
                m_Calc.GetOperand2().c_str(), nullptr, pos1.x + region.x);

            ImVec2 grid_pos = pos1;
            grid_pos.y += region.y - m_GridSize * 4 - 5;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    KEY key = NUM_KEYS[i + j * 3 + 1];
                    createButtons(
                        key,
                        ImVec2(grid_pos.x + i * m_GridSize, grid_pos.y + j * m_GridSize),
                        m_Focused[key.first], true);
                }
            }

            for (int i = 0; i < 4; i++)
            {
                KEY key = SPECIAL_KEYS[i];
                createButtons(
                    key,
                    ImVec2(grid_pos.x + 3 * m_GridSize, grid_pos.y + i * m_GridSize),
                    m_Focused[key.first],
                    false);
            }

            createButtons(
                NUM_KEYS[0],
                ImVec2(grid_pos.x + m_GridSize, grid_pos.y + m_GridSize * 3),
                m_Focused[NUM_KEYS[0].first],
                true);

            createButtons(
                SPECIAL_KEYS[4],
                ImVec2(grid_pos.x, grid_pos.y + m_GridSize * 3),
                m_Focused[SPECIAL_KEYS[4].first],
                false);

            createButtons(
                SPECIAL_KEYS[5],
                ImVec2(grid_pos.x + m_GridSize * 2, grid_pos.y + m_GridSize * 3),
                m_Focused[SPECIAL_KEYS[5].first],
                false);
        }

        void HandleKeyboardInput()
        {
            // HANDLE NUM KEYS
            for (auto a : NUM_KEYS)
            {
                if (ImGui::IsKeyDown(a.second))
                    m_Focused[a.first] = true;

                if (ImGui::IsKeyReleased(a.second))
                {
                    m_Calc.OnNumKeyPressed(a.first);
                    m_Focused[a.first] = false;
                }
            }

            // HANDLE SPECIAL KEYS
            for (auto a : SPECIAL_KEYS)
            {
                if (ImGui::IsKeyDown(a.second))
                    m_Focused[a.first] = true;

                if (ImGui::IsKeyReleased(a.second))
                {
                    m_Calc.OnSpecialKeyPressed(a.first);
                    m_Focused[a.first] = false;
                }
            }

            // HANDLE BACKSPACE
            if (ImGui::IsKeyReleased(ImGuiKey_Backspace))
            {
                m_Calc.OnBackspacePressed();
            }

            // HANDLE ESCAPE
            if (ImGui::IsKeyReleased(ImGuiKey_Escape))
            {
                m_Calc.Reset();
            }
        }
    };
}