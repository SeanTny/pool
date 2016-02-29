TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cc \
    mpool.c \
    lib/pthread.c \
    thpool.c

INCLUDEPATH += "F:\C-C++\hfdslib\include"

INCLUDEPATH += "F:\C-C++\boost_1_59_0\boost_1_59_0"

LIBS+="F:\C-C++\hfdslib\lib\hfdslib.lib"

LIBS += user32.lib shell32.lib ole32.lib

HEADERS += \
    mpool.h \
    m_vector.h \
    lib/pthread.h \
    thpool.h
