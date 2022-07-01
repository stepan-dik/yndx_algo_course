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
    activities/activities.cpp \
    algorithms.cpp \
    big_num/big_num.cpp \
    bracket_gen/bracket_gen.cpp \
    bracket_sequence/bracket_sequence.cpp \
    bubble_sort/bubble_sort.cpp \
    calculator_polish/calculator_polish.cpp \
    combinations/combinations.cpp \
    conferencers/conferencers.cpp \
    cookies_and_kids.cpp \
    count_sort/count_sort.cpp \
    count_values/count_values.cpp \
    deque.cpp \
    hashtable/hashtable.cpp \
    in_place_quicksort/in_place_quicksort.cpp \
    limited_queue.cpp \
        main.cpp \
    merge_sort/merge_sort.cpp \
    print_range/print_range.cpp \
    refconnector.cpp \
    rpcmethod.cpp \
    reqtypes.cpp \
    closest_zero/closest_zero.cpp \
    deleteNode/deleteNode.cpp \
    findElement/findElement.cpp \
    printLinkedList/printLinkedList.cpp \
    reverseOrder/reverseOrder.cpp \
    search_index/search_index.cpp \
    sleight_of_hand/sleight_of_hand.cpp \
    stackmax.cpp \
    subsequence/subsequence.cpp \
    triangle_perimeter/triangle_perimeter.cpp \
    two_bin_search/two_bin_search.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    algorithms.h \
    deque.h \
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
