# --- tgcs-car for GP2X makefile
#  rerofumi <rero2@yuumu.org>
#

# --- your build environment

# - Windows with Cygwin
PCCC     = gcc
PCCFLAGS = -DNOTPSP -D__GP2X_SCREEN__
PCLIBS   = -lSDL_mixer -lm -lSDL_image -lpng -lz -lsmpeg -lvorbis -logg -ljpeg
PCINCLUDE = -I/usr/local/mingw32/include
PCSDLCONFIG = /usr/local/mingw32/bin/sdl-config

# - GP2X crosscompile with Cygwin
GPTOOLCHAIN = /opt/crosstool/gcc-3.4.1-glibc-2.3.3/arm-linux/bin
GPCC     = $(GPTOOLCHAIN)/arm-linux-gcc
GPCXX    = $(GPTOOLCHAIN)/arm-linux-g++
GPSTRIP  = $(GPTOOLCHAIN)/arm-linux-strip
GPCFLAGS = -DNOTPSP -D__GP2X__ -D__GP2X_SCREEN__
GPLIBS   = -lSDL_mixer -lm -lSDL_image -lpng -lz -ljpeg -lmad -lvorbisidec -lmikmod 
GPINCLUDE = -I/opt/theoddbot-libs-open2x-soft-float/usr/include
GPSDLCONFIG = /opt/theoddbot-libs-open2x-soft-float/usr/bin/sdl-config
GPSTATIC = -static

# --- source code target
PCOBJS = bootmain.o debug.o input.o sound.o \
        grp_screen.o grp_texture.o grp_sprite.o

GP2XOBJS = bootmain.o debug.o input.o sound.o \
          gp2x_grp_screen.o grp_texture.o grp_sprite.o

# - your apprication object
APPOBJS = gamemain.o puz_base.o puz_disp.o puz_trial.o


#
TARGET = tailtale-gp2x

CFLAGS = -O2 -Wall #-DDEBUG -g



# ----- suffix
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $<


# ----- target
#   (pc) = windows with cygwin
#   gp   = GP2X crosscompile with cygwin
#   mac  = MacOSX(tiger)
#
all : pc

pc : CC = $(PCCC)
pc : OBJS = $(PCOBJS) $(APPOBJS)
pc : LIBS += $(PCLIBS)
pc : LIBS += $(shell $(PCSDLCONFIG) --libs)
pc : CFLAGS += $(PCCFLAGS)
pc : CFLAGS += $(shell $(PCSDLCONFIG) --cflags)
pc : INCLUDE = $(PCINCLUDE)
pc : pcobjs
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

pcobjs : $(PCOBJS) $(APPOBJS)


gp : CC = $(GPCC)
gp : OBJS = $(GP2XOBJS) $(APPOBJS)
gp : LIBS += $(GPLIBS)
gp : LIBS += $(shell $(GPSDLCONFIG) --libs)
gp : CFLAGS += $(GPCFLAGS)
gp : CFLAGS += $(shell $(GPSDLCONFIG) --cflags)
gp : INCLUDE = $(GPINCLUDE)
gp : gpobjs
	$(GPCXX) $(GPSTATIC) -o $(TARGET).gpe $(OBJS) $(LIBS)
	$(GPSTRIP) $(TARGET).gpe

gpobjs : $(GP2XOBJS) $(APPOBJS)


clean :
	rm -rf *.o $(TARGET) $(TARGET)% $(TARGET).exe $(TARGET).gpe *~

bootmain.o : bootmain.c bootmain.h debug.h
debug.o : debug.c debug.h
psp_debug.o : psp_debug.c debug.h
grp_screen.o : grp_screen.c grp_screen.h grp_texture.h
psp_grp_screen.o : psp_grp_screen.c grp_screen.h grp_texture.h
input.o : input.c
sound.o : sound.h
grp_texture.o : grp_texture.c grp_texture.h
grp_sprite.o : grp_sprite.c grp_sprite.h
gamemain.o : gamemain.c gamemain.h grp_screen.h input.h sound.h debug.h \
             grp_texture.h grp_sprite.h



