#include <format>
#include <iostream>

// A wrapper for type T
template <class T> struct Box
{
    T value;
};

// The wrapper Box<T> can be formatted using the format specification of the wrapped value
template <class T, class CharT> struct std::formatter<Box<T>, CharT> : std::formatter<T, CharT>
{
    // parse() is inherited from the base class

    // Define format() by calling the base class implementation with the wrapped value
    template <class FormatContext> auto format(Box<T> t, FormatContext& fc)
    {
        return std::formatter<T, CharT>::format(t.value, fc);
    }
};

int main()
{
    Box<int> v = {42};
    std::cout << std::format("{:#x}", v);
}
