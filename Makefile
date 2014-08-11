# TODO: BSD make compatibility
# (use gmake)
OBJDIR = build
SRCDIR = src
LIBNAME_SO = libfastblit.so
LIBNAME_A = libfastblit.a
BINNAME_FAB_TEST = fab_test

RANLIB = ranlib

OBJS = \
	$(OBJDIR)/blit.o \
	$(OBJDIR)/blitexp.o \
	$(OBJDIR)/convert.o \
	$(OBJDIR)/expand.o \
	#

INCLUDES = src/common.h src/fastblit.h

CFLAGS = -Wall -Wextra -Wno-unused-parameter -O2 -g -Isrc -I/usr/local/include -fPIC
LDFLAGS_SO = -O2 -g $(LIBS_DIRS) -lm #$(LIBS_SDL)
CFLAGS_APP_SDL = -Wall -Wextra -Wno-unused-parameter -O2 -g -Isrc -I/usr/local/include `sdl-config --cflags`
LDFLAGS_APP_SDL = -O2 -g $(LIBS_DIRS) -lm $(LIBS_SDL)
LIBS_DIRS = -L/usr/local/lib
LIBS_SDL = `sdl-config --libs`

all: $(LIBNAME_SO) $(LIBNAME_A) $(BINNAME_FAB_TEST)

clean:
	rm -r $(OBJDIR)

$(BINNAME_FAB_TEST): $(LIBNAME_A) src/app_test.c
	$(CC) -o $(BINNAME_FAB_TEST) $(CFLAGS_APP_SDL) $(LDFLAGS_APP_SDL) $(OBJS) src/app_test.c

$(LIBNAME_SO): $(OBJDIR) $(OBJS)
	$(CC) -shared -o $(LIBNAME_SO) $(LDFLAGS_SO) $(OBJS)

$(LIBNAME_A): $(OBJDIR) $(OBJS)
	$(AR) -rcs $(LIBNAME_A) $(OBJS)
	$(RANLIB) $(LIBNAME_A)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES)
	$(CC) -c -o $@ $(CFLAGS) $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: all clean

