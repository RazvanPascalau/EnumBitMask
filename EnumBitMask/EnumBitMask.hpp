//
//  EnumBitMask.hpp
//  EnumBitMask
//
//  Created by Razvan Pascalau on 22/12/15.
//  Copyright © 2015 Razvan Pascalau. All rights reserved.
//

#pragma once
#include <algorithm>
#include <initializer_list>
#include <type_traits>

template <typename EnumType>
class EnumBitMask {
    static_assert(std::is_enum<EnumType>::value, "This type works only with enums as flags");

public:
    EnumBitMask();
    explicit EnumBitMask(const std::initializer_list<EnumType>& initFlags);

    bool isSet(EnumType enumFlag) const;
    template <typename... Params>
    bool isSet(EnumType enumFlag, Params... nextEnumFlags) const;

    void set(EnumType flag);
    template <typename... Params>
    void set(EnumType enumFlag, Params... nextEnumFlags);

    void clear(EnumType flag);
    template <typename... Params>
    void clear(EnumType enumFlag, Params... nextEnumFlags);

    typename std::underlying_type<EnumType>::type getRawValue() const { return mBits; };

private:
    using EnumUnderlyingType = typename std::underlying_type<EnumType>::type;
    EnumUnderlyingType mBits = 0;
};

template <typename EnumType>
EnumBitMask<EnumType>::EnumBitMask()
{
}

template <typename EnumType>
EnumBitMask<EnumType>::EnumBitMask(const std::initializer_list<EnumType>& initFlags)
{
    std::for_each(std::begin(initFlags), std::end(initFlags), [this, &initFlags](EnumType enumFlag) { set(enumFlag); });
}

template <typename EnumType>
void EnumBitMask<EnumType>::clear(EnumType flag)
{
    mBits &= ~(static_cast<EnumUnderlyingType>(flag));
}

template <typename EnumType>
template <typename... Params>
void EnumBitMask<EnumType>::clear(EnumType enumFlag, Params... nextEnumFlags)
{
    clear(enumFlag);
    clear(nextEnumFlags...);
}

template <typename EnumType>
void EnumBitMask<EnumType>::set(EnumType flag)
{
    mBits |= static_cast<EnumUnderlyingType>(flag);
}

template <typename EnumType>
template <typename... Params>
void EnumBitMask<EnumType>::set(EnumType enumFlag, Params... nextEnumFlags)
{
    set(enumFlag);
    set(nextEnumFlags...);
}

template <typename EnumType>
bool EnumBitMask<EnumType>::isSet(EnumType checkedEnum) const
{
    auto result = (mBits & static_cast<EnumUnderlyingType>(checkedEnum)) == static_cast<EnumUnderlyingType>(checkedEnum);
    return result;
}

template <typename EnumType>
template <typename... Params>
bool EnumBitMask<EnumType>::isSet(EnumType checkedEnum, Params... nextEnums) const
{
    return isSet(checkedEnum) && isSet(nextEnums...);
}
