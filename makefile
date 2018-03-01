FLIBS= `fltk-config --libs --cxxflags --ldflags`
NAME = FullClock
GPP  = g++

all:
	$(GPP) *.cpp -o $(NAME) $(FLIBS) -ggdb;
