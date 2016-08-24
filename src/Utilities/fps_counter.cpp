#include "fps_counter.h"

#include <SDL2/SDL.h>

#include <iostream>

namespace pear {
	
	FPSCounter::FPSCounter()
		: m_StepCounter( 0 ),
		fps( 0.0f )
	{
		for( int i = 0; i < 20; i++ )
			m_Steps[i] = 0;
		
		m_Timer.start();
	}
	
	FPSCounter::~FPSCounter()
	{
	}
	
	void FPSCounter::countfps()
	{
		if( m_StepCounter < 20 )
		{
			double time = m_Timer.getTime();
			m_Steps[m_StepCounter] = time;
			
			m_StepCounter++;
		}
		else if( m_StepCounter == 20 )
			m_StepCounter = 0;
		
		double average = 0.0f;
		double sum = 0.0f;
		for( int i = 0; i < 20; i++ )
		{
			sum += m_Steps[i];
		}
		average = sum / 20.0f;
		fps = 1.0f / average;
		
		m_Timer.stop();
		m_Timer.start();
	}
	
	void FPSCounter::limitfps( unsigned int fps_limit )
	{
		unsigned int delay = 0;
		double limit = (double)fps_limit;
		
		if( limit < fps )
			delay = (unsigned int)(1000.0f / limit);
		
		SDL_Delay( delay );
	}
	
}
