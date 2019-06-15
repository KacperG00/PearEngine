#ifndef PEAR_GRAPHICS_RENDERER2D_H
#define PEAR_GRAPHICS_RENDERER2D_H

#include "PEngine/graphics/renderable2D.h"
#include "PEngine/graphics/shader.h"

namespace pear { namespace graphics {
	
	class Renderer2D
	{
	protected:
		Shader* m_Shader;
		
	public:
		virtual void submit(Renderable2D* renderable) = 0;
		virtual void erase(Renderable2D* renderable) = 0;
		virtual void flush() = 0;
		virtual void bindShader(const char* shaderName) = 0;
	};
	
} }

#endif // PEAR_GRAPHICS_RENDERER_H
