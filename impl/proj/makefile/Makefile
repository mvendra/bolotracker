
.PHONY : all clean compile link 

APPNAME=bolotracker

BASE_SRC=../../src
BASE_OBJ=../../build
RUN=../../run

SRC=main.cpp bolotracker.cpp controller_interface.cpp database.cpp model.cpp tui.cpp /exceptions/ex_base.cpp /tests/bolotracker_tests.cpp /tests/datehelper_tests.cpp /tests/database_tests.cpp /tests/model_tests.cpp /utils/conversions.cpp /utils/datehelper.cpp /utils/sysutils.cpp /dataobjects/bonus.cpp /dataobjects/currency.cpp /dataobjects/invested_assets_subjects_link.cpp /dataobjects/invested_time.cpp /dataobjects/investor.cpp /dataobjects/bonuses_subjects_link.cpp /dataobjects/invested_asset.cpp /dataobjects/invested_money.cpp /dataobjects/invested_time_subjects_link.cpp /dataobjects/subject.cpp gui_fltk.cpp

SRC_SQLITE=../../lib/third_party/sqlite/src/sqlite3.c
#SRC_FULL=$(addprefix $(BASE_SRC)/, $(SRC))
#OBJ=$(SRC:.cpp=.o) 
#OBJ_FULL=$(addprefix $(BASE_OBJ)/, $(OBJ))
COMPILER=g++
C_COMPILER=gcc

ARCH := $(shell getconf LONG_BIT)
PLAT=linux

ifeq ($(MODE),)
	MODE=debug
endif

ifeq ($(MODE),debug)
BASE_OBJ_FULL=$(BASE_OBJ_FULL)_
INTFLAGS = \
	-g \
	-Wall \
	-Wextra \
	-pedantic \
	-Weffc++ \
	-Werror \
	-fPIC \
	-pthread \
	-D_GLIBCXX_DEBUG \
	-std=c++14

SQLITE_CPPFLAGS = \
              -g  \
            -fPIC \
         -pthread

FLTK_CPPFLAGS = \
                -D_LARGEFILE_SOURCE \
                -D_LARGEFILE64_SOURCE \
                -D_THREAD_SAFE \
                -D_REENTRANT

FLTK_LDFLAGS = \
			   -L../../lib/third_party/fltk/lib/linux_x64_debug/ \
               -lfltk \
               -lXcursor \
	  		   -lXfixes \
			   -lXext \
			   -lXft \
			   -lfontconfig \
			   -lXinerama \
			   -lm \
			   -lX11

POSTBUILD=
#DEFINES= -D _DEBUG -D _LOG 
endif

ifeq ($(MODE),release)
INTFLAGS = \
 	-O2 \
	-Wall \
	-Wextra \
	-pedantic \
	-Weffc++ \
	-Werror \
	-fPIC \
	-std=c++14

SQLITE_CPPFLAGS = \
              -O2 \
            -fPIC \
         -pthread

FLTK_CPPFLAGS = \
                -D_LARGEFILE_SOURCE \
                -D_LARGEFILE64_SOURCE \
                -D_THREAD_SAFE \
                -D_REENTRANT

FLTK_LDFLAGS = \
			   -L../../lib/third_party/fltk/lib/linux_x64_release/ \
               -lfltk \
               -lXcursor \
	  		   -lXfixes \
			   -lXext \
			   -lXft \
			   -lfontconfig \
			   -lXinerama \
			   -lm \
			   -lX11

POSTBUILD= strip $(FULL_APP_NAME)
#DEFINES= -D _LOG 
endif

ifeq ($(ARCH),64)
CPPFLAGS = $(INTFLAGS) -m64
else 
CPPFLAGSS = $(INTFLAGS)
endif


INCLUDES=-I$(BASE_SRC) -I../../lib/third_party/sqlite/src -I../../lib/testforecho/include -I../../lib/third_party/fltk/src -I../../lib/third_party/fltk/src/images
LDFLAGS=-lpthread -ldl $(FLTK_LDFLAGS)

BASE_OBJ_FULL=$(BASE_OBJ)/$(PLAT)_x$(ARCH)_$(MODE)
RUN_FULL=$(RUN)/$(PLAT)_x$(ARCH)_$(MODE)
ALL_OBJS=$(foreach src,$(SRC),$(BASE_OBJ_FULL)/$(notdir $(src:.cpp=.o)))
FULL_APP_NAME=$(RUN_FULL)/$(APPNAME)

all: compile link 

compile:
	@mkdir -p $(BASE_OBJ_FULL)
	$(foreach src,$(SRC),$(COMPILER) $(INCLUDES) $(CPPFLAGS) $(FLTK_CPPFLAGS) -c $(BASE_SRC)/$(src) -o $(BASE_OBJ_FULL)/$(notdir $(src:.cpp=.o));)
	$(C_COMPILER) $(INCLUDES) $(SQLITE_CPPFLAGS) -c $(SRC_SQLITE) -o $(BASE_OBJ_FULL)/$(notdir $(SRC_SQLITE:.c=.o))

link:
	@mkdir -p $(RUN_FULL)
	$(COMPILER) -o $(FULL_APP_NAME) $(ALL_OBJS) $(BASE_OBJ_FULL)/$(notdir $(SRC_SQLITE:.c=.o)) $(LDFLAGS)
	$(POSTBUILD)

clean:
	$(foreach objs,$(ALL_OBJS),rm -rf $(objs);)
	rm -rf $(BASE_OBJ_FULL)/$(notdir $(SRC_SQLITE:.c=.o))
	rm -rf $(FULL_APP_NAME)

