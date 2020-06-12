#ifndef HDLTYPES_IMPL_LOGIC_HPP
#define HDLTYPES_IMPL_LOGIC_HPP

#include <cstdint>          // uint8_t
#include <type_traits>      // enable_if_t, is_same_v, is_integral
#include <stdexcept>        // invalid_argument
#include <cassert>

#include "hdltypes/logic.hpp"


namespace hdltypes {

    namespace {

        constexpr bool logic_value_valid(Logic::value_type value)
        {
            return (Logic::U <= value) && (value <= Logic::DC);
        }

    }

    constexpr Logic::Logic(value_type value) noexcept : value_(value)
    {
        assert(logic_value_valid(value_));
    }

    template <typename CharType>
    constexpr Logic Logic::deserialize(const CharType& c)
    {
        switch (c)
        {
            case 'U': return Logic(U);
            case 'u': return Logic(U);
            case 'X': return Logic(X);
            case 'x': return Logic(X);
            case '0': return Logic(_0);
            case '1': return Logic(_1);
            case 'Z': return Logic(Z);
            case 'z': return Logic(Z);
            case 'W': return Logic(W);
            case 'w': return Logic(W);
            case 'L': return Logic(L);
            case 'l': return Logic(L);
            case 'H': return Logic(H);
            case 'h': return Logic(H);
            case '-': return Logic(DC);
        }
        throw std::invalid_argument("Given value is not a Logic");
    }

    constexpr Logic::value_type Logic::value() const noexcept
    {
        assert(logic_value_valid(value_));
        return value_;
    }

    template <typename CharType = char>
    constexpr CharType Logic::serialize() const noexcept
    {
        constexpr CharType table[9] = {
            'U', 'X', '0', '1', 'Z', 'W', 'L', 'H', '-'};
        return table[int(value())];
    }

    constexpr Logic operator ""_l (char c)
    {
        return Logic::deserialize(c);
    }

    template <typename IntType, typename std::enable_if<
        std::is_integral<IntType>::value &&
        !std::is_same<IntType, bool>::value
    , int>::type = 0>
    constexpr Logic to_logic(const IntType& i)
    {
        switch (i)
        {
            case 0: return '0'_l;
            case 1: return '1'_l;
        }
        throw std::invalid_argument("Given value is not a Logic");
    }

    constexpr Logic to_logic(bool b) noexcept
    {
        return b ? '1'_l : '0'_l;
    }

    constexpr bool operator== (Logic a, Logic b) noexcept
    {
        return a.value() == b.value();
    }

    constexpr bool operator!= (Logic a, Logic b) noexcept
    {
        return a.value() != b.value();
    }

    constexpr Logic operator& (Logic a, Logic b) noexcept
    {
        constexpr Logic table[9][9] = {
            {'U'_l, 'U'_l, '0'_l, 'U'_l, 'U'_l, 'U'_l, '0'_l, 'U'_l, 'U'_l},  // U
            {'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l},  // X
            {'0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l},  // 0
            {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // 1
            {'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l},  // Z
            {'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l},  // W
            {'0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l},  // L
            {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // H
            {'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l}}; // -
        //    U      X      0      1      Z      W      L      H      -
        return table[int(a.value())][int(b.value())];
    }

    constexpr Logic operator| (Logic a, Logic b) noexcept
    {
        constexpr Logic table[9][9] = {
            {'U'_l, 'U'_l, 'U'_l, '1'_l, 'U'_l, 'U'_l, 'U'_l, '1'_l, 'U'_l},  // U
            {'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l},  // X
            {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // 0
            {'1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l},  // 1
            {'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l},  // Z
            {'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l},  // W
            {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // L
            {'1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l},  // H
            {'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l}}; // -
        //    U      X      0      1      Z      W      L      H      -
        return table[int(a.value())][int(b.value())];
    }

    constexpr Logic operator^ (Logic a, Logic b) noexcept
    {
        constexpr Logic table[9][9] = {
            {'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l},  // U
            {'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l},  // X
            {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // 0
            {'U'_l, 'X'_l, '1'_l, '0'_l, 'X'_l, 'X'_l, '1'_l, '0'_l, 'X'_l},  // 1
            {'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l},  // Z
            {'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l},  // W
            {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // L
            {'U'_l, 'X'_l, '1'_l, '0'_l, 'X'_l, 'X'_l, '1'_l, '0'_l, 'X'_l},  // H
            {'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l}}; // -
        //    U      X      0      1      Z      W      L      H      -
        return table[int(a.value())][int(b.value())];
    }

    constexpr Logic operator~ (Logic a) noexcept
    {
        constexpr Logic table[9] = {
            'U'_l, 'X'_l, '1'_l, '0'_l, 'X'_l, 'X'_l, '1'_l, '0'_l, 'X'_l};
        //   U      X      0      1      Z      W      L      H      -
        return table[int(a.value())];
    }

    constexpr bool is01(Logic a) noexcept
    {
        return (a == '0'_l) || (a == '1'_l);
    }

    template <typename IntType = int>
    constexpr IntType to_int(Logic a)
    {
        if (a == '0'_l) {
            return 0;
        } else if (a == '1'_l) {
            return 1;
        }
        throw std::domain_error("Value cannot be converted to an integer.");
    }

    constexpr bool to_bool(Logic a)
    {
        return to_int(a);
    }

}

#endif
