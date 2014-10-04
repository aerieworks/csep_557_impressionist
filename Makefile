#
#  Makefile for fltk IMPRESSIONIST application
#  On the Mac! (Intel Macbook with developer tools (Rez resource fork command) and X11)  
#

FLTK = /usr/local/#Where you put fltk

INCLUDE = -I$(FLTK)/include -I$(FLTK)/png -I$(FLTK)/jpeg -I/usr/X11R6/include 
LIBDIR = -L$(FLTK)/lib -L$(FLTK)/lib/libfltk.a -L/usr/X11R6/lib 

LIBS = -lXext -lX11 -lfltk -lfltk_gl -lm -framework OpenGL -framework GLUT -lfltk_images -framework AGL \
        -framework Carbon -framework ApplicationServices

CFLAGS = -g

CC = g++

POSTPROCESS = /Developer/Tools/Rez -t APPL -o impressionist mac.r



.SUFFIXES: .o .cpp

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $<

ALL.O = imageio.o impBrush.o \
	impressionist.o FltDesignUI.o \
	impressionistDoc.o impressionistUI.o \
	originalView.o paintView.o pointBrush.o 
    
impressionist: $(ALL.O)
	$(CC) $(CFLAGS) -o $@ $(ALL.O) $(INCLUDE) $(LIBS) $(LIBDIR)# && $(POSTPROCESS)

clean:
	rm *.o impressionist
