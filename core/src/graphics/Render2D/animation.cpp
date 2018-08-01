#include "PEngine/graphics/animation.h"

#include "PEngine/app/resource_manager.h"
#include "PEngine/string_constants.h"
#include "PEngine/utilities/string_manipulations.h"

#include <iostream>
#include <fstream>
#include <string>

namespace pear { namespace graphics {
	
	SS_Animation::SS_Animation(const char* texture_name, int nosh, int nosv, int first_sprite, int last_sprite)
		: m_NumOfCurrFrame(0)
	{
		m_NormPos = loadDataReg( texture_name, nosh, nosv, first_sprite, last_sprite );
		m_CountOfFrames = m_NormPos.size();
	}
	
	SS_Animation::SS_Animation(const char* texture_name, const char* animation_name)
		: m_Name( animation_name ),
		m_NumOfCurrFrame(0)
	{
		std::vector<glm::vec4> pixPos = loadDataWithSP( texture_name, animation_name );
		m_NormPos = normalizePositions( texture_name, pixPos );
		m_CountOfFrames = m_NormPos.size();
	}
	
	SS_Animation::~SS_Animation()
	{
	}
	
	void SS_Animation::resetAni()
	{
		m_NumOfCurrFrame = 0;
	}
	
	glm::vec4* SS_Animation::getFrame()
	{
		m_CurrFrame = &m_NormPos[m_NumOfCurrFrame];
		
		m_NumOfCurrFrame++;
		if( !(m_NumOfCurrFrame < m_CountOfFrames) )
		{
			m_NumOfCurrFrame = 0;
		}
		
		return m_CurrFrame;
	}
	
	glm::vec4* SS_Animation::getFrame(unsigned int frame_number)
	{
		if( m_NormPos.size() > frame_number )
			return &m_NormPos[frame_number];
		else
		{
			printf("SS_Animation: Non-existent frame has been called\n");
			return nullptr;
		}
	}
	
	const char* SS_Animation::getName()
	{
		return m_Name;
	}
	
	std::vector<glm::vec4> SS_Animation::loadDataReg(const char* texture_name, int nosh, int nosv, int first_frame, int last_frame)
	{
		int texture_width = ResourceManager::getTexture(texture_name)->width;
		int texture_height = ResourceManager::getTexture(texture_name)->height;
		
		float sprite_width = ((float)texture_width) / ((float)nosh) / (float)texture_width;
		float sprite_height = ((float)texture_height) / ((float)nosv) / (float)texture_height;
		
		std::vector<glm::vec4> positions;
		
		float sprite_pos_x = first_frame * sprite_width;
		float sprite_pos_y = ((float)(first_frame / nosh)) * sprite_height;
		
		for( int i = first_frame; i <= last_frame; i++ )
		{
			if( sprite_pos_x + sprite_width <= 1.0f )
			{
				positions.push_back( glm::vec4( sprite_pos_x, sprite_pos_y, sprite_width, sprite_height ) );
				
				sprite_pos_x += sprite_width;
			}
			else
			{
				sprite_pos_x = 0.0f;
				sprite_pos_y += sprite_height;
			}
		}
		
		return positions;
	}
	
	std::vector<glm::vec4> SS_Animation::loadDataWithSP(const char* filename, const char* animationName)
	{
		bool success = false;
		
		std::vector<glm::vec4> rVector;
		
		const char* path = std::string(std::string(paths_from_build::TEXTURES) + filename).c_str();
		path = utils::changeFileExtention( path, "sp" );
		std::ifstream file( path );
		if( file.fail() )
		{
			std::cout << "Failed to open " << path << std::endl;
		}
		else
		{
			std::string currLine = "";
			
			int number = 1;
			
			bool animationBound = false;
			
			while( std::getline( file, currLine ) )
			{
				currLine += '\n';
				
				if( animationBound )
				{
					glm::vec4 positions;
					
					bool endOfLineFound = false;
					unsigned int commaPos = 0;
					
					unsigned int countOfNumbers = 0;
					
					int i = 0;
					while( !endOfLineFound )
					{
						if( currLine[i] == ',' || currLine[i] == '\n' || currLine[i] == ';' )
						{
							std::string fnumber = "";
							for( int j = commaPos; j < i; j++ )
							{
								fnumber += currLine[j];
							}
							
							// traslating string to float and packing them to glm::vec4 positions
							switch( countOfNumbers % 4 )
							{
								case 0:
								{
									countOfNumbers++;
									positions.x = std::stof( fnumber );
								} break;
								case 1:
								{
									countOfNumbers++;
									positions.y = std::stof( fnumber );
								} break;
								case 2:
								{
									countOfNumbers++;
									positions.z = std::stof( fnumber );
								} break;
								case 3:
								{
									countOfNumbers = 0;
									positions.w = std::stof( fnumber );
									rVector.push_back( glm::vec4( positions.x, positions.y, positions.z, positions.w ) );
								} break;
							}
							
							commaPos = i + 1;
							
							if( currLine[i] == '\n' )
								endOfLineFound = true;
						
							if( currLine[i] == ';' )
							{
								animationBound = false;
								endOfLineFound = true;
							}
						}
						
						i++;
					}
				}
				
				if( utils::findWord( currLine.c_str(), std::string( std::string( "animation " ) + animationName + ":\n" ).c_str() ) >= 0 )
				{
					animationBound = true;
					success = true;
				}
			}
		}
		file.close();
		
		if( !success )
			std::cout << "Animation " << animationName << " is not found\n";
		
		return rVector;
	}
	
	std::vector<glm::vec4> SS_Animation::normalizePositions(const char* texture_name, const std::vector<glm::vec4>& inVector)
	{
		int texture_width = ResourceManager::getTexture( texture_name )->width;
		int texture_height = ResourceManager::getTexture( texture_name )->height;
		
		std::vector<glm::vec4> normalizedPos;
		
		for( int i = 0; i < inVector.size(); i++ )
		{
			float width = inVector[i].z - inVector[i].x;
			float height = inVector[i].w - inVector[i].y;
			
			normalizedPos.push_back( glm::vec4( inVector[i].x / texture_width, inVector[i].y / texture_height,
									width / texture_width, height / texture_height ) );
		}
		
		return normalizedPos;
	}
	
} }
