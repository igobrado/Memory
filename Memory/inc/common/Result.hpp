//
// Created by Igor Obradovic.
//
#pragma once

#include <cassert>
#include <memory>
#include <type_traits>

template <typename T>
class Result
{
    template <typename>
    friend class Result;  // Pronounce all templated as friends to make converting constructor working.
public:
    using ValueType    = T;
    using ValueTypeRef = T const&;
    using ValuePtr     = T*;

    Result() : m_Value{ nullptr }
    {
    }

    ~Result()
    {
        if (m_Value)
        {
            delete m_Value;
            m_Value = nullptr;
        }
    }

    Result(Result&& other) : m_Value{ nullptr }
    {
        if (other)
        {
            m_Value = new ValueType{ std::move(*other.m_Value) };
        }
    }

    template <typename... Args>
    Result(Args&&... args) : m_Value{ new ValueType{ std::forward<Args>(args)... } }
    {
        static_assert(std::is_constructible<ValueType, Args...>::value, "Type is not constructable from given params");
    }

    Result(ValueType&& rhs) : m_Value{ new ValueType{ std::forward<ValueType>(rhs) } }
    {
    }

    ValueTypeRef getValue() const
    {
        assert(m_Value != nullptr);
        return *m_Value;
    }

    ValuePtr release()
    {
        assert(m_Value != nullptr);
        ValuePtr* rv = m_Value;
        m_Value      = nullptr;  // drop ownership but leave heap obj.
        return rv;
    }

    constexpr explicit operator bool() const
    {
        return m_Value != nullptr;
    }

private:
    ValuePtr m_Value;
};