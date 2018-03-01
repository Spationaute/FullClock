
#if __linux__
	#include <Fl/Fl.H>
	#include <Fl/Fl_Widget.H>
	#include <Fl/fl_draw.H> 
#endif
#if __MINGW32__
	#include <FL/Fl.H>
	#include <FL/Fl_Widget.H>
	#include <FL/fl_draw.H> 
#endif
#ifndef CLOCKGAUGE_HPP
#define CLOCKGAUGE_HPP
#define toRAD(x) 0.017453292519943295*x


#include <math.h>



class ClockGauge : public Fl_Widget
{
	public:
		ClockGauge(int x, int y,int w, int h);
		~ClockGauge();
		
		void set_time(int h,int m,int s);
		void set_message(char*ptomess);
		void set_line_size(int size);

		void draw();

	private:
		int hour;
		int min;
		int sec;
		int line_size;

		bool reelstep;
		char* message;
};

#endif