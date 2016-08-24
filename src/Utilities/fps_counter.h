#ifndef PEAR_FPS_COUNTER_H
#define PEAR_FPS_COUNTER_H

#include "timer.h"

namespace pear {
	
	class FPSCounter
	{
		double m_Steps[20];
		unsigned int m_StepCounter;
		Timer m_Timer;
		
	public:
		double fps;
		
	public:
		FPSCounter();
		~FPSCounter();
		void countfps();
		void limitfps( unsigned int fps_limit ); // Needs more attention...
	};
	
}

#endif // PEAR_FPS_COUNTER_H