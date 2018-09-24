#getDefStruct Makefile

GCC=/usr/bin/gcc

PROJDIR=$(HOME)/temp/XmlEditor
PROJ_LIB_DIR=$(PROJDIR)/lib

MODULE = libpub_str_api.so
OBJS = pub_str_api.o pub_print.o pub_xml_api.o
CFLAG = -Wall -Werror -I/usr/include -I/usr/include/libxml2
D_CFLAG = -g -m32 -Wall -Werror -I/usr/include -I/usr/include/libxml2 -I$(PROJDIR)/include
LDIR = -L. -L/usr/lib -m32
LLIB = -lxml2

all: $(OBJS)
	$(GCC) -shared -o $(PROJ_LIB_DIR)/$(MODULE) $(OBJS) $(LDIR) $(LLIB)

pub_str_api.o: pub_str_api.c
	$(GCC) -c -o pub_str_api.o pub_str_api.c $(D_CFLAG)

pub_print.o: pub_print.c
	$(GCC) -c -o pub_print.o pub_print.c $(D_CFLAG)

pub_xml_api.o: pub_xml_api.c
	$(GCC) -c -o pub_xml_api.o pub_xml_api.c $(D_CFLAG)

clean: 
	rm -rf $(OBJS)
	rm -rf $(PROJ_LIB_DIR)/$(MODULE)
