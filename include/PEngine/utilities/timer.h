#ifndef PEAR_UTILITIES_TIMER_H
#define PEAR_UTILITIES_TIMER_H

namespace pear { namespace utils {
	
	class Timer
	{
		double m_StartTime;
		double m_PauseTime;
		double m_LastPauseTime;
		double m_CurrentTime;
		
		bool started;
		bool stopped;
		bool paused;
		
	public:
		Timer();
		~Timer();
		void start();
		void stop();
		void pause();
		double getTime();
	
	private:
		double getSeconds();
	};
	
} }

#endif // PEAR_UTILITIES_TIMER_H
