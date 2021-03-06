#ifndef PEAR_GRAPHICS_SIMPLESPRITERENDERER_H
#define PEAR_GRAPHICS_SIMPLESPRITERENDERER_H

#include "PEngine/graphics/renderer2D.h"

#include "PEngine/graphics/sprite.h"
#include "PEngine/graphics/shader.h"

#include <vector>
#include <glm/glm.hpp>

namespace pear { namespace graphics {
	
	const unsigned int MAX_SPRITES = 10000;
	const unsigned long int MAX_VERTICES = 4 * MAX_SPRITES;
	const unsigned long int MAX_ELEMENTS = 6 * MAX_SPRITES;
	const unsigned long int MAX_SIZE_OF_SPRITES = sizeof( Vertex ) * MAX_VERTICES;
	
	const unsigned int TEXTURE_ARRAY_SIZE16 = 16;
	const unsigned int TEXTURE_ARRAY_SIZE32 = 32;
	const unsigned int TEXTURE_ARRAY_SIZE = TEXTURE_ARRAY_SIZE32;
	
	class StaticSpriteRenderer : public Renderer2D
	{
		std::vector<Sprite*> m_Sprites;
		
		std::vector<Sprite*> m_RenderedSprites;
		unsigned int m_TextureArray[TEXTURE_ARRAY_SIZE32];
		unsigned int m_GreatestTextureID;
		
		Shader m_Shader;
		GLuint m_VBO;
		GLuint m_IBO;
		
		bool everySpriteIsDrawn;
		bool areSpritesWithoutTexturesDrawn;
		
	public:
		StaticSpriteRenderer();
		~StaticSpriteRenderer();
		void submit( Renderable2D* renderable ) override;
		void erase( Renderable2D* renderable ) override;
		void flush() override;
		void bindShader(const char* shaderName) override;
		void sortSpritesByTextureID();
		
	private:
		void initShaders();
		void setUpVBO();
		void bindTextures();
		void loadTextures();
		void loadSpritesToRender();
		void loadPartitionOfSprites();
		void sendDataToGPU();
		
		void clearTextureArray();
		bool swapSprites( unsigned int key1, unsigned int key2 );
	};
	
} }

#endif // PEAR_GRAPHICS_SIMPLESPRITERENDERER_H
