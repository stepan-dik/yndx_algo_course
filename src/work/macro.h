#ifndef MACRO_H
#define MACRO_H

#define FUNC_MACRO(name) \
    Q_SIGNALS: \
        void signal##name(); \
    private: \

#endif // MACRO_H
