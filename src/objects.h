#ifndef OBJECTS_H
#define OBJECTS_H

#include <string>
#include <unordered_map>

struct SomeStruct {
    std::string str;
    std::unordered_map<std::string, int> map;
    int number = 0;

    template<typename T, typename A, typename B>
    SomeStruct(T&& _str, A&& _map, B&& _number) noexcept
        : str(std::forward<T>(_str))
        , map(std::forward<A>(_map))
        , number(std::forward<B>(_number))
    {}
};

class Entities
{
public:
    template<typename T, typename A, typename B>
    void add(T&& str, A&& map, B&& number) noexcept
    {
        the_map.insert({std::string(str), SomeStruct(std::forward<T>(str), std::forward<A>(map), std::forward<B>(number))});
    }

    std::unordered_map<std::string, SomeStruct> the_map;
};

#endif // OBJECTS_H
