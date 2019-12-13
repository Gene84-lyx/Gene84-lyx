#############################################################################
# Makefile for building: Mplayer
# Generated by qmake (2.01a) (Qt 4.8.7) on: ?? 12? 13 16:48:57 2019
# Project:  Mplayer.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -o Makefile Mplayer.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mlabel.cpp \
		mainwidgit.cpp moc_mlabel.cpp \
		moc_mainwidgit.cpp \
		qrc_picture.cpp
OBJECTS       = main.o \
		mlabel.o \
		mainwidgit.o \
		moc_mlabel.o \
		moc_mainwidgit.o \
		qrc_picture.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		Mplayer.pro
QMAKE_TARGET  = Mplayer
DESTDIR       = 
TARGET        = Mplayer

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mlabel.h ui_mainwidgit.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Mplayer.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile Mplayer.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile Mplayer.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/Mplayer1.0.0 || $(MKDIR) .tmp/Mplayer1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/Mplayer1.0.0/ && $(COPY_FILE) --parents mlabel.h mainwidgit.h .tmp/Mplayer1.0.0/ && $(COPY_FILE) --parents picture.qrc .tmp/Mplayer1.0.0/ && $(COPY_FILE) --parents main.cpp mlabel.cpp mainwidgit.cpp .tmp/Mplayer1.0.0/ && $(COPY_FILE) --parents mlabel.ui mainwidgit.ui .tmp/Mplayer1.0.0/ && (cd `dirname .tmp/Mplayer1.0.0` && $(TAR) Mplayer1.0.0.tar Mplayer1.0.0 && $(COMPRESS) Mplayer1.0.0.tar) && $(MOVE) `dirname .tmp/Mplayer1.0.0`/Mplayer1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/Mplayer1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mlabel.cpp moc_mainwidgit.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mlabel.cpp moc_mainwidgit.cpp
moc_mlabel.cpp: mlabel.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) mlabel.h -o moc_mlabel.cpp

moc_mainwidgit.cpp: mlabel.h \
		mainwidgit.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) mainwidgit.h -o moc_mainwidgit.cpp

compiler_rcc_make_all: qrc_picture.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_picture.cpp
qrc_picture.cpp: picture.qrc \
		image/muteoff.jpg \
		image/music2.png \
		image/timg.jpg \
		image/music1.png \
		image/mute.jpg \
		image/music.png \
		image/background/Thumbs.db \
		image/background/11.jpg \
		image/background/6.jpg \
		image/background/7.jpg \
		image/background/20.jpg \
		image/button_style/Thumbs.db \
		image/button_style/back.png \
		image/button_style/play1.png \
		image/button_style/front1.png \
		image/button_style/exit.jpg \
		image/button_style/play.png \
		image/button_style/pause1.png \
		image/button_style/back1.png \
		image/button_style/pause.png \
		image/button_style/front.png
	/usr/lib/x86_64-linux-gnu/qt4/bin/rcc -name picture picture.qrc -o qrc_picture.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mlabel.h ui_mainwidgit.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mlabel.h ui_mainwidgit.h
ui_mlabel.h: mlabel.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic mlabel.ui -o ui_mlabel.h

ui_mainwidgit.h: mainwidgit.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic mainwidgit.ui -o ui_mainwidgit.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwidgit.h \
		mlabel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mlabel.o: mlabel.cpp mlabel.h \
		ui_mlabel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mlabel.o mlabel.cpp

mainwidgit.o: mainwidgit.cpp mainwidgit.h \
		mlabel.h \
		ui_mainwidgit.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwidgit.o mainwidgit.cpp

moc_mlabel.o: moc_mlabel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mlabel.o moc_mlabel.cpp

moc_mainwidgit.o: moc_mainwidgit.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwidgit.o moc_mainwidgit.cpp

qrc_picture.o: qrc_picture.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_picture.o qrc_picture.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

