#include "line.hpp"


namespace cg {

	void Line::_render()
	{
		if (vertices.empty())
			return; // A linha deve ter pelo menos 2 v�rtices (a posi��o do item conta como 1 v�rtice)
		GLdebug{
			glBegin(GL_LINE_STRIP);
				glColor3f(color.r, color.g, color.b);
				glVertex2f(position.x, position.y);
				for (auto& vertice : vertices)
					glVertex2f(vertice.x, vertice.y);
			glEnd();
		}
	}

}