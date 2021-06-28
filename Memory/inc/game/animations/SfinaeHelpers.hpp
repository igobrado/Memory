//
// Created by Igor Obradovic.
//
#pragma once

#include <tinyxml2.h>

namespace traits
{

template <typename U>
using PointerToFunctionThatTakesNothingAndReturnsVoid = void (U::*)();

template <typename U, PointerToFunctionThatTakesNothingAndReturnsVoid<U>>
struct SfinaeHelper;

template <typename T>
struct HasStopAnimation
{
    using TrueType  = char;
    using FalseType = int;

    template <typename U>
    static TrueType& Test(SfinaeHelper<U, &U::stopAnimation>*);

    template <typename>
    static FalseType& Test(...);

    static bool const value = sizeof(Test<T>(0)) == sizeof(TrueType);
};

template <typename T>
struct HasInvalidateTransform
{
    using TrueType  = char;
    using FalseType = int;

    template <typename U>
    static TrueType& Test(SfinaeHelper<U, &U::invalidateTransform>*);

    template <typename>
    static FalseType& Test(...);

    static bool const value = sizeof(Test<T>(0)) == sizeof(TrueType);
};

template <typename T>
struct HasLoad
{
    using TrueType  = char;
    using FalseType = int;

    template <typename U,  void (U::*)(tinyxml2::XMLElement*, char const*, char const*)>
    struct LoadMethodSfinaeHelper;

    template <typename U>
    static TrueType& Test(LoadMethodSfinaeHelper<U, &U::Load>*);

    template <typename>
    static FalseType& Test(...);

    static bool const value = sizeof(Test<T>(0)) == sizeof(TrueType);
};

}  // namespace traits