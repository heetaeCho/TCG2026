#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace wuint {



class Uint128Test_304 : public ::testing::Test {

protected:

    uint128 default_uint128;

    uint128 initialized_uint128;



    Uint128Test_304() 

        : default_uint128(), 

          initialized_uint128(0x123456789ABCDEF0, 0xFEDCBA9876543210) {}

};



TEST_F(Uint128Test_304, DefaultConstructorInitializesZero_304) {

    EXPECT_EQ(default_uint128.high(), static_cast<std::uint_least64_t>(0));

    EXPECT_EQ(default_uint128.low(),  static_cast<std::uint_least64_t>(0));

}



TEST_F(Uint128Test_304, ParameterizedConstructorInitializesCorrectly_304) {

    EXPECT_EQ(initialized_uint128.high(), static_cast<std::uint_least64_t>(0x123456789ABCDEF0));

    EXPECT_EQ(initialized_uint128.low(),  static_cast<std::uint_least64_t>(0xFEDCBA9876543210));

}



TEST_F(Uint128Test_304, LowMethodReturnsCorrectValue_304) {

    EXPECT_EQ(initialized_uint128.low(), static_cast<std::uint_least64_t>(0xFEDCBA9876543210));

}



TEST_F(Uint128Test_304, HighMethodReturnsCorrectValue_304) {

    EXPECT_EQ(initialized_uint128.high(), static_cast<std::uint_least64_t>(0x123456789ABCDEF0));

}



TEST_F(Uint128Test_304, OperatorPlusEqualUpdatesLow_304) {

    std::uint_least64_t increment = 1;

    initialized_uint128 += increment;

    EXPECT_EQ(initialized_uint128.high(), static_cast<std::uint_least64_t>(0x123456789ABCDEF0));

    EXPECT_EQ(initialized_uint128.low(),  static_cast<std::uint_least64_t>(0xFEDCBA9876543211));

}



TEST_F(Uint128Test_304, OperatorPlusEqualHandlesCarry_304) {

    std::uint_least64_t increment = 1;

    uint128 max_low(0x0, std::numeric_limits<std::uint_least64_t>::max());

    max_low += increment;

    EXPECT_EQ(max_low.high(), static_cast<std::uint_least64_t>(1));

    EXPECT_EQ(max_low.low(),  static_cast<std::uint_least64_t>(0));

}



}}}}} // namespace YAML::jkj::dragonbox::detail::wuint
