.SUFFIXES: .c .o .a 

#LIBS=-lGL -lGLU -lglut -lm
LIBS=-framework GLUT -framework OpenGL -lm
#LIBS=-lglut32 -lglu32 -lopengl32 -DWIN32 -lm

SOURCE= \
	myInit.c \
	myLight.c \
	myIdle.c \
	myCamera.c \
	myKeyboard.c \
	myMouse.c \
	myReshape.c \
	myDisplay.c \
	myOperation.c \
	pdbRead.c \
	lpdbCenterCalc.c \
	lpdbSizeCalc.c
	

.c.o:
	gcc -g -Wall -c $*.c -o $*.o
	#gcc -g -c -Wall $*.c -o $*.o -Wno-deprecated
	#gcc -g -Wall -DWIN32 -c $*.c -o $*.o

all: myTest

win: myTest.exe

myTest: myTest.o libmyGLUT.a
	gcc -g -Wall -o $@ myTest.o -L./ -lmyGLUT -lm $(LIBS)

myTest.exe: myTest.o libmyGLUT.a
	gcc -g -Wall -o $@ myTest.o -L./ -lmyGLUT $(LIBS) -lm

libmyGLUT.a: $(SOURCE:.c=.o)
	ar r $@ $(SOURCE:.c=.o)

test:
	./myTest

clean:
	rm -rf *.o *.exe *.a myTest 

depend: $(SOURCE)
	gcc -M *.c > dependency

include dependency
