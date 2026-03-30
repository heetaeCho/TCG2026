#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace log {



using Info = std::integral_constant<std::size_t, 0>;

template <>

struct Info<0> {

    static constexpr stdr::int_least32_t min_exponent = -10;

    static constexpr stdr::int_least32_t max_exponent = 10;

};



TEST_F(DragonboxTest_316, IsInRange_NormalRange_316) {

    EXPECT_TRUE((is_in_range<Info, -5, 5, 0>()));

}



TEST_F(DragonboxTest_316, IsInRange_BoundaryMinExponent_316) {

    EXPECT_TRUE((is_in_range<Info, -10, 5, 0>()));

}



TEST_F(DragonboxTest_316, IsInRange_BoundaryMaxExponent_316) {

    EXPECT_TRUE((is_in_range<Info, -5, 10, 0>()));

}



TEST_F(DragonboxTest_316, IsInRange_OutOfRangeMinExponent_316) {

    EXPECT_FALSE((is_in_range<Info, -11, 5, 0>()));

}



TEST_F(DragonboxTest_316, IsInRange_OutOfRangeMaxExponent_316) {

    EXPECT_FALSE((is_in_range<Info, -5, 11, 0>()));

}



TEST_F(DragonboxTest_316, IsInRange_ExactMinAndMaxExponent_316) {

    EXPECT_TRUE((is_in_range<Info, -10, 10, 0>()));

}



} } } } }
