//
//  EnumBitMask.hpp
//  EnumBitMask
//
//  Created by Razvan Pascalau on 22/12/15.
//  Copyright © 2015 Razvan Pascalau. All rights reserved.
//

#pragma once
#include <type_traits>

template <typename EnumType>
class EnumBitMask
{
private:
    using EnumUnderlyingType = typename std::underlying_type<EnumType>::type;
};

