ifndef EGT_DEVROOT
	$(error EGT_DEVROOT must be defined before calling make)
endif

SOURCES = pugixml.cpp

LIBNAME=libpugixml.a

$(LIBNAME): $(SOURCES)

include $(EGT_DEVROOT)/Defines

install: $(LIBNAME)
