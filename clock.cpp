#include <stdio.h>

#if __MINGW32__
	#include <FL/Fl.H>
	#include <FL/Fl_Window.H>
	#include <FL/Fl_Box.H>
#endif

#if __linux__
	#include <Fl/Fl.H>
	#include <Fl/Fl_Window.H>
	#include <Fl/Fl_Box.H>
#endif

#include <unistd.h>
#include <time.h>
#include "clockgauge.hpp"

unsigned int hour,min,sec,tz;

void printHelp(){
	printf("Usage: ./clock [-z timezone]\n");
	printf("\t-h\t\t\tPrint Help\n");
	printf("\t-z tz\t\t\tSet Timezone\n");
	printf("\t-f RRGGBB\t\tForeground color in the hexadecimal form RRGGBB \n");
	printf("\t-b RRGGBB\t\tBackground color in the hexadecimal form RRGGBB \n");
	printf("\t-m \"string\"\t\tUpper clock string \n");
	printf("\t-l\t\t\tSet line width\n");
	printf("\t-n\t\t\tno border \n");
}

static void uptime(){
	time_t t;
	tm time_struct;
	time(&t);

	#if __MINGW32__
		gmtime_s(&time_struct,&t);
	#else
		gmtime_r(&t,&time_struct);
	#endif
	int htz=time_struct.tm_hour+tz;

	hour=htz<24?htz:htz-24;
	hour=htz>=0?htz:24+htz;

	min=time_struct.tm_min;
	sec=time_struct.tm_sec;
}

int charHextoInt(char to_read){
	if(to_read>=0x30 && to_read<=0x39){
		return (int)to_read^0x30;
	}else if(to_read>=0x41 && to_read<=0x46){
		return ((int)to_read^0x40)+9;
	}else if(to_read>=0x61 && to_read<=0x66){
		return ((int)to_read^0x60)+9;
	}
	printf("%c cannot be interpreted. \n", to_read);
	exit(2);
	return 0;
}

int main(int argc, char *argv[])
{
	// Initialise time
	hour=0;
	min=0;
	sec=0;
	tz=-4;

	//Initialise Display
	Fl_Window* cwindow= new Fl_Window(200,200,"Clock");
	ClockGauge* clockg = new ClockGauge(0,0,200,200);

	int option=0;
	unsigned char flags=0x01;
	char in_color_set[7];
	int color[3];
	while( (option=getopt(argc,argv,"hz:f:l:b:m:n")) != -1){
		switch(option){
			case 'h':
				printHelp();
				return 0;
				break;
			case 'z':
				//Cange timezone
				tz=atoi(optarg);
				break;
			case 'f':
				//Set forground
				strncpy(in_color_set,optarg,7*sizeof(char));
				for(int i=0;i<3;++i){
					color[i]=charHextoInt(in_color_set[2*i])*16+charHextoInt(in_color_set[2*i+1]);
				}
				Fl::set_color(FL_FOREGROUND_COLOR,color[0],color[1],color[2]);
				break;
			case 'b':
				//Set Background
				strncpy(in_color_set,optarg,7*sizeof(char));
				for(int i=0;i<3;++i){
					color[i]=charHextoInt(in_color_set[2*i])*16+charHextoInt(in_color_set[2*i+1]);
				}
				Fl::set_color(FL_BACKGROUND_COLOR,color[0],color[1],color[2]);
				break;
			case 'l':
				clockg->set_line_size(atoi(optarg));
				break;
			case 'm':
				clockg->set_message(optarg);
				break;
			case 'n':
				cwindow->border(0);
				break;
			default:
				printf("Bad input, use -h for help\n");
				exit(1);
				break;
		}
	}

	if(flags & 0x01){

		//#if __linux__
		//	
		//	cwindow->set_modal();
		//#endif
		uptime();
		clockg->set_time(hour,min,sec);
		cwindow->resizable(clockg);
		cwindow->end();
		cwindow->show();
		int last_sec=sec;
		while(Fl::check()>0){
			// Update Time 
			uptime();
			if(!(last_sec==sec)){
				clockg->set_time(hour,min,sec);
				last_sec=sec;
			}
			Fl::wait(0.5);
		}
		return Fl::run();
	}
}