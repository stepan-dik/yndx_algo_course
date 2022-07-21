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
    main.cpp \
    sprint_1/algorithms.cpp \
    sprint_1/closest_zero/closest_zero.cpp \
    sprint_1/sleight_of_hand/sleight_of_hand.cpp \
    sprint_2/bracket_sequence/bracket_sequence.cpp \
    sprint_2/calculator_polish/calculator_polish.cpp \
    sprint_2/deleteNode/deleteNode.cpp \
    sprint_2/deque.cpp \
    sprint_2/findElement/findElement.cpp \
    sprint_2/limited_queue.cpp \
    sprint_2/printLinkedList/printLinkedList.cpp \
    sprint_2/reverseOrder/reverseOrder.cpp \
    sprint_2/stackmax.cpp \
    sprint_3/big_num/big_num.cpp \
    sprint_3/bracket_gen/bracket_gen.cpp \
    sprint_3/bubble_sort/bubble_sort.cpp \
    sprint_3/combinations/combinations.cpp \
    sprint_3/conferencers/conferencers.cpp \
    sprint_3/cookies_and_kids.cpp \
    sprint_3/count_sort/count_sort.cpp \
    sprint_3/count_values/count_values.cpp \
    sprint_3/in_place_quicksort/in_place_quicksort.cpp \
    sprint_3/median/median.cpp \
    sprint_3/merge_sort/merge_sort.cpp \
    sprint_3/subsequence/subsequence.cpp \
    sprint_3/triangle_perimeter/triangle_perimeter.cpp \
    sprint_3/two_bin_search/two_bin_search.cpp \
    sprint_4/activities/activities.cpp \
    sprint_4/anagrams/anagrams.cpp\
    sprint_4/break_me/break_me.cpp \
    sprint_4/competition/competition.cpp \
    sprint_4/hashtable/hashtable.cpp \
    sprint_4/poly_hash/poly_hash.cpp \
    sprint_4/prefix_hashes/prefix_hashes.cpp \
    sprint_4/search_index/search_index.cpp \
    sprint_4/strange_cmp/strange_cmp.cpp \
    sprint_4/substrings/substrings.cpp \
    sprint_5/add_node/add_node.cpp \
    sprint_5/print_range/print_range.cpp \
    sprint_5/remove_node/remove_node.cpp \
    sprint_5/search_tree/search_tree.cpp \
    work/refconnector.cpp \
    work/rpcmethod.cpp \
    work/reqtypes.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    sprint_1/algorithms.h \
    sprint_2/deque.h \
    sprint_2/limited_queue.h \
    sprint_2/stack.h \
    sprint_2/stackmax.h \
    work/macro.h \
    nodes.h \
    objects.h \
    solution.h \
    study.h \
    work/refconnector.h \
    work/rpcmethod.h \
    work/reqtypes.h
