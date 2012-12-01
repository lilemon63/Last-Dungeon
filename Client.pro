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
    Go/Control/pawn.cpp \
    Go/Control/grouppawn.cpp \
    Go/Control/groupplayer.cpp \
    Go/Control/player.cpp \
    Go/Control/map.cpp \
    Go/Control/board.cpp
LIBS += -lIrrlicht \
        -llua50 \
        -llualib50

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
    Go/Control/pawn.h \
    Go/Control/grouppawn.h \
    Go/Control/groupplayer.h \
    Go/Control/player.h \
    lunar.h \
    Go/Control/map.h \
    Go/Control/board.h

OTHER_FILES += \
    README.txt \
    ../Client-build-desktop-Qt_4_8_1_dans_le_PATH__Syst_me__Release/test.lua
