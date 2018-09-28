#xcTree Makefile

GCC=/usr/bin/gcc

PROJDIR=$(HOME)/temp/XmlEditor

MODULE = xml2c
OBJS = xcTree.o xcFunc.o xcObj.o xcT1.o xcT2.o xcT3.o xcT3Common.o xcT3Set.o xcT3Call.o
CFLAG = -m32 -I/usr/include -I/usr/include/libxml2 -I$(PROJDIR)/include
D_CFLAG = -g -m32 -I/usr/include -I/usr/include/libxml2 -I$(PROJDIR)/include
LDIR = -m32 -L. -L/usr/lib -L$(PROJDIR)/lib
LLIB = -lxml2 -lpub_api

all: SO TEST

SO: $(OBJS)
	ln -nfs  /usr/lib/libxml2.so.2.7.6 libxml2.so
	$(GCC) -shared -o libxml2c.so $(OBJS) $(LDIR) $(LLIB)

xcTree.o: xcTree.c
	$(GCC) -c $< $(D_CFLAG)

xcFunc.o: xcFunc.c
	$(GCC) -c $< $(D_CFLAG)

xcObj.o: xcObj.c
	$(GCC) -c $< $(D_CFLAG)

xcT1.o: xcT1.c
	$(GCC) -c $< $(D_CFLAG)

xcT2.o: xcT2.c
	$(GCC) -c $< $(D_CFLAG)

xcT3.o: xcT3.c
	$(GCC) -c $< $(D_CFLAG)

xcT3Common.o: xcT3Common.c
	$(GCC) -c $< $(D_CFLAG)

xcT3Set.o: xcT3Set.c
	$(GCC) -c $< $(D_CFLAG)

xcT3Call.o: xcT3Call.c
	$(GCC) -c $< $(D_CFLAG)

clean: 
	rm -rf $(OBJS)
	rm -rf lib$(MODULE).so
	rm -rf xcTest.o
	rm -rf xcTest

xcTest.o: xcTest.c
	$(GCC) -c $< $(D_CFLAG)

TEST: xcTest.o
	$(GCC) -o xcTest $< $(LDIR) $(LLIB) -lxml2c
