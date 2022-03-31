QT -= gui

CONFIG += c++20 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algorithms.cpp \
    bracket_sequence.cpp \
    calculator_polish.cpp \
    deck.cpp \
    hashtable.cpp \
    in_place_quicksort.cpp \
    limited_queue.cpp \
        main.cpp \
    refconnector.cpp \
    rpcmethod.cpp \
    reqtypes.cpp \
    closest_zero.cpp \
    deleteNode.cpp \
    findElement.cpp \
    printLinkedList.cpp \
    reverseOrder.cpp \
    search_index.cpp \
    sleight_of_hand.cpp \
    stackmax.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    algorithms.h \
    deck.h \
    limited_queue.h \
    macro.h \
    nodes.h \
    objects.h \
    solution.h \
    stack.h \
    stackmax.h \
    study.h \
    refconnector.h \
    rpcmethod.h \
    reqtypes.h
