TEMPLATE = app
CONFIG -= qt

SOURCES += main.cpp \
    testelementgui.cpp \
    Go/Vue/vue.cpp \
    elementgui.cpp \
    Go/Control/servergo.cpp \
    Go/preferences.cpp \
    Go/Control/plinth.cpp \
    Go/Vue/vueplinth.cpp \
    Go/Vue/playervue.cpp \
    Go/Vue/vuepawn.cpp \
    Go/Control/pawn.cpp
LIBS += -lIrrlicht

HEADERS += \
    testelementgui.h \
    Go/Vue/vue.h \
    elementgui.h \
    Go/Control/servergo.h \
    Go/preferences.h \
    Go/Control/plinth.h \
    Go/Vue/vueplinth.h \
    Go/Vue/playervue.h \
    Go/Vue/vuepawn.h \
    Go/Control/pawn.h

OTHER_FILES += \
    README.txt

