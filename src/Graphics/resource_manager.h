#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <GL/glew.h>

#include <map>

namespace pear {
	
	enum class FileExtention { NONE, PNG, JPEG, BMP };
	
	class ResourceManager
	{
		static std::map <std::string, GLuint> m_Textures;
		static GLuint m_TextureCount;
		
	public:
		static void cleanManager();
		static void addTexture( const char* filename );
		
		inline static const GLuint& getTexture( const char* texture_name ) { return m_Textures[texture_name]; }
		inline static GLuint getTextureCount() { return m_TextureCount; }
		
	private:
		static GLuint loadTexture( const char* filename );
		static FileExtention getFileExtention( const char* filename );
	};
	
}

#endif // RESOURCE_MANAGER_H
