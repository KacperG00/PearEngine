#ifndef PEAR_RENDERER_H
#define PEAR_RENDERER_H

#include "renderable2D.h"

namespace pear { namespace graphics {
	
	class Renderer2D
	{
	public:
		virtual void submit(Renderable2D* renderable) = 0;
		virtual void flush() = 0;
	};
	
} }

#endif // PEAR_RENDERER_H
