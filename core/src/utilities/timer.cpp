#include "PEngine/utilities/timer.h"

#include <SDL.h>

namespace pear { namespace utils {
	
	Timer::Timer()
		: started( false ), stopped( true ), paused( false ),
		m_StartTime( 0.0f ), m_CurrentTime( 0.0f ), m_PauseTime( 0.0f ), m_LastPauseTime( 0.0f )
	{
	}
	
	Timer::~Timer()
	{
	}
	
	void Timer::start()
	{
		if( stopped )
		{
			started = true;
			stopped = false;
			if( !paused )
				m_StartTime = getSeconds();
		}
		else
		{
			if( paused )
			{
				paused = false;
				m_PauseTime += ( getSeconds() - m_LastPauseTime );
			}
		}
	}
	
	void Timer::stop()
	{
		started = false;
		stopped = true;
		paused = false;
		m_StartTime = 0.0f;
		m_PauseTime = 0.0f;
	}
	
	void Timer::pause()
	{
		if( started )
		{
			if( !paused )
			{
				paused = true;
				m_LastPauseTime = getSeconds();
			}
		}
	}
	
	double Timer::getTime()
	{
		if( started )
		{
			if( paused )
			{
				m_PauseTime += (getSeconds() - m_LastPauseTime);
				m_LastPauseTime = getSeconds();
			}
			
			m_CurrentTime = getSeconds();
			return (m_CurrentTime - m_StartTime) - m_PauseTime;
		}
		return -1.0f;
	}
	
	double Timer::getSeconds()
	{
		return ((double)SDL_GetTicks() / 1000.0f);
	}
	
} }
