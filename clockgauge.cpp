#include "clockgauge.hpp"

ClockGauge::ClockGauge(int x, int y,int w, int h)
:Fl_Widget(x,y,w,h)
{
	reelstep=false;
	line_size=2;
}


void ClockGauge::set_time(int h,int m,int s){
	this->hour=h;
	this->min=m;
	this->sec=s;
	this->damage(1);
}

void ClockGauge::set_message(char*ptomess){
	message=ptomess;
}

void ClockGauge::set_line_size(int size){
	line_size=size;
}

void ClockGauge::draw(){
	int wx=this->x();
	int wy=this->y();
	int ww=this->w();
	int wh=this->h();

	//Calcul the length of the needles
	int hyp= (wh-wy)<(ww-wx)?(wh-wy):(ww-wx);

	//Draw background
	fl_line_style(FL_SOLID, line_size, NULL);
	fl_color(FL_BACKGROUND_COLOR);
	fl_rectf(wx,wy,ww,wh);
	fl_color(FL_FOREGROUND_COLOR);

	//Prepare the time string
	char* time_string=new char[12];
	sprintf(time_string,"%02i:%02i:%02i",hour,min,sec);

	int string_w=0;
	int string_h=0;
	fl_font(FL_COURIER,hyp*0.10);

	//Mesure the size then draw
	fl_measure(time_string, string_w, string_h);
	fl_color(FL_FOREGROUND_COLOR);

	fl_draw(time_string, (ww-wx)/2-(string_w)/2, (wh-wy)/2+hyp/4);

	//Adjuste and display message
	if(message != NULL){
		string_w=0;
		string_h=0;
		int font_size=hyp*0.10;

		//Calcule la meilleur taille
		fl_font(FL_COURIER,font_size);
		fl_measure(message, string_w, string_h);
		int best_w= font_size*(hyp*0.7)/(string_w);
		int best_h= font_size*(hyp*0.2)/(string_h);
		font_size=best_w<best_h?best_w:best_h;

		//Paramètre l'affichage
		fl_font(FL_COURIER,font_size);
		fl_measure(message, string_w, string_h);
		
		//Affiche
		fl_color(FL_FOREGROUND_COLOR);
		fl_draw(message, (ww-wx)/2-(string_w)/2, (wh-wy)/2-hyp/4);
	}

	//Draw gauge
	fl_color(fl_color_average(FL_FOREGROUND_COLOR,FL_BACKGROUND_COLOR,0.5));
	for(int i=0;i<360;i+=6){
		int angle=180-i;


		int cpx=hyp/(i%30==0?2.2:2.1)*sin(toRAD(angle));
		cpx+=(ww+wx)/2;

		int cpy=hyp/(i%30==0?2.2:2.1)*cos(toRAD(angle));
		cpy+=(wh+wy)/2;


		int px=hyp/2*sin(toRAD(angle));
		px+=(ww+wx)/2;

		int py=hyp/2*cos(toRAD(angle));
		py+=(wh+wy)/2;
	
		fl_line(cpx,cpy,px,py);
	}



	
	//Draw minutes
	int angle=180-(min*6)-(sec*6/60);

	int px=hyp/2*sin(toRAD(angle));
	px+=(ww+wx)/2;

	int py=hyp/2*cos(toRAD(angle));
	py+=(wh+wy)/2;

	fl_color(FL_FOREGROUND_COLOR);
	fl_line((ww+wx)/2,(wh+wy)/2,px,py);

	//Draw hour
	angle=180-(hour*30)-(min*6/12);

	px=hyp/2.5*sin(toRAD(angle));
	px+=(ww+wx)/2;

	py=hyp/2.5*cos(toRAD(angle));
	py+=(wh+wy)/2;

	fl_color(FL_FOREGROUND_COLOR);
	fl_line((ww+wx)/2,(wh+wy)/2,px,py);

	//Draw second
	if(line_size>1){
		fl_line_style(FL_SOLID, line_size/2, NULL);
	}
	angle=180-(sec*6);

	px=hyp/2*sin(toRAD(angle));
	px+=(ww+wx)/2;

	py=hyp/2*cos(toRAD(angle));
	py+=(wh+wy)/2;

	fl_color(FL_FOREGROUND_COLOR);
	fl_line((ww+wx)/2,(wh+wy)/2,px,py);
}

ClockGauge::~ClockGauge(){

}