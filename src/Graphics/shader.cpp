#include <iostream>
#include <fstream>
#include "shader.h"

namespace pear {
	
	Shader::Shader()
		: m_Program( 0 ),
		m_NumAttributes( 0 )
	{
	}

	Shader::~Shader()
	{
		if( m_Program != 0 )
			glDeleteProgram( m_Program );
	}

	void Shader::use()
	{
		glUseProgram( m_Program );
		
		for( int i = 0; i < m_NumAttributes; i++ )
		{
			glEnableVertexAttribArray( i );
		}
	}
	void Shader::unuse()
	{
		glUseProgram( 0 );
		
		for( int i = 0; i < m_NumAttributes; i++ )
		{
			glDisableVertexAttribArray( i );
		}
	}
	
	void Shader::addAttribute( const char* attributeName )
	{
		glBindAttribLocation( m_Program, m_NumAttributes++, attributeName );
	}
	
	GLint Shader::getUniformLocation( const char* uniformName )
	{
		return glGetUniformLocation( m_Program, uniformName );
	}
	
	void Shader::setUniform1f( const char* name, float value )
	{
		glUniform1f( getUniformLocation( name ), value );
	}
	
	void Shader::setUniform2f( const char* name, glm::vec2 vector )
	{
		glUniform2f( getUniformLocation( name ), vector.x, vector.y );
	}
	
	void Shader::setUniform3f( const char* name, glm::vec3 vector )
	{
		glUniform3f( getUniformLocation( name ), vector.x, vector.y, vector.z );
	}
	
	void Shader::setUniform4f( const char* name, glm::vec4 vector )
	{
		glUniform4f( getUniformLocation( name ), vector.x, vector.y, vector.z, vector.w );
	}
	
	void Shader::setUniform1i( const char* name, int value )
	{
		glUniform1i( getUniformLocation( name ), value );
	}
	
	void Shader::setUniformMat4( const char* name, const glm::mat4& matrix )
	{
		glUniformMatrix4fv( getUniformLocation( name ), 1, GL_FALSE, &matrix[0][0] );
	}
	
	void Shader::compileShaders( const char* sourcePath )
	{
		m_Program = glCreateProgram();
		
		m_VertexShaderID = glCreateShader( GL_VERTEX_SHADER );
		m_FragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );
		
		std::string path = std::string( "../src/Graphics/Shaders/" ) + sourcePath;
		std::ifstream file( path.c_str() );
		if( file.fail() )
		{
			std::cout << "Failed to open " << sourcePath << std::endl;
		}
		else
		{
			std::string vertexSource = "";
			std::string fragmentSource = "";
			std::string line;
			
			enum class ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER, NO_SHADER } shader_type;
			shader_type = ShaderType::NO_SHADER;
			
			const std::string vertexShaderPrep = "#vertex_shader";
			const std::string fragmentShaderPrep = "#fragment_shader";
			
			while( std::getline( file, line ) )
			{
				bool isItPrepCom = false;
				
				if( line == vertexShaderPrep )
				{
					shader_type = ShaderType::VERTEX_SHADER;
					isItPrepCom = true;
				}
				else if( line == fragmentShaderPrep )
				{
					shader_type = ShaderType::FRAGMENT_SHADER;
					isItPrepCom = true;
				}
				
				if( !isItPrepCom )
				{
					switch( shader_type )
					{
						case ShaderType::VERTEX_SHADER:
						{
							vertexSource += line + "\n";
						} break;
						case ShaderType::FRAGMENT_SHADER:
						{
							fragmentSource += line + "\n";
						} break;
					}
				}
			}
			
			const char* contentsPtr = vertexSource.c_str();
			glShaderSource( m_VertexShaderID, 1, &contentsPtr, NULL );
			glCompileShader( m_VertexShaderID );
			
			GLint success;
			GLchar infoLog[512];
			glGetShaderiv( m_VertexShaderID, GL_COMPILE_STATUS, &success);
			if(!success)
			{
				glGetShaderInfoLog( m_VertexShaderID, 512, NULL, infoLog );
				std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"<< sourcePath << infoLog << std::endl;
			}
			
			contentsPtr = fragmentSource.c_str();
			glShaderSource( m_FragmentShaderID, 1, &contentsPtr, NULL );
			glCompileShader( m_FragmentShaderID );
			
			glGetShaderiv( m_FragmentShaderID, GL_COMPILE_STATUS, &success);
			if(!success)
			{
				glGetShaderInfoLog( m_FragmentShaderID, 512, NULL, infoLog );
				std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"<< sourcePath << infoLog << std::endl;
			}
		}
		file.close();
	}
	
	void Shader::compileShaders( const std::string vertexPath, const std::string fragmentPath )
	{
		m_Program = glCreateProgram();
		
		m_VertexShaderID = glCreateShader( GL_VERTEX_SHADER );
		m_FragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );
		
		compileShader( m_VertexShaderID, vertexPath );
		compileShader( m_FragmentShaderID, fragmentPath );
	}
	
	void Shader::linkShaders()
	{
		GLint success;
		GLchar infoLog[512];
		
		glAttachShader( m_Program, m_VertexShaderID );
		glAttachShader( m_Program, m_FragmentShaderID );
		glLinkProgram( m_Program );
		
		glGetProgramiv( m_Program, GL_LINK_STATUS, &success );
		if( !success )
		{
			glGetProgramInfoLog( m_Program, 512, NULL, infoLog );
			std::cout << "Failed to link shader program!\nError: " << infoLog << std::endl;
		}
		
		glDetachShader( m_Program, m_VertexShaderID );
		glDetachShader( m_Program, m_FragmentShaderID );
		glDeleteShader( m_VertexShaderID );
		glDeleteShader( m_FragmentShaderID );
	}

	void Shader::compileShader( GLuint shader, const std::string filePath )
	{
		std::string path = std::string( "../src/Graphics/Shaders/" ) + filePath;
		std::ifstream file( path.c_str() );
		if( file.fail() )
		{
			std::cout << "Failed to open " + filePath << std::endl;
		}
		else
		{
			std::string content = "";
			std::string line;
			
			while( std::getline( file, line ) )
			{
				content += line + "\n";
			}
			
			const char* contentsPtr = content.c_str();
			glShaderSource( shader, 1, &contentsPtr, NULL );
			glCompileShader( shader );
			
			GLint success;
			GLchar infoLog[512];
			glGetShaderiv( shader, GL_COMPILE_STATUS, &success);
			if(!success)
			{
				glGetShaderInfoLog( shader, 512, NULL, infoLog );
				std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"<< filePath << infoLog << std::endl;
			}
		}
		file.close();
	}
	
}
