#include "tool_box.hpp"

#include "canvas.hpp"

#include "canvas_itens/point.hpp"
#include "canvas_itens/line.hpp"

#include "tools/point_tool.hpp"
#include "tools/line_tool.hpp"


namespace cg {

    // Declare as ferramentas aqui.


    // Passe as ferramentas para o array (lembre-se de alterar o tamanho dele em N_PRIMITIVES).
    ToolBox::ToolBox() {
        static PointTool pointTool{ *this };
        static LineTool lineTool{ *this };
        tools = { (Painter*)&pointTool, (Painter*)&lineTool };
    }

    void ToolBox::addCanvas(Canvas* canvas_ptr) {
        assert_err(canvas == nullptr, "Canvas already added.");
        canvas = canvas_ptr;
    }

    void ToolBox::_render()
    {
        if (currentPrimitive >= N_PRIMITIVES)
            return;
        tools[currentPrimitive]->_render();
    }

    void ToolBox::captureInput(io::MouseMove input_event)
    {
        if (currentPrimitive >= N_PRIMITIVES)
            return;
        if (currentTool != currentPrimitive) {
            // TODO -> update using tool
            currentTool = currentPrimitive;
        }

        tools[currentPrimitive]->_input(input_event);
    }

    void ToolBox::captureInput(io::MouseDrag input_event)
    {
        if (currentPrimitive >= N_PRIMITIVES)
            return;
        if (currentTool != currentPrimitive) {
            // TODO -> update using tool
            currentTool = currentPrimitive;
        }

        tools[currentPrimitive]->_input(input_event);
    }

    void ToolBox::captureInput(io::MouseLeftButtonPressed input_event)
    {
        if (currentPrimitive >= N_PRIMITIVES)
            return;
        if (currentTool != currentPrimitive) {
            // TODO -> update using tool
            currentTool = currentPrimitive;
        }

        tools[currentPrimitive]->_input(input_event);
    }

    void ToolBox::captureInput(io::MouseLeftButtonReleased input_event)
    {
        if (currentPrimitive >= N_PRIMITIVES)
            return;
        if (currentTool != currentPrimitive) {
            // TODO -> update using tool
            currentTool = currentPrimitive;
        }

        tools[currentPrimitive]->_input(input_event);
    }

} // namespace cg