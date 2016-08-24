#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

#include <string>
#include <GL/glew.h>

namespace pear {
	
	const int VERTEX_SHADER = 1;
	const int FRAGMENT_SHADER = 2;
	
	class Shader
	{
		GLuint m_Program;
		GLuint m_VertexShaderID;
		GLuint m_FragmentShaderID;
		
		unsigned int m_NumAttributes;
		
	public:
		Shader();
		~Shader();
		void compileShaders( const char* sourcePath );
		void compileShaders( const std::string vertexPath, const std::string fragmentPath );
		void linkShaders();
		
		void use();
		void unuse();
		
		void addAttribute( const char* attributeName );
		
		GLint getUniformLocation( const char* uniformName );
		
		void setUniform1f( const char* name, float value );
		void setUniform2f( const char* name, glm::vec2 vector );
		void setUniform3f( const char* name, glm::vec3 vector );
		void setUniform4f( const char* name, glm::vec4 vector );
		void setUniform1i( const char* name, int value );
		void setUniformMat4( const char* name, const glm::mat4& matrix );
		
		inline GLuint GetProgram() { return m_Program; }
		
	private:
		void compileShader( GLuint shader, const std::string filePath );
	};

}

#endif