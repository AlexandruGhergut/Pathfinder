TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Application.cpp \
    main.cpp \
    MainState.cpp \
    NodeShape.cpp \
    Pathfinder.cpp \
    TextureManager.cpp


LIBS *= -L"D:\Programming\cpp_libraries\SFML-2.1-build-qt\lib" -lsfml-graphics -lsfml-window -lsfml-network -lsfml-audio -lsfml-system


CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += D:\Programming\cpp_libraries\SFML-2.1-build-qt\include
DEPENDPATH += D:\Programming\cpp_libraries\SFML-2.1-build-qt\include

HEADERS += \
    Application.h \
    MainState.h \
    Node.h \
    NodeShape.h \
    Pathfinder.h \
    Point2D.h \
    TextureManager.h

OTHER_FILES += \
    Pathfinder2.pro.user

DESTDIR = $$PWD

