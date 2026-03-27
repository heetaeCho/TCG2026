#include <gtest/gtest.h>

#include <cstdint>



// Assuming the namespace structure is correct and umul128_upper64 is accessible

namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace wuint {



class DragonboxTest_308 : public ::testing::Test {

protected:

    using uint_least64_t = stdr::uint_least64_t;



    // Utility to test the function

    uint_least64_t umul128_upper64(uint_least64_t x, uint_least64_t y) const {

        return detail::wuint::umul128_upper64(x, y);

    }

};



// Test normal operation with typical values

TEST_F(DragonboxTest_308, NormalOperation_308) {

    EXPECT_EQ(umul128_upper64(0x123456789ABCDEF0, 0xFEDCBA9876543210), 0x1A9B5F54E2A44D2E);

}



// Test boundary condition with zero

TEST_F(DragonboxTest_308, ZeroMultiplication_308) {

    EXPECT_EQ(umul128_upper64(0, 0xFEDCBA9876543210), 0);

    EXPECT_EQ(umul128_upper64(0x123456789ABCDEF0, 0), 0);

}



// Test boundary condition with maximum values

TEST_F(DragonboxTest_308, MaxValuesMultiplication_308) {

    EXPECT_EQ(umul128_upper64(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF), 0xFFFFFFFFFFFFFFFE);

}



// Test boundary condition with one

TEST_F(DragonboxTest_308, OneMultiplication_308) {

    EXPECT_EQ(umul128_upper64(1, 0xFEDCBA9876543210), 0);

    EXPECT_EQ(umul128_upper64(0x123456789ABCDEF0, 1), 0);

}



// Test boundary condition with small values

TEST_F(DragonboxTest_308, SmallValuesMultiplication_308) {

    EXPECT_EQ(umul128_upper64(2, 3), 0);

    EXPECT_EQ(umul128_upper64(5, 7), 0);

}



// Test for overflow condition

TEST_F(DragonboxTest_308, OverflowCondition_308) {

    EXPECT_EQ(umul128_upper64(0x8000000000000000, 0x8000000000000000), 0x4000000000000000);

}



} } } } }
